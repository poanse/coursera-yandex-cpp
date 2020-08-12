#include <iostream>
#include <iostream>
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
class Route {
	public:
		string GetSource() {
			return source;
		}
		string GetDestination() {
			return destination;
		}
		int GetLength() {
			return length;
		}
		void SetSource(const string& new_source){
			source = new_source;
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

int ComputeDistance(const string& source, const string& destination);

int main(){
}
