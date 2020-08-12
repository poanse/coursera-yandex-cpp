#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <sstream>
using namespace std;


template <typename Collection>
string Join(const Collection& c, char d) {
	stringstream ss;
	bool first = true;
	for (const auto& i : c) {
		if (!first) {
			ss << d;
		}
		first = false;
		ss << i;
	}
	return ss.str();
}

template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1,T2>& vi) {
	return out << '(' << vi.first << ',' << vi.second << ')';
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& vi) {
	return out << '[' << Join(vi, ',') << ']';
	//for (const auto& i : vi) {
	//	out << i << ' ';
	//}
	//return out;
}

template <typename T, typename T2>
ostream& operator<<(ostream& out, const map<T,T2>& m) {
	return out << '{' << Join(m, ',') << '}';
	//for (const auto& i : vi) {
	//	out << i << ' ';
	//}
	//return out;
}

int main() {
	vector<double> vi {1,2.5,3};
	cout << vi << endl;
	map<int, int> m ={{1,2}, {3,4}};
	cout << m << endl;
	vector<vector<int>> vv {{1,2},{3,4}};
	cout << vv << endl;
}
