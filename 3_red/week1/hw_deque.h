#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Deque {
private:
	vector<T> forward;
	vector<T> backward;
	size_t bias = 0; 
public:
	bool Empty() const {
		return forward.empty() && backward.empty();
	}

	size_t Size() const {
		return forward.size() + bias;
	}

	T& operator[](size_t index) {
		if (index < bias) {
			return backward[bias - 1 - index];
		}
		return forward[index - bias];
	}

	const T& operator[](size_t index) const {
		if (index < bias) {
			return backward[bias - 1 - index];
		}
		return forward[index - bias];
	}

	T& At(size_t index) {
		if (index < Size()) {
			return operator[] (index);
		}
		throw out_of_range("");
	}
	const T& At(size_t index) const {
		if (index < Size()) {
			return operator[] (index);
		}
		throw out_of_range("");
	}

	T& Front() {
		if (0 == backward.empty()) {
			return backward.back();
		}
		return forward.front();
	}
	const T& Front() const {
		if (0 == backward.empty()) {
			return backward.back();
		}
		return forward.front();
	}

	T& Back() {
		if (0 == forward.empty()) {
			return forward.back();
		}
		return backward.front();
	}
	const T& Back() const {
		if (0 == forward.empty()) {
			return forward.back();
		}
		return backward.front();
	}

	void PushFront(T elem) {
		backward.push_back(move(elem));
		bias++;
	}
	void PushBack(T elem) {
		forward.push_back(move(elem));
	}

};
