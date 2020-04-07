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
					temp = n; // ���� �� �� �ִ� ���� �ڸ�

					/*
					0 1 2 3 4 5 6 7
					1 O O O O X O O
					2
					3
					4
					5
					6
					7					
					�� ��� 2��° �ٿ��� 4, 5, 6���� �����ϸ� ��� ���� ���� ���� �� �ֱ� ������
					CHECK[5] �� CHECK[5-1] �� CHECK[5+1] �� Ȱ��ȭ��Ų��.
					

					0 1 2 3 4 5 6 7
					1 O O O O X O O
					2 X O O O O O O
					3
					4
					5
					6
					7
					�� ��� 3��° �ٿ��� 1, 2 �׸��� 3, 5, 7���� �����ϸ� ��� ���� ���� ���� �� �ֱ� ������
					CHECK[1] �� CHECK[1+1] (CHECK[1-1] �� �������� ����⿡ ����) �׸��� CHECK[5] �� CHECK[5-2], CHECK[5+2] �� Ȱ��ȭ��Ų��.
					*/


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
					}

					// ���� �ٿ��� ���� �� �� �ִ� ���� �ڸ��� �����Ƿ� = ������ ����
					if (temp == 0) {
						break;
					}

					// �����ϰ� ������ �� (1 ~ temp)
					num = rand() % temp + 1; 

					// ���࿡ �����Ѱ� ������ ���� �̹� �ٸ� ���鿡 ���� ������ �޴� ���̶��, 
					if (check[num] == 1) {
						for (j = 1; j <= n; j++) {

							/*
							check[4, 5, 6] = 1 �� ��, temp �� 4�̹Ƿ� num �� 1���� 4 ����
							0 1 2 3 4 5 6 7
							1 O O O O X O O
							2 O O O T T T O
							3
							4
							5
							6
							7
							
							(num = 4 �� ����)
							j = 1	num = 3
							j = 2	num = 2
							j = 3	num = 1
							j = 4	num = 1
							j = 5	num = 1
							j = 6	num = 1
							j = 7	num = 0

							�ᱹ���� col[count + 1] = 7 �� ���� �ȴ�
							�� num �� 1, 2, 3 �� ���� if (check[num] == 1) ���� ��ġ�� �ʰ� �ٷ� ��� �����ϰ�,
							num �� 4 �� ���� if ���� ���ļ� ���� ������ �Ҵ� �����ϴ�.


							check[2, 3, 4] = 1 �� ��, temp �� 4�̹Ƿ� num �� 1���� 4 ����
							0 1 2 3 4 5 6 7
							1 O O X O O O O
							2 O T T T O O O
							3
							4
							5
							6
							7

							(num = 4 �� ����)
							j = 1	num = 3
							j = 2	num = 3
							j = 3	num = 3
							j = 4	num = 3
							j = 5	num = 2
							j = 6	num = 1
							j = 7	num = 0
							col[count + 1] = 7
							
							(num = 3 �� ����)
							j = 1	num = 2
							j = 2	num = 2
							j = 3	num = 2
							j = 4	num = 2
							j = 5	num = 1
							j = 6	num = 0
							j = 7	...
							col[count + 1] = 6

							(num = 2 �� ����)
							j = 1	num = 1
							j = 2	num = 1
							j = 3	num = 1
							j = 4	num = 1
							j = 5	num = 0
							j = 6	...
							j = 7	...
							col[count + 1] = 5
							
							�� num = 1, 2, 3, 4 �� �� ���ʴ�� ũ�⿡ ���� ���� ������ �Ҵ��� �ȴ�.

							*/

							if (num == 0) break;
							// ���࿡ j �� �̹� �ٸ� ���鿡 ���� ������ �޴� ���̶��, num ���� �����ȴ�
							// ���࿡ j �� ������ ���̶��, num ���� 1 �پ���.
							if (check[j] == 1) num++;
							num--;
						}
						// ���� �� (count + 1) �� j - 1 ���� �ִ´�.
						col[count + 1] = j - 1;
					}
					// ���࿡ �����ϰ� ������ ���� ������ ���̶��, ���� �� (count + 1) �� �� �������� �ִ´�
					else {
						col[count + 1] = num;
					}

					// ���� �ٿ��� ���� ���� �� ���� �� �ִ� �ڸ��� ã�� ���� �ٽ� CHECK �� �ʱ�ȭ
					for (int i = 1; i <= n; i++) {
						check[i] = 0;
					}

					//count + 1 ���� queen�� ��ġ�� ������
					count++;
				}

				// ������ ���, ��� ���� RESET �Ͽ� ó������ �ٽ� ����
				if (temp == 0) { 
					for (int i = 1; i <= n; i++)
						check[i] = 0;
					temp = n;
					continue;
				}
				// n�� �߿��� 5������
				queens(count - 1, col, n); 			
			}
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