#include<vector>
#include<iostream>
using namespace std;

vector<int> Reversed(const vector<int>& v){
	vector<int> vec = {};
	for (int i = 0; i < v.size(); ++i){
		vec.push_back(v[v.size() - i - 1]);
	}
	return vec;
}

int main() {
	vector<int> v = {1, 2, 3};
	for (auto x : Reversed(v)){
		cout << x << " ";
	}
	cout << endl;
}
