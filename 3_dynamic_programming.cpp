#include <cstdio>
#include <iostream>

using namespace std;

class binomial_coefficient {
private:
	int size;
	int** B;

public:
	binomial_coefficient(int num) : size(num) {
		B = new int*[size];
		for (int i = 0; i < size; i++) {
			B[i] = new int[size];
			for (int j = 0; j < size; j++) {
				B[i][j] = -1;
			}
		}
	}

	~binomial_coefficient() {
		for (int i = 0; i < size; i++) {
			delete[] B[i];
		}
		delete[] B;
	}

	int recursive_binomial(int n, int k) {
		if (k == 0 || k == n) {
			return 1;
		}
		else {
			return recursive_binomial(n - 1, k - 1) + recursive_binomial(n - 1, k);
		}
	}

	int bottom_up_binomial(int n, int k) {
		int min;
		for (int i = 0; i < n; i++) {
			min = (i < k ? i : k);
			for (int j = 0; j < min; j++) {
				if (j == 0 || j == i) {
					B[i][j] = 1;
				}
				else {
					B[i][j] = B[i - 1][j - 1] + B[i - 1][j];
				}
			}
		}
		return B[n][k];
	}
};

class floyd_shortest_path {
private:
	const int inf = 999;
	int content_size = 5;

	int W[6][6] = {
		{inf, inf, inf, inf, inf, inf},
		{inf, 0, 1, inf, 1, 5 },
		{inf, 9, 0, 3, 2, inf},
		{inf, inf, inf, 0, 4, inf},
		{inf, inf, inf, 2, 0, 3},
		{inf, 3, inf, inf, inf, 0}
	};
	int D_rec[6][6];
	int D[6][6];
	int P_rec[6][6];
	int P[6][6];

public:
	void setting() {
		for (int i = 0; i <= content_size; i++) {
			for (int j = 0; j <= content_size; j++) {
				D[i][j] = W[i][j];
				D_rec[i][j] = W[i][j];
				P[i][j] = 0;
				P_rec[i][j] = 0;
			}
		}
	}

	void print_path(int q, int r) {
		cout << "v" << q << "-> ";
		print_path_inside(q, r);
		cout << "v" << r << endl;
		cout << "Total Distance: " << D[q][r] << endl;
	}

	void print_path_inside(int q, int r) {
		if (P[q][r] != 0) {
			print_path_inside(q, P[q][r]);
			cout << 'v' << P[q][r] << "-> ";
			print_path_inside(P[q][r], r);
		}
	}

	//D(k)[i, j] 는 k를 거쳐 i에서 j로 도달 (k가 0이면 바로 도달)
	//D(k)[i, j] = min(D(k-1)[i, j] , D(k-1)[i, k] + D(k-1)[k, j])
	void recursive_floyd(int k) {
		if (k > 1) {
			recursive_floyd(k - 1);
		}

		for (int i = 1; i <= content_size; i++) {
			for (int j = 1; j <= content_size; j++) {
				if (D_rec[i][j] > D_rec[i][k] + D_rec[k][j]) {
					P_rec[i][j] = k;
					D_rec[i][j] = D_rec[i][k] + D_rec[k][j];
				}
			}
		}
	}

	void bottom_up_floyd() {
		for (int k = 1; k <= content_size; k++) {
			for (int i = 1; i <= content_size; i++) {
				for (int j = 1; j <= content_size; j++) {
					if (D[i][j] > D[i][k] + D[k][j]) {
						P[i][j] = k;
						D[i][j] = D[i][k] + D[k][j];
					}
				}
			}
		}
	}

	void main() {
		setting();
		recursive_floyd(content_size);
		bottom_up_floyd();
		print_path(5, 3);
	}
};

class chained_matrix_multiplication {
private:
	const int content_size = 6;
	const int inf = 999;
	int d[7] = { 5, 2, 3, 4, 6, 7, 8 };
	int M[7][7];
	int K[7][7];

public:
	void initial_setting() {
		for (int i = 0; i <= content_size; i++) {
			for (int j = 0; j <= content_size; j++) {
				M[i][j] = 0;
				K[i][j] = 0;
			}
		}
	}

	void chained_calculation() {
		for (int k = 1; k <= content_size; k++) {
			for (int i = 1; i <= content_size; i++) {
				if (i + k <= content_size) {
					M[i][i + k] = get_min(i, i + k);
				}
			}
		}
	}

	int get_min(int i, int j) {
		int min = inf;
		for (int k = i; k < j; k++) {
			if (min > M[i][k] + M[k+1][j] + d[i - 1] * d[k] * d[j]) {
				min = M[i][k] + M[k+1][j] + d[i - 1] * d[k] * d[j];
				K[i][j] = k;
			}
		}
		return min;
	}

	void print_order(int i, int j) {
		if (i == j) cout << i;
		else {
			cout << "(";
			print_order(i, K[i][j]);
			print_order(K[i][j] + 1, j);
			cout << ")";
		}
	}

	void main() {
		initial_setting();
		chained_calculation();
		for (int i = 1; i <= content_size; i++) {
			for (int j = 1; j <= content_size; j++) {
				cout << M[i][j] << "(" << K[i][j] << ")" <<  "\t" ;
			}
			cout << endl;
		}
		print_order(1, content_size);
	}
};

int main() {
	chained_matrix_multiplication fsp = chained_matrix_multiplication();
	fsp.main();
	return 0;
}