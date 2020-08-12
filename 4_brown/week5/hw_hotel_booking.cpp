#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

struct Booking {
	long long int time;
	size_t client_id;
	size_t room_count;
};

struct BookingInput {
	long long int time;
	size_t client_id;
	size_t room_count;
	string hotel_name;
};

istream& operator>> (istream& is, BookingInput& b) {
	is >> b.time >> b.hotel_name >> b.client_id >> b.room_count;
	return is;
}

struct HotelData {
	queue<Booking> q;
	size_t room_count = 0;
	unordered_map<size_t, size_t> client_count;


	void RemoveOutdated(long int current_time) {
		//cerr << "Entered RemoveOutdated method" << endl;
		while (!q.empty() && q.front().time + 86400 <= current_time) {
			RemoveLast();
		}
	}

	void RemoveLast() {
		//cerr << "Entered RemoveLast method" << endl;
		auto& b = q.front();
		room_count -= b.room_count;
		auto it = client_count.find(b.client_id);
		if (it->second == 1) {
			client_count.erase(it);
		} else {
			it->second--;
		}
		q.pop();
	}
};

class BookingManager {
private:
	unordered_map<string, HotelData> data;
	long long int current_time;
	void RemoveOutdatedAll() {
		for (auto& pair : data) {
			pair.second.RemoveOutdated(current_time);
		}
	}
public:
	void Book(const BookingInput& b) {
		//cerr << "Entered Book method" << endl;
		// add new
		current_time = b.time;
		auto& hdata = data[b.hotel_name];
		hdata.room_count += b.room_count;
		hdata.client_count[b.client_id]++;
		hdata.q.push({b.time, b.client_id, b.room_count});
	}

	size_t ClientCount(const string& hotel_name) {
		// delete old
		//RemoveOutdatedAll();
		data[hotel_name].RemoveOutdated(current_time);
		if (data.count(hotel_name)) {
			return data.at(hotel_name).client_count.size();
		}
		return 0;
	}

	size_t RoomCount(const string& hotel_name) {
		// delete old
		//RemoveOutdatedAll();
		data[hotel_name].RemoveOutdated(current_time);
		if (data.count(hotel_name)) {
			return data.at(hotel_name).room_count;
		}
		return 0;
	}
};




int main() {
	BookingManager bm;
	string command, hotel_name;
	BookingInput b;
	size_t Q;
	cin >> Q;
	for (size_t i = 0; i < Q; i++) {
		cin >> command;
		if (command == "CLIENTS") {
			cin >> hotel_name;
			cout << bm.ClientCount(hotel_name) << endl;
		} else if (command == "ROOMS") {
			cin >> hotel_name;
			cout << bm.RoomCount(hotel_name) << endl;
		} else if (command == "BOOK") {
			cin >> b;
			bm.Book(b);
		}
	}
}
