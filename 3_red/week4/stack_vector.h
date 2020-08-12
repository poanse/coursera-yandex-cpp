#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) {
	if (a_size > N) {
	  throw invalid_argument("Size is larger than capacity");
	}
	_end = data.begin() + a_size;
	_size = a_size;
  }

  T& operator[](size_t index) {
	return *(_end - _size + index);
  }
  const T& operator[](size_t index) const {
	return *(_end - _size + index);
  }

  T* begin() {return _end - _size;}
  T* end() {return _end;}
  T* begin() const {return _end - _size;}
  T* end() const {return _end;}

  size_t Size() const {return _size;}
  size_t Capacity() const {return N;};

  void PushBack(const T& value) {
	if (_size != N) {
	  *_end++ = value;
	  _size++;
	} else {
	  throw overflow_error("123");
	}
  }
  T PopBack() {
	if (_size == 0) {
	  throw underflow_error("133");
	}
	_size--;
	return *(--_end);
  }

private:
  array<T, N> data;
  T* _end;
  size_t _size;
};

