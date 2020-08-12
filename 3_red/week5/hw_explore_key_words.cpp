#include "test_runner.h"
#include "profile.h"

#include <iostream>
#include <map>
#include <string>
#include <future>
#include <functional>
#include <algorithm>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
		for (auto& [key, value] : other.word_frequences) {
			word_frequences[key] += value;
		}
	}
};

void ProcessWord(const set<string>& key_words, Stats& stats, string word) 
{
	if (key_words.count(word)) {
		stats.word_frequences[word]++;
	}
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats stats;
	string word;
	for (char ch : line) {
		if (ch == ' ') {
			ProcessWord(key_words, stats, move(word));
		} else {
			word += ch;
		}
	}
	ProcessWord(key_words, stats, move(word));
	return stats;
}

Stats ExploreLines(const set<string>& key_words,  vector<string> lines) {
	Stats stats;
	string word;
	auto process_line = [&](const string& line){
		stats += ExploreLine(key_words, line);
	};
	for_each(lines.begin(), lines.end(), process_line);
	return stats;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input) 
{
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  // Реализуйте эту функцию
	constexpr int N = 500;
	Stats stats;
	vector<string> lines;
	lines.reserve(N);
	vector<future<Stats>> futures;
	int i = 0;
  for (string line; getline(input, line); ) {
		lines.push_back(move(line));
		if (i >= N) {
			futures.push_back(async(
						ExploreLines, ref(key_words), move(lines)
			));
			i = -1;
		}
		i++;
  }
	if (i > 0) {
		futures.push_back(async(ExploreLines, ref(key_words), move(lines)));
	}
	for (auto& f : futures) {
		stats += f.get();
	}
	return stats;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
