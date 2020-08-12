#pragma once

#include <cstdlib>

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
		new_data[i] = data[i];
	  }
	  delete[] data;
	  data = new_data;
	  capacity_ = 2 * Capacity();
	}
	*end_ = value;
	end_++;
  }

private:
  // Добавьте поля для хранения данных вектора
  T* data = nullptr;
  T* end_ = nullptr;
  size_t capacity_ = 0;
};
