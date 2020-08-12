#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
struct Route {
	string source = "Moscow";
	string destination = "Saint Petersburg";
};

struct Route {
	private:
		string source;
		string destination;
}; // cannot read source or destination
*/
int ComputeDistance(const string& source, const string& dest) {
	return 1;
}

class Route {
public:
	// constructors
	// Route() {}
	Route() { // default
		source = "Moscow";
		destination = "Saint Petersburg";
		UpdateLength();
		cout << "Default constructed" << endl;
	}
	Route(const string& new_source, const string& new_destination) {
		source = new_source;
		destination = new_destination;
		UpdateLength();
		cout << "Constructed" << endl;
	}
	// destructors
	~Route() {
		cout << "Destructed" << endl;
	}
	// methods
	string GetSource() const {
		return source;
	}
	string GetDestination() const {
		return destination;
	}
	int GetLength() const {
		return length;
	}
	void SetSource(const string& new_source){
		source = new_source;
		UpdateLength();
	}
	void SetDestination(const string& new_source){
		destination = new_source;
		UpdateLength();
	}
private:
	void UpdateLength() {
		length = ComputeDistance(source, destination);
		compute_distance_log.push_back(source + " - " + destination);
	}
	string source;
	string destination;
	int length;
	vector<string> compute_distance_log;
};

void PrintRoute(const Route& route) {
	cout << route.GetSource() << " - " << 
		route.GetDestination() << endl;
}

int main(){
	for (int i : {0,1}) {
		cout << "Step1 " << i << endl;
		Route route {};
		cout << "Step2 " << i << endl;
	}
	cout << "End" << endl;
}
