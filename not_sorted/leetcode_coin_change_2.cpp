#include <iostream>
#include <vector>
#include <map>
using namespace std;


int rec_change(int& amount, 
				const vector<int>& coins,
				int& combinations,
				int& largest_coin,
				vector<map<int,int>>& amounts) {
	if (amounts[largest_coin].count(amount) > 0) {
		return amounts[largest_coin][amount];
	} else {
		int value = 0;
		if (amount % coins[0] == 0) {
			++value;
		}
		//for (int i = 1; i <= largest_coin; i++) {
		for (int i = largest_coin; i > 0; --i) {
			int new_amount = amount - coins[i];
			if (new_amount > 0) {
				value += rec_change(new_amount, coins, combinations, i, amounts);
			} else if (new_amount == 0) {
				++value;
			}
		}
		amounts[largest_coin][amount] = value;
		return value;
	}
}

int change(int amount, const vector<int>& coins) {
	if (amount == 0) {
		return 1;
	}
	if (coins.size() == 0) {
		return 0;
	}
	int combinations = 0;
	vector<map<int,int>> amounts;
	for (int i = 0; i < coins.size(); i++) {
		amounts.push_back({});
	}
	int largest_coin = coins.size() - 1;
	combinations = rec_change(amount, coins, combinations, largest_coin, amounts);
	return amounts[largest_coin][amount];
}

int main() {
	//int amount = 5;
	//vector<int> coins {1,2,5};
	int amount = 500;
	vector<int> coins {3,5,7,8,9,10,11};
	cout << change(amount, coins) << endl;
}
