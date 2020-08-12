#include <iostream>
#include "profile.h"
#include <vector>
#include <string>
using namespace std;

string MakeString() {
	return string(100000000,'a');
}


int main() {
	{
		LOG_DURATION("with variable");
		vector<string> strings;
		string heavy_string = MakeString();
		strings.push_back(heavy_string);
	}
	{
		LOG_DURATION("without variable");
		vector<string> strings;
		strings.push_back(MakeString());
	}
}
