#include "test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table

template <class T>
class Table {
public:
	Table(size_t n, size_t m) {
		n_rows = n;
		n_cols = m;
		data = vector<vector<T>> (n_rows);
		for (auto& vec : data) {
			vec = vector<T> (n_cols, T());
		}
	}

	pair<size_t, size_t> Size() const {
		return {n_rows, n_cols};
	}

	void Resize(size_t rows, size_t cols) {
		//if (rows < n_rows) {
			//data.erase(data.begin() + rows, data.end());
		//} else if (rows > n_rows) {
			//vector<vector<T>> tmp (rows - n_rows);
			//data.insert(data.end(), tmp.begin(), tmp.end());
		//}
		//if (cols < n_cols) {
			//for (auto & vec : data) {
				//vec.erase(vec.begin() + cols, vec.end());
			//}
		//} else if (cols > n_cols) {
			//vector<T> tmp (cols - n_cols, T());
			//for (auto & vec : data) {
				//vec.insert(vec.end(), tmp.begin(), tmp.end());
			//}
		//}
		data.resize(rows);
		for (auto& vec : data) {
			vec.resize(cols);
		}
		n_rows = rows;
		n_cols = cols;
	}

	vector<T>& operator[] (size_t i) {
		return data[i];
	}

	vector<T>& operator[] (size_t i) const {
		return data[i];
	}
private:
	vector<vector<T>> data;
	size_t n_rows;
	size_t n_cols;
};


void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
  //Table<int> tt(2,2);
  //cout << tt[1][1] << endl;
  //tt.Resize(2,4);
  //cout << (tt[0][0] == tt[0][3]) << endl;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
