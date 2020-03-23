#include <cstdio>
#include <ctime>
#include <iostream>

using namespace std;

//binary_search
//merge_class
//in_place_class
//quick_class
//strassen_class

class binary_search {
private:
	int n = 0, x = -1;
	int* S = nullptr;
	int temp[12] = { 0, 10, 12, 13, 14, 18, 20, 25, 27, 30, 35, 40 };

public:
	binary_search() : n(12), x(0), S(temp) {	

	}

	binary_search(int size, int var) : n(size), x(var) {
		S = new int[n];
		for (int i = 0; i < n; i++) {
			S[i] = 0;
		}
	}

	void set_x(int input) {
		x = input;
	}

	void set_n(int input) {
		n = input;
	}

	int get_n() {
		return n;
	}

	int loc_recursive(int low, int high) {
		int mid;
		if (low > high) {
			return 0;
		}
		else {
			mid = (low + high) / 2;
			if (x == S[mid]) {
				return mid;
			}
			else if (x < S[mid]){
				return loc_recursive(low, mid - 1);
			}
			else {
				return loc_recursive(mid + 1, high);
			}
		}
	}

	void main() {
		cout << endl << "< binary search main >" << endl;
		set_x(12);
		cout << loc_recursive(0, get_n()) << endl;
	}
};

class merge_class {
private:
	int temp[9] = {-1, 27, 10, 12, 20, 25, 13, 15, 22 };

public:
	int* get_S() {
		return temp;
	}

	int get_size() {
		return sizeof(temp) / sizeof(int);
	}

	void merge_sort(int n, int* S) {
		int left = n / 2;
		int left_over = n - left;

		int* left_S = new int[left + 1];
		int* right_S = new int[left_over + 1];

		if (n > 1) {
			for (int i = 1; i <= left; i++) {
				left_S[i] = S[i];
			}
			for (int i = 1; i <= left_over; i++) {
				right_S[i] = S[left + i];
			}

			merge_sort(left, left_S);
			merge_sort(left_over, right_S);
			merge(left, left_over, left_S, right_S, S);
		}

		delete[]left_S;
		delete[]right_S;
 	}

	void merge(int left, int right, int* left_S, int* right_S, int* S) {
		int i = 1, j = 1, k = 1;

		while (i <= left && j <= right) {
			if (left_S[i] < right_S[j]) {
				S[k] = left_S[i];
				i++;
			}
			else {
				S[k] = right_S[j];
				j++;
			}
			k++;
		}

		if (i > left) {
			for (int t = j; t <= right; t++) {
				S[k++] = right_S[t];
			}
		}
		else {
			for (int t = i; t <= left; t++) {
				S[k++] = left_S[t];
			}
		}
	}

	void main() {
		int* temp = get_S();
		cout << endl << "< merge sort main >" << endl;
		for (int i = 1; i < get_size(); i++) {
			cout << temp[i] << " ";
		}
		cout << endl;
		merge_sort(get_size() - 1, get_S());

		for (int i = 1; i < get_size(); i++) {
			cout << temp[i] << " ";
		}
		cout << endl;
	}
};

class in_place_class {
private:
	int temp[9] = { -1, 27, 10, 12, 20, 25, 13, 15, 22 };

public:
	int* get_S() {
		return temp;
	}

	int get_size() {
		return sizeof(temp) / sizeof(int);
	}

	void merge_sort(int low, int high) {
		int mid;
		if (low < high) {
			mid = (low + high) / 2;
			merge_sort(low, mid);
			merge_sort(mid + 1, high);
			merge(low, mid, high);
		}
	}

	void merge(int low, int mid, int high) {
		int* S = temp;
		int i = low, j = mid + 1, k = low;
		int* U = new int[get_size()];

		while (i <= mid && j <= high) {
			if (S[i] < S[j]) {
				U[k] = S[i];
				i++;
			}
			else {
				U[k] = S[j];
				j++;
			}
			k++;
		}

		if (i > mid) {
			for (int t = j; t <= high; t++) {
				U[k] = S[t];
				k++;
			}
		}
		else {
			for (int t = i; t <= mid; t++) {
				U[k] = S[t];
				k++;
			}
		}
		
		for (int t = low; t <= high; t++) {
			S[t] = U[t];
		}
		delete []U;
	}

