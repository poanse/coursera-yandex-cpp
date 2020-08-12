#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class Matrix{
	public:
		Matrix() {
			n_rows = 0;
			n_cols = 0;
		}
		Matrix(int num_rows, int num_cols) {
			Reset(num_rows, num_cols);
		}
		void Reset(int new_rows, int new_cols) {
			if (new_rows < 0 || new_cols < 0) {
				throw out_of_range("Number of rows/columns < 0");	
			} else if (new_rows == 0 || new_cols == 0) {
				n_rows = n_cols = 0;
			} else {
				n_rows = new_rows;
				n_cols = new_cols;
			}
			values = {};
			for (int i = 0; i < n_rows; ++i) {
				values.push_back({});
				for (int j = 0; j < n_cols; ++j) {
					values[i].push_back({0});
				}
			}
		}
		
		int At(int row, int col) const {
			if (row < 0 || row > n_rows - 1 || col < 0 || col > n_cols - 1) {
				throw out_of_range("Wrong number of rows/columns");
			} else {
				return values[row][col];
			}
		}
		int& At(int row, int col) {
			if (row < 0 || row > n_rows - 1 || col < 0 || col > n_cols - 1) {
				throw out_of_range("Wrong number of rows/columns");
			} else {
				return values.at(row).at(col);
			}
		}
		int GetNumRows () const {
			return n_rows;
		}
		int GetNumColumns () const {
			return n_cols;
		}

	private:
		int n_rows;
		int n_cols;
		vector<vector<int>> values;
};

istream& operator>>(istream& stream, Matrix& matrix) {
	int n_rows, n_cols;
	stream >> n_rows >> n_cols;
	matrix = Matrix(n_rows, n_cols);
	for (int i = 0; i < n_rows; ++i) {
		for (int j = 0; j < n_cols; ++j) {
			stream >> matrix.At(i,j);
		}
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
	stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	for (int i = 0; i < matrix.GetNumRows(); ++i) {
		for (int j = 0; j < matrix.GetNumColumns(); ++j) {
			stream << matrix.At(i,j) << " ";
		}
		if (i != matrix.GetNumRows()-1) {
			stream << endl;
		}
	}
	return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() != rhs.GetNumRows()) {
		return false;
	} else if (lhs.GetNumColumns() != rhs.GetNumColumns()) {
		return false;
	} else {
		for (int i = 0; i < lhs.GetNumRows(); ++i) {
			for (int j = 0; j < lhs.GetNumColumns(); ++j) {
				if (lhs.At(i, j) != rhs.At(i, j)) {
					return false;
				}
			}
		}
	}
	return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() != rhs.GetNumRows()) {
		throw invalid_argument("Arguments are of different size");
	} else if (lhs.GetNumColumns() != rhs.GetNumColumns()) {
		throw invalid_argument("Arguments are of different size");
	} else {
		int nrows = lhs.GetNumRows();
		int ncols = lhs.GetNumColumns();
		Matrix matrix = Matrix(nrows, ncols);
		for (int i = 0; i < nrows; ++i) {
			for (int j = 0; j < ncols; ++j) {
				matrix.At(i,j) = lhs.At(i,j) + rhs.At(i,j);
			}
		}
		return matrix;
	}
}

int main() {
	Matrix matrix1, matrix2;
	stringstream s1 {"2 3 1 2 3 4 5 6"};
	stringstream s2 {"2 3 1 2 3 4 5 6"};
	s1 >> matrix1;
	s2 >> matrix2;
	cout << (matrix1 == matrix2) << endl;
	matrix2.Reset(1,1);
	cout << (matrix1 == matrix2) << endl;
	matrix1 = Matrix(0,2);
	matrix2 = Matrix(0,2);
	Matrix matrix3 = matrix1 + matrix2;
	cout << matrix3;
	//matrix.Reset(5,8);
	//cout << matrix;
	//Matrix new_matrix = matrix + matrix;
	//cout << new_matrix << endl;
}
