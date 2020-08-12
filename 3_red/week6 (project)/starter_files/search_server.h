#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <unordered_map>
#include <string>
#include <mutex>
#include <atomic>
#include <future>
using namespace std;

using DocId = size_t;

class InvertedIndex {
public:
	InvertedIndex()
	{
		docs.reserve(50000);
	}
  void Add(string document);
	//list<size_t> Lookup(const string& word) const;
	const vector<pair<DocId, size_t>>* Lookup(string_view word) const;
  const string& GetDocument(DocId id) const;
	size_t Size() const;
	void Swap(InvertedIndex& other);

//private:
	unordered_map<string_view, vector<pair<DocId, size_t>>> index;
  vector<string> docs;
};

class SearchServer {
public:
  SearchServer();
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
  void UpdateDocumentBaseThread(istream& document_input);
  void AddQueriesStreamThread(istream& query_input, ostream& search_results_output);
	mutable vector<mutex> mutexes;
	mutable mutex mut_for_next_mutex;
	mutable size_t next_mutex;
	~SearchServer() {
		for (auto& f : async_tasks) {
			f.get();
		}
	}

private:
  InvertedIndex index;
	vector<future<void>> async_tasks;
};
