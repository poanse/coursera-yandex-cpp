#include <iostream>
//#include <string>
//#include <algorithm>
//#include <vector>
#include <cmath>
using namespace std;

int main() {
	double a, b, c;
	cin >> a >> b >> c;
	double d = b * b - 4 * a * c;
	d = sqrt(d);
	if ((a == 0.0) && (b == 0.0)) {
		return 0;
	} else if (a == 0) {
		cout << -c / b;
		return 0;
	} else if (d == 0.0) {
		cout << -b / 2 / a;	
	} else if (d > 0) {
		double x1, x2;
		x1 = (-b + d) / 2 / a;
		x2 = (-b - d) / 2 / a;
		cout << x1 << ' ' << x2;
	}
}
