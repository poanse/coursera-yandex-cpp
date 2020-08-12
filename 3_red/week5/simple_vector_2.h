#pragma once

#include <cstdlib>
#include <algorithm>
#include <utility>
using namespace std;
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector(){}
  explicit SimpleVector(size_t size){
	  data = new T[size];
	  end_ = data + size;
  	  capacity_ = size;
  }
  ~SimpleVector() {
	  delete[] data;
  }
	SimpleVector(const SimpleVector<T>& other);
	// rvalue reference (+temporary objects)
	SimpleVector(SimpleVector&& other);
	SimpleVector<T> operator=(const SimpleVector<T>& other);
	SimpleVector<T> operator=(SimpleVector<T>&& other);

  T& operator[] (size_t index) {
	  return *(data + index);
  }

  const T* begin() const { return data; }
  const T* end() const { return end_;	}

  T* begin() { return data; }
  T* end() { return end_; }

  size_t Size() const {return end_ - data;}
  size_t Capacity() const { return capacity_; }

  void PushBack(const T& value) {
	if (Capacity() == 0) {
	  data = new T[1];
	  end_ = data;
	  capacity_ = 1;
	} else if (Size() == Capacity()) {
	  T* new_data = new T[2 * Capacity()];
	  end_ = new_data + Size();
	  for (auto i = 0; new_data + i < end_; i++) {
		new_data[i] = move(data[i]);
	  }
	  delete[] data;
	  data = move(new_data);
	  capacity_ = 2 * Capacity();
	}
	*end_ = value;
	end_++;
  }

  void PushBack(T&& value) {
	if (Capacity() == 0) {
	  data = new T[1];
	  end_ = data;
	  capacity_ = 1;
	} else if (Size() == Capacity()) {
	  T* new_data = new T[2 * Capacity()];
	  end_ = new_data + Size();
	  for (auto i = 0; new_data + i < end_; i++) {
		new_data[i] = move(data[i]);
	  }
	  delete[] data;
	  data = move(new_data);
	  capacity_ = 2 * Capacity();
	}
	*end_ = move(value);
	end_++;
  }

private:
  // Добавьте поля для хранения данных вектора
  T* data = nullptr;
  T* end_ = nullptr;
  size_t capacity_ = 0;
};


template <typename T>
SimpleVector<T> SimpleVector<T>::operator=(const SimpleVector<T>& other) {
	delete[] data;
	data = new T[other.Size()];
	end_ = data + other.Size();
	capacity_ = other.capacity_;
	std::copy(other.begin(), other.end(), begin());
	//for (size_t i = 0; i < other.Size(); i++) {
		//data[i] = other.data[i];
	//}
	return *this;
}


template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other)
	: data(new T[other.Size()])
	, end_(data + other.Size())
	, capacity_(other.capacity_) {
		std::copy(other.begin(), other.end(), begin());
}

template <typename T>
SimpleVector<T>::SimpleVector(SimpleVector&& other)
	: data(other.data)
	, end_(data + other.Size())
	, capacity_(other.capacity_)
{
	other.data = nullptr;
	other.end_ = nullptr;
	other.capacity_ = 0;
}

template <typename T>
SimpleVector<T> SimpleVector<T>::operator=(SimpleVector<T>&& other) {
	delete[] data;
	data = other.data;
	end_ = other.end_;
	capacity_ = other.capacity_;
	other.data = nullptr;
	other.end_ = nullptr;
	other.capacity_ = 0;
	return *this;
}