	void main() {
		int* temp = get_S();
		cout << endl << "< in place sort main >" << endl;
		for (int i = 1; i < get_size(); i++) {
			cout << temp[i] << " ";
		}
		cout << endl;
		merge_sort(1, get_size() - 1);

		for (int i = 1; i < get_size(); i++) {
			cout << temp[i] << " ";
		}
		cout << endl;
	}
};

class quick_class {
private:
	int S[9] = { -1, 15, 22, 13, 27, 12, 10, 20, 25 };

public:
	quick_class() {
		srand(time(NULL));
	}

	int* get_S() {
		return S;
	}

	int get_size() {
		return sizeof(S) / sizeof(int);
	}

	void quick_sort(int low, int high) {
		int pivot_point = -1;
		if (high > low) {
			partition(low, high, &pivot_point);
			quick_sort(low, pivot_point);
			quick_sort(pivot_point + 1, high);
		}
	}

	void partition(int low, int high, int* pivot_point) {
		int pivot_item = S[low];
		int low_temp = low, temp = -1;

		for (int i = low + 1; i <= high; i++) {
			// i 와 low_temp 와 교환
			if (S[i] < pivot_item) {
				low_temp++;
				temp = S[low_temp];
				S[low_temp] = S[i];
				S[i] = temp;
			}
			*pivot_point = low_temp;
			temp = S[low];
			S[low] = S[*pivot_point];
			S[*pivot_point] = temp;
		}
	}

	void main() {
		int* temp = get_S();
		cout << endl << "< quick sort main >" << endl;
		for (int i = 1; i < get_size(); i++) {
			cout << temp[i] << " ";
		}
		cout << endl;
		quick_sort(1, get_size() - 1);

		for (int i = 1; i < get_size(); i++) {
			cout << temp[i] << " ";
		}
		cout << endl;

	}
};

class strassen_class {
private:
	int size;
	int **A, **B, **C;

public:
	strassen_class() : size(2) {
		srand(time(NULL));
		A = new int* [size];
		B = new int* [size];
		C = new int* [size];

		for (int i = 0; i < size; i++) {
			A[i] = new int[size];
			B[i] = new int[size];
			C[i] = new int[size];

			for (int j = 0; j < size; j++) {
				A[i][j] = rand() % 4 + 1;
				B[i][j] = rand() % 4 + 1;
				C[i][j] = -1;
			}
		}
	}

	~strassen_class() {
		delete_class();
	}

	void delete_class() {
		for (int i = 0; i < size; i++) {
			delete[]A[i];
			delete[]B[i];
			delete[]C[i];
		}

		delete[]A;
		delete[]B;
		delete[]C;
	}
	
	void print_matrix(int** matrix_a, int** matrix_b, int** matrix_c) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << matrix_a[i][j] << " ";
			}
			cout << "   ";
			for (int j = 0; j < size; j++) {
				cout << matrix_b[i][j] << " ";
			}
			cout << "   ";
			for (int j = 0; j < size; j++) {
				cout << matrix_c[i][j] << " ";
			}
			cout << endl;
		}
	}

	void ordinary_mult() {
		// 8 times multiplication and 4 times addition
		int sum = 0, k = 0;
		for (int i = 0; i < size; i++) {
			while (k != size) {
				for (int j = 0; j < size; j++) {
					sum += A[i][j] * B[j][k];
				}
				C[i][k] = sum;
				sum = 0;
				k++;
			}
			k = 0;
		}
	}

	void strassen_mult() {
		int M1, M2, M3, M4, M5, M6, M7;
		M1 = (A[0][0] + B[1][1]) * (B[0][0] + B[1][1]);
		M2 = (A[1][0] + A[1][1]) * B[0][0];
		M3 = A[0][0] * (B[0][1] - B[1][1]);
		M4 = A[1][1] * (B[1][0] - B[0][0]);
		M5 = (A[0][0] + A[0][1]) * B[1][1];
		M6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
		M7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

		C[0][0] = M1 + M4 - M5 + M7;
		C[0][1] = M3 + M5;
		C[1][0] = M2 + M4;
		C[1][1] = M1 - M2 + M3 + M6;
	}

	void main() {
		strassen_mult();
		print_matrix(A, B, C);
	}

};

int main() {
	clock_t start, end;
	start = clock();

	binary_search bs = binary_search();
	bs.main();

	merge_class mc = merge_class();
	mc.main();

	in_place_class ic = in_place_class();
	ic.main();

	quick_class qc = quick_class();
	qc.main();

	strassen_class sc = strassen_class();
	sc.main();
	end = clock();

	printf("%f ms", double(double(end) - double(start)));
	return 0;
}