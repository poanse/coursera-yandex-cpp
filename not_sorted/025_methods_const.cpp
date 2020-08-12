#include <iostream>
#include <string>
#include <iostream>
using namespace std;
/*
struct Route {
	string source;
	string destination;
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
	string source;
	string destination;
	int length;
	void UpdateLength() {
		length = ComputeDistance(source, destination);
	}
};

void PrintRoute(const Route& route) {
	cout << route.GetSource() << " - " << 
		route.GetDestination() << endl;
}

int main(){
	Route route;
	route.SetSource("Moscow");
	route.SetDestination("Vologda");
	PrintRoute(route);
}
