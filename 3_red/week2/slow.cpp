//#include "profile.h"

#include <set>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

//class RouteManager {
//public:
  //void AddRoute(int start, int finish) {
    //reachable_lists_[start].push_back(finish);// O(logN)
    //reachable_lists_[finish].push_back(start);// O(logN)
  //}
  //int FindNearestFinish(int start, int finish) const {
    //int result = abs(start - finish);
    //if (reachable_lists_.count(start) < 1) {// O(logN)
        //return result;
    //}
    //const vector<int>& reachable_stations = \
		//reachable_lists_.at(start);// O(logN)
    //if (!reachable_stations.empty()) {
      //result = min(
          //result,
          //abs(finish - *min_element(
              //begin(reachable_stations), end(reachable_stations),
              //[finish](int lhs, int rhs) { 
				  //return abs(lhs - finish) < abs(rhs - finish); 
			  //}// O(N)
          //))
      //);
    //}
    //return result;
  //}
//private:
  //map<int, vector<int>> reachable_lists_;
//};

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);// O(logN)
    reachable_lists_[finish].insert(start);// O(logN)
  }
  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {// O(logN)
        return result;
    }
    const set<int>& reachable_stations = \
		reachable_lists_.at(start);// O(logN)
    if (!reachable_stations.empty()) {
		int alternative;
		auto it = reachable_stations.lower_bound(finish); 
		if (it == begin(reachable_stations)) {
			alternative = *it;
		} else if (it == end(reachable_stations)) {
			alternative = *(prev(it));
		} else {
			if ((*it - finish) < (finish - *prev(it))) {
				alternative = *it;
			} else {
				alternative = *(prev(it));
			}
		}
			//alternative = *min_element(prev(it), it, 
              //[finish](int lhs, int rhs) { 
				  //return abs(lhs - finish) < abs(rhs - finish); 
			  //}
			//);
      result = min(result, abs(finish - alternative));
    }
		return result;
  }
private:
  map<int, set<int>> reachable_lists_;
};

int main() {
  //LOG_DURATION("ALL");
  RouteManager routes;

  int query_count;
  cin >> query_count;
  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << '\n';
    }
  }

  return 0;
}
