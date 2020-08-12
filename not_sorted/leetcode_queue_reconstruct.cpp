#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

void PrintQueue(const vector<vector<int>>& myqueue) {
	for (auto& i : myqueue) {
		cout << i[0] << ":" << i[1] << " ";
	}
	cout << endl;
}

vector<vector<int>> reconstructQueue(vector<vector<int>>& input) {
	int n = input.size();
	
	vector<int> idx;
	for (int i = 0; i < n; i++) {
		// idx[i] = i;
		idx.push_back(i);
	}

	vector<vector<int>> myqueue;
	myqueue.assign(n, {0,0});
	
	// create set of heights, sort it and iterate over
	set<int> heights;
	for (auto& i : input) {
		heights.insert(i[0]);
	}
	
	for (auto& height : heights) {
		// find shortest height
		// for every shortest person: insert into myqueue
		vector<int> idx_to_delete;
		for (auto& person : input) {
			if (person[0] == height) {
				//myqueue.insert(myqueue.begin() + idx[person[1]], person);
				myqueue[idx[person[1]]] = person;
				//PrintQueue(myqueue);
				idx_to_delete.push_back(person[1]);
				//input.erase(&person);
			}
		}
		// delete used indexes
		sort(idx_to_delete.begin(), idx_to_delete.end());
		for (int i = idx_to_delete.size(); i > 0; --i) {
			idx.erase(idx.begin() + idx_to_delete[i - 1]); 
		}
	}
	return myqueue;
}

int main() {
	vector<vector<int>> input {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
	vector<vector<int>> myqueue = reconstructQueue(input);
	PrintQueue(myqueue);
}
