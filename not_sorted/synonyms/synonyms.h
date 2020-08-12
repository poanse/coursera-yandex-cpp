#pragma once
#include <set>
#include <map>
#include <string>
using namespace std;

using Synonyms = map<string, set<string>>;


void AddSynonyms (Synonyms& dict, const string& a, const string& b);
size_t CountSynonyms (Synonyms& dict, const string& word);
bool AreSynonyms (Synonyms& dict, const string& word1, const string& word2);
