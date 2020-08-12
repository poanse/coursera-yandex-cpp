#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
	vector<string> words;
	char delim = ' ';
	string::const_iterator it_begin = s.begin();
	string::const_iterator it_delim;
	while(1) {
		it_delim = find(it_begin, s.end(), delim);
		words.emplace_back(it_begin, it_delim);
		if (it_delim == s.end()) {
			break;
		}
		it_begin = next(it_delim);
	}
	return words;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
