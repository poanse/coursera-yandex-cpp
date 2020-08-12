#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool IsPalindrom(string s) {
	int n = s.size();
	for (int i = 0; i < n; ++i) {
		if (s[i] != s[n - i - 1]) {
			return false;
		}
	}
	return true;
}

vector<string> PalindromFilter(const vector<string>& words, int minLength) {
	vector<string> output;
	for (auto word : words) {
		if (IsPalindrom(word) && word.size() >= minLength) {
			output.push_back(word);
		}
	}
	return output;
}

int main() {
	vector<string> words = {"weew","bro","code"};
	int minlength = 4;
	for (auto x : PalindromFilter(words, minlength)) {
		cout << x << ' ';
	}
}
