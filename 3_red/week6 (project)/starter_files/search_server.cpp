#include "search_server.h"
#include "iterator_range.h"
#include "logger.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <mutex>
#include <future>
#include <iterator>
#include <functional>

vector<string_view> SplitIntoWords(const string& line) {
	vector<string_view> words;
	auto current_word = line.begin();
	size_t length = 0;
	for (auto it = line.begin(); it != line.end(); it++) {
		if (length == 0) {
			current_word = it;
			if (*it != ' '){
				length = 1;
			}
		} else {
			if (*it == ' ') {
				words.emplace_back(&(*current_word), length);
				current_word = it;
				length = 0;
			} else {
				length++;
			}
		}
	}
	if (length > 0) {
		words.emplace_back(&(*current_word), length);
	} 
	return words;
}

SearchServer::SearchServer()
	: mutexes(100)
	, next_mutex(0)
{
}
SearchServer::SearchServer(istream& document_input)
	: mutexes(100)
	, next_mutex(0)
{
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBaseThread(istream& document_input) {
	InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document); ) {
		new_index.Add(move(current_document));
  }
	for (auto& m : mutexes) {
		m.lock();
	}
	index.Swap(new_index);
	for (auto& m : mutexes) {
		m.unlock();
	}
}
void SearchServer::UpdateDocumentBase(istream& document_input) {
	if (index.index.empty()) {
		UpdateDocumentBaseThread(document_input);
	} else {
		async_tasks.push_back(
			async(
					[&](){ UpdateDocumentBaseThread(document_input); }
			)
		);
	}
}


void SearchServer::AddQueriesStreamThread(
  istream& query_input, ostream& search_results_output
) {
	//Logger log; 
	mutex* m = nullptr;
	{
		lock_guard<mutex> guard(mut_for_next_mutex);
		m = &mutexes[next_mutex];
		next_mutex++;
		if (next_mutex >= mutexes.size()) {
			next_mutex = 0;
		}
	}
	vector<size_t> docid_count_v(index.Size(), 0);
  for (string current_query; getline(query_input, current_query); ) {
		//log.Start();
		//log.Tick("1_Split");
		docid_count_v.assign(index.Size(), 0);
		{
			lock_guard guard(*m);
			for (const auto word : SplitIntoWords(current_query)) {
				auto lookup = index.Lookup(word);
				if (lookup) {
					for (auto [docid, counts] : *lookup) {
						docid_count_v[docid] += counts;
					}
				}
			}
		}

		vector<pair<size_t, size_t>> search_results;
		search_results.reserve(index.Size());
		for (size_t id = 0; id < index.Size(); id++) {
			if (docid_count_v[id] > 0){
				search_results.emplace_back(id, docid_count_v[id]);
			}
		}
		//log.Tick("2_CreateMap");
		//log.Tick("3_ConvertToVector");
		partial_sort(
			begin(search_results),
			begin(search_results) + min((size_t)5, search_results.size()),
			end(search_results),
			[](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
				if (lhs.second != rhs.second) {
					return lhs.second > rhs.second;
				}
				return lhs.first < rhs.first;
			}
		);
		

		//log.Tick("4_PartialSort");

		search_results_output << current_query << ':';
		for (auto [docid, hitcount] : Head(search_results, 5)) {
			search_results_output << " {"
				<< "docid: " << docid << ", "
				<< "hitcount: " << hitcount << '}';
		}
		search_results_output << endl;
		//log.Tick("5_Output");
  }
}

void SearchServer::AddQueriesStream(istream& query_input, 
		ostream& search_results_output) 
{
	async_tasks.push_back(async(
		[&] () {
			AddQueriesStreamThread(query_input, search_results_output);
		}
	));
}

void InvertedIndex::Add(string document) {
	size_t docid = docs.size();
  docs.push_back(move(document));
  for (auto word : SplitIntoWords(docs[docid])) {
		if (!index.count(word)) {
			index[word].reserve(50000);
		}
		auto& lookup = index[word];
		if (!lookup.empty() && lookup.back().first == docid) {
			lookup.back().second++;
		} else {
			lookup.emplace_back(docid, 1);
		}
  }
}

const string& InvertedIndex::GetDocument(size_t id) const {
	return docs[id];
}

const vector<pair<size_t, size_t>>* InvertedIndex::Lookup(string_view word) const {
	if (auto it = index.find(word); it != index.end()) {
		return &it->second;
	}
	return nullptr;
}

size_t InvertedIndex::Size() const {
	return docs.size();
}

void InvertedIndex::Swap(InvertedIndex& other) {
	index.swap(other.index);
	docs.swap(other.docs);
}
