#include<cmath>
#include<iostream>

int main() {
	int x = 1534236469;
	std::cout << x << "\n";
	bool is_negative = false;
	if (x < 0){
	    x = -x;
	    is_negative = true;
	}
	long int number = 0;
	int digit;
	int power = 10;
	while (x > 0){
	    power = power - 1;
	    if (power < 0){
		return 0;
	    }
	    digit = x % 10;
	    if (number == 0 && digit > 2){
		power = power - 1;
	    }
	    number += digit * std::pow(10, power);
	    x = x / 10;
	}
	number = number / std::pow(10, power);
	if (is_negative == true){
	    number = -number;
	}
	std::cout << number << "\n";
	return number;
}

