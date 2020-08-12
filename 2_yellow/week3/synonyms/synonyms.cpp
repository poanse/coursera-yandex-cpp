#include "synonyms.h"

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
