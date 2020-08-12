#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

using Synonyms = map<string, set<string>>;

void AddSynonyms (Synonyms& dict, const string& a, const string& b) {
	dict[a].insert(b);	
	dict[b].insert(a);	
}

size_t CountSynonyms (Synonyms& dict, const string& word) {
	return dict[word].size();
}

bool AreSynonyms (Synonyms& dict, const string& word1, const string& word2) {
	if (dict[word1].count(word2)) {
		return true;
	}
	return false;
}



int main() {
	Synonyms dict;
	int Q;
	cin >> Q;
	string command;
	string w1, w2;
	for (auto i = 0; i < Q; i++) {
		cin >> command;
		if (command == "ADD") {
			cin >> w1 >> w2;
			AddSynonyms(dict, w1, w2);
		} else if (command == "COUNT") {
			cin >> w1;
			cout << (CountSynonyms(dict, w1)) << endl;
		} else if (command == "CHECK") {
			cin >> w1 >> w2;
			if (AreSynonyms(dict, w1, w2)) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
		}
	}
}
