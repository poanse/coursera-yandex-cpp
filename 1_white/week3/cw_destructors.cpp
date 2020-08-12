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
	}
	Route(const string& new_source, const string& new_destination) {
		source = new_source;
		destination = new_destination;
		UpdateLength();
	}
	// destructors
	~Route() {
		for (const string& entry : compute_distance_log) {
			cout << entry << endl;
		}
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
	Route route("Moscow", "Vologda");
	PrintRoute(route);
	PrintRoute(Route());
	PrintRoute({});
	PrintRoute(Route("Moscow", "Zvenigorod"));
	PrintRoute({"Moscow", "Zvenigorod"});
	cout << endl;
	route.SetSource("Kaluga");
	route.SetDestination("Vyborg");
}
