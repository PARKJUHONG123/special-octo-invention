//DFS
//n-queens Problem
//Sum-of-subsets Problem
//Graph Coloring
//Hamilton Circuits Problem
//0/1 Knapsack Problem

#include <cstdio>
#include <iostream>
#include <ctime>

using namespace std;

class n_queens_dynamic {
private:
	int n = -1;
	int* col = nullptr;

public:
	n_queens_dynamic() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\nqueens_input.txt", "r");
		if (in == NULL) {
			printf("file open error");
			exit(0);
		}
		fscanf_s(in, "%d", &n);
		fclose(in);

		col = new int[n + 1];
		for (int i = 0; i <= n; i++) {
			col[i] = 0;
		}
	}

	~n_queens_dynamic() {
		delete[]col;
	}

	void wrong_path(int i, int* col) {
		printf("Blocked Path : ");
		for (int k = 1; k <= i; k++) {
			printf("%d ", col[k]);
		}
		printf("\n");
	}

	bool promising(int i, int* col) {
		int k = 1;
		bool flag = true;
		while (k < i && flag) {
			if (col[i] == col[k] || abs(col[i] - col[k]) == abs(i - k))
				// ���ο� ������ ���̰� ���� = �밢�� �� �ִ�
				// ���� �� ���� ���� �ִ� = ���� �� �ִ�
				flag = false;
			k++;
		}
		return flag;
	}

	void queens(int i, int* col, int n) {
		int j = 1; //index
		if (promising(i, col) == true) {
			if (i == n) { // ���� ���� ��� ����Ʈ�Ѵ�
				for (j = 1; j <= n; j++) {
					printf("%d ", col[j]);
				}
				printf("\n");
				return;
			}
			else {
				for (j = 1; j <= n; j++) { // �� ���� COL�� �ϳ��� ���� �־�� ������ �� �ٱ⸦ �̾ ����
					col[i + 1] = j;
					queens(i + 1, col, n);
				}
			}
		}

		// 61�� �ٿ��� return �� �ϱ� ������ ���� ��Ʈ���� wrong_path ���� ��µ��� ����
		//wrong_path(i, col);
	}

	void main() {
		queens(0, col, n);
	}
};

class n_queens_monte_carlo {
private:
	int n = -1;
	int* col = nullptr;
	bool* check = nullptr;

public:
	n_queens_monte_carlo() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\nqueens_input.txt", "r");
		if (in == NULL) {
			cout << "file open error";
			exit(0);
		}
		fscanf_s(in, "%d", &n);
		fclose(in);

		col = new int[n + 1];
		check = new bool[n + 1];
		srand(time(NULL)); 

		for (int i = 0; i <= n; i++) {
			col[i] = 0;
			check[i] = false;
		}
	}

	~n_queens_monte_carlo() {
		delete[]col;
		delete[]check;
	}

	bool promising(int i, int* col) {
		bool flag = true;
		int k = 1;
		while (k < i && flag){
			if (col[i] == col[k] || abs(col[i] - col[k]) == abs(i - k)) {
				flag = false;
			}
			k++;
		}
		return flag;
	}

	void queens(int i, int* col, int n) {
		if (promising(i, col)) {
			if (i == n) {
				for (int k = 1; k <= i; k++) {
					cout << col[k] << " ";
				}
				cout << endl;
				exit(1);
			}
			else {
				for (int j = 1; j <= n; j++){
					col[i + 1] = j;
					queens(i + 1, col, n);
				}
			}
		}
	}

	void main() {
//		int count_col = 0, left_queen = 1;
		int count = 0, temp = 1, num = 0, j = 0;
		if (n <= 5) {
			queens(0, col, n);
		}
		else {
			while (1) {
				count = 0; //ù�� ° �ٺ��� ����
				while (count <= n - 5 && temp != 0) {			// �Ʒ� ������ n-5 �������� (�� 5���� ����) �ϰ�, ���� ���� ������ 0�� �ƴ� ���� �ݺ�
					temp = n; // ���� ���� ����

					for (int i = 1; i <= count; i++) {
						if (check[col[i]] != 1) { // ���� ��ġ�ϰ� �� ������ ���� �����Ǿ���
							check[col[i]] = 1;
							temp--;
						}
						if ((count + 1) - i < col[i] && check[col[i] - ((count + 1) - i)] != 1) { // ���� ��ġ�� ���� ������ ���� ��
							check[col[i] - ((count + 1) - i)] = 1;
							temp--;
						}
						if ((count + 1) - i + col[i] <= n && check[col[i] + ((count + 1) - i)] != 1) { // ���� ��ġ�� ���� �������� ���� ��
							check[col[i] + ((count + 1) - i)] = 1;
							temp--;
						}
						for (int i = 1; i <= n; i++) {
							cout << col[i] << " ";
						}
						cout << endl;
					}

					if (temp == 0)
						break;
					num = rand() % temp + 1;				//make random number
					if (check[num] == 1) {
						for (j = 1; j <= n; j++) {
							if (num == 0) break;
							if (check[j] == 1) num++;
							num--;
						}
						col[count + 1] = j - 1;
					}
					else col[count + 1] = num;
					for (int i = 1; i <= n; i++)
						check[i] = 0;
					count++; //count ���� queen�� ��ġ�� ������
				}
				if (temp == 0) { // ������ ���
					for (int i = 1; i <= n; i++)
						check[i] = 0;
					temp = n;
					continue;
				}

				queens(count - 1, col, n); 			//n�� �߿��� 5������


			}
			/*
			while (1) {
				count_col = 0;
				while (count_col <= n - 5 && left_queen != 0) {
					left_queen = n;
					for (int i = 1; i <= count_col; i++) {
						if (check[col[i]] != true) {
							check[col[i]] = true;
							left_queen--;
						}
						if ((count_col + 1) - i < col[i] && check[col[i] - ((count_col + 1) - i)] != true)
					}



				}
				if (left_queen == 0) {
					for (int i = 1; i <= n; i++) {
						check[i] = 0;
					}
					left_queen = n;
					continue;
				}
				queens(count_col - 1, col, n);
			}
			*/
		}
	}
};

class sum_of_subsets {

};

class graph_coloring {

};

class hamilton_circuits {

};

class knapsack{

};

int main() {
	n_queens_dynamic test_1 = n_queens_dynamic();
	n_queens_monte_carlo test_2 = n_queens_monte_carlo();
	clock_t start_d, end_d,	start_m, end_m;

	start_d = clock();
	test_1.main();
	end_d = clock();
	start_m = clock();
	test_2.main();
	end_m = clock();

	cout << "n_queens_dynamic : ";
	printf("%f\n", (double)(end_d - start_d));
	cout << "n_queens_monte_carlo : ";
	printf("%f", (double)(end_m - start_m));

	return 0;
}