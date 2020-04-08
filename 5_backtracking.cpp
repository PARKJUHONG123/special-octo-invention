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
	bool print_out = false;

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
				// 가로와 세로의 길이가 같다 = 대각선 상에 있다
				// 세로 상에 같은 값이 있다 = 세로 상에 있다
				flag = false;
			k++;
		}
		return flag;
	}

	void queens(int i, int* col, int n) {
		int j = 1; //index
		if (print_out == true) return;

		if (promising(i, col) == true) {
			if (i == n) { // 가득 차면 모두 프린트한다
				for (j = 1; j <= n; j++) {
					printf("%d ", col[j]);
				}
				printf("\n");
				print_out = true;
				return;
			}
			else {
				for (j = 1; j <= n; j++) { // 그 다음 COL에 하나씩 값을 넣어보고 있으면 그 줄기를 이어서 간다
					col[i + 1] = j;
					queens(i + 1, col, n);
				}
			}
		}

		// 61번 줄에서 return 을 하기 때문에 최종 루트들은 wrong_path 에서 출력되지 않음
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
	bool print_out = false;

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
		if (print_out == true) return;

		if (promising(i, col)) {
			if (i == n) {
				for (int k = 1; k <= i; k++) {
					cout << col[k] << " ";
				}
				cout << endl;
				print_out = true;
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
		int count = 0, temp = 1, num = 0, j = 0;
		if (n <= 5) {
			queens(0, col, n);
		}
		else {
			while (1) {
				count = 0; //첫번 째 줄부터 시작
				while (count <= n - 5 && temp != 0) {			// 아래 과정을 n-5 번까지만 (즉 5줄이 남게) 하고, 남은 퀸의 갯수가 0이 아닌 동안 반복
					temp = n; // 퀸이 들어갈 수 있는 남은 자리

					/*
					0 1 2 3 4 5 6 7
					1 O O O O X O O
					2
					3
					4
					5
					6
					7					
					일 경우 2번째 줄에서 4, 5, 6만을 제외하면 모든 곳에 퀸이 있을 수 있기 때문에
					CHECK[5] 와 CHECK[5-1] 와 CHECK[5+1] 을 활성화시킨다.
					

					0 1 2 3 4 5 6 7
					1 O O O O X O O
					2 X O O O O O O
					3
					4
					5
					6
					7
					일 경우 3번째 줄에서 1, 2 그리고 3, 5, 7만을 제외하면 모든 곳에 퀸이 있을 수 있기 때문에
					CHECK[1] 과 CHECK[1+1] (CHECK[1-1] 은 범위에서 벗어나기에 제외) 그리고 CHECK[5] 와 CHECK[5-2], CHECK[5+2] 을 활성화시킨다.
					*/


					for (int i = 1; i <= count; i++) {
						if (check[col[i]] != 1) { // 퀸을 배치하고 그 지역은 이제 차지되었음
							check[col[i]] = 1;
							temp--;
						}
						if ((count + 1) - i < col[i] && check[col[i] - ((count + 1) - i)] != 1) { // 지금 배치한 퀸의 왼쪽이 남을 때
							check[col[i] - ((count + 1) - i)] = 1;
							temp--;
						}
						if ((count + 1) - i + col[i] <= n && check[col[i] + ((count + 1) - i)] != 1) { // 지금 배치한 퀸의 오른쪽이 남을 때
							check[col[i] + ((count + 1) - i)] = 1;
							temp--;
						}
					}

					// 다음 줄에서 퀸이 들어갈 수 있는 남은 자리가 없으므로 = 실패한 형태
					if (temp == 0) {
						break;
					}

					// 랜덤하게 생성한 값 (1 ~ temp)
					num = rand() % temp + 1; 

					// 만약에 랜덤한게 생성한 값이 이미 다른 퀸들에 의해 영향을 받는 곳이라면, 
					if (check[num] == 1) {
						for (j = 1; j <= n; j++) {

							/*
							check[4, 5, 6] = 1 일 때, temp 는 4이므로 num 은 1에서 4 사이
							0 1 2 3 4 5 6 7
							1 O O O O X O O
							2 O O O T T T O
							3
							4
							5
							6
							7
							
							(num = 4 로 시작)
							j = 1	num = 3
							j = 2	num = 2
							j = 3	num = 1
							j = 4	num = 1
							j = 5	num = 1
							j = 6	num = 1
							j = 7	num = 0

							결국에는 col[count + 1] = 7 가 들어가게 된다
							즉 num 이 1, 2, 3 일 때는 if (check[num] == 1) 문을 거치지 않고 바로 등록 가능하고,
							num 이 4 일 때는 if 문을 거쳐서 남은 공간에 할당 가능하다.


							check[2, 3, 4] = 1 일 때, temp 는 4이므로 num 은 1에서 4 사이
							0 1 2 3 4 5 6 7
							1 O O X O O O O
							2 O T T T O O O
							3
							4
							5
							6
							7

							(num = 4 로 시작)
							j = 1	num = 3
							j = 2	num = 3
							j = 3	num = 3
							j = 4	num = 3
							j = 5	num = 2
							j = 6	num = 1
							j = 7	num = 0
							col[count + 1] = 7
							
							(num = 3 로 시작)
							j = 1	num = 2
							j = 2	num = 2
							j = 3	num = 2
							j = 4	num = 2
							j = 5	num = 1
							j = 6	num = 0
							j = 7	...
							col[count + 1] = 6

							(num = 2 로 시작)
							j = 1	num = 1
							j = 2	num = 1
							j = 3	num = 1
							j = 4	num = 1
							j = 5	num = 0
							j = 6	...
							j = 7	...
							col[count + 1] = 5
							
							즉 num = 1, 2, 3, 4 일 때 차례대로 크기에 따라 남은 공간에 할당이 된다.

							*/

							if (num == 0) break;
							// 만약에 j 가 이미 다른 퀸들에 의해 영향을 받는 곳이라면, num 값은 유지된다
							// 만약에 j 가 괜찮은 곳이라면, num 값은 1 줄어든다.
							if (check[j] == 1) num++;
							num--;
						}
						// 다음 줄 (count + 1) 에 j - 1 값을 넣는다.
						col[count + 1] = j - 1;
					}
					// 만약에 랜덤하게 생성한 값이 괜찮은 곳이라면, 다음 줄 (count + 1) 에 그 랜덤값을 넣는다
					else {
						col[count + 1] = num;
					}

					// 다음 줄에서 퀸이 있을 수 있을 수 있는 자리를 찾기 위해 다시 CHECK 를 초기화
					for (int i = 1; i <= n; i++) {
						check[i] = 0;
					}

					//count + 1 줄의 queen의 배치가 끝났음
					count++;
				}

				// 실패한 경우, 모든 값을 RESET 하여 처음부터 다시 시작
				if (temp == 0) { 
					for (int i = 1; i <= n; i++)
						check[i] = 0;
					temp = n;
					continue;
				}
				// n개 중에서 5개빼고
				queens(count - 1, col, n);
				if (print_out == true) {
					break;
				}
			}
		}
	}
};

class sum_of_subsets {
private:
	int n = -1, W = -1, weight = 0, total = 0;
	int* w = nullptr;
	bool* include = nullptr;

public:
	sum_of_subsets() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\subsets_input.txt", "r");

		if (in == NULL) {
			printf("file open error\n");
			exit(1);
		}
		fscanf_s(in, "%d %d", &n, &W);
		w = new int[n + 1];
		include = new bool[n + 1];

		for (int i = 1; i <= n; i++) {
			fscanf_s(in, "%d", &w[i]);
			total += w[i];
			include[i] = false;
		}
		fclose(in);
		sort(w, n);

	}

	~sum_of_subsets() {
		delete[]w;
	}

	void sort(int* w, int n) {
		int temp = -1;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (w[i] > w[j]) {
					temp = w[i];
					w[i] = w[j];
					w[j] = temp;
				}
			}
		}
	}

	bool promising(int i, int weight, int total) {
		return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
	}

	void sum_subsets(int i, int weight, int total) {
		if (promising(i, weight, total)) {
			if (weight == W) {
				cout << "{ ";
				for (int j = 1; j <= n; j++) {
					if (include[j]) cout << w[j] << " ";
				}
				cout << "}" << endl;
			}
			else {
				include[i + 1] = true;
				sum_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
				include[i + 1] = false;
				sum_subsets(i + 1, weight, total - w[i + 1]);
			}
		}
	}

	void main() {
		sum_subsets(0, weight, total);
	}

};

class graph_coloring {
private:
	int** W = nullptr;
	int* vcolor = nullptr;
	int n = -1;

public:
	graph_coloring() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\graph_coloring_input.txt", "r");
		if (in == NULL) {
			cout << "file open error";
			exit(1);
		}
		fscanf_s(in, "%d", &n);

		W = new int* [n + 1];
		vcolor = new int[n + 1];
		for (int i = 0; i <= n; i++) {
			W[i] = new int[n + 1];
			vcolor[i] = 0;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fscanf_s(in, "%d", &W[i][j]);
			}
		}

		fclose(in);
	}

	~graph_coloring() {
		for (int i = 0; i <= n; i++) {
			delete[] W[i];
		}
		delete[] W;
	}

	bool promising(int i) {
		int j = 1;
		bool result = true;
		while (j < i) {
			if (W[i][j] != 0 && vcolor[i] == vcolor[j]) {
				result = false;
			}
			j++;
		}
		return result;
	}

	void m_coloring(int i) {
		if (promising(i)) {
			if (i == n) {
				for (int j = 1; j <= n; j++) {
					cout << vcolor[j] << " ";
				}
				cout << endl;
			}
			else {
				for (int color = 1; color <= n; color++) {
					vcolor[i + 1] = color;
					m_coloring(i + 1);
				}
			}
		}
	}

	void main() {
		m_coloring(0);
	}
};

class hamilton_circuits_with_dyanmic_programming {
private:
	int** W;
	int* index_vertex;
	int n = -1;

public:
	hamilton_circuits_with_dyanmic_programming() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\hamilton_input.txt", "r");
		if (in == NULL) {
			cout << "file open error";
			exit(1);
		}
		fscanf_s(in, "%d", &n);

		W = new int* [n + 1];
		index_vertex = new int[n + 1];
		for (int i = 0; i <= n; i++) {
			W[i] = new int[n + 1];
			index_vertex[i] = 0;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fscanf_s(in, "%d", &W[i][j]);
			}
		}
	}

	~hamilton_circuits_with_dyanmic_programming() {
		delete[]index_vertex;
		for (int i = 0; i <= n; i++) {
			delete[]W[i];
		}
		delete[]W;
	}

	bool promising(int i) {
		bool result = true;
		if (i == n && W[index_vertex[n]][index_vertex[1]] == 0) {
			result = false;
		}
		else if (i > 1 && W[index_vertex[i - 1]][index_vertex[i]] == 0) {
			result = false;
		}
		else {
			int j = 1;
			while (j < i && result) {
				if (index_vertex[i] == index_vertex[j]) {
					result = false;
				}
				j++;
			}
		}
		return result;
	}

	void hamilton(int i) {
		if (promising(i)) {
			if (i == n) {
				for (int j = 1; j <= n; j++) {
					cout << index_vertex[j] << " ";
				}
				cout << endl;
			}
			else {
				for (int j = 1; j <= n; j++) {
					index_vertex[i + 1] = j;
					hamilton(i + 1);
				}
			}
		}
	}

	void main() {
		hamilton(0);
	}
};

class knapsack{
private:
	struct product {
		int w; //weight
		int p; //profit
		int p_w; //profit per weight
	};
	product* prod;
	int n;
	int W;
	bool* include, *bestset;

	int numbest = 0, maxprofit = 0;
	int bound = 0, total_weight = 0;

public:
	knapsack() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\knapsack_input.txt", "r");
		if (in == NULL) {
			cout << "file open error";
			exit(1);
		}
		fscanf_s(in, "%d %d", &n, &W);
		prod = new product[n + 1];
		include = new bool[n + 1];
		
		for (int i = 1; i <= n; i++) {
			fscanf_s(in, "%d", &(prod[i].p));
			include[i] = false;
		}

		for (int i = 1; i <= n; i++) {
			fscanf_s(in, "%d", &(prod[i].w));
			prod[i].p_w = prod[i].p / prod[i].w;
		}

		fclose(in);
		sort();
	}

	~knapsack() {
		delete[]prod;
	}

	void sort() {
		product temp;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (prod[i].p_w < prod[j].p_w) {
					temp = prod[i];
					prod[i] = prod[j];
					prod[j] = temp;
				}
			}
		}
	}

	bool promising(int i, int profit, int weight) {
		bool result = true;
		int j = 1;

		if (weight >= W) {
			result = false;
		}
		else {
			j = i + 1;
			bound = profit;
			total_weight = weight;

			while (j <= n && total_weight + prod[j].w <= W) {
				total_weight = total_weight + prod[j].w;
				bound = bound + prod[j].p;
				j++;
			}
			int k = j;

			if (k <= n) {
				bound += (W - total_weight) * prod[k].p_w;
				result = (bound > maxprofit ? true : false);
			}
		}
		return result;
	}

	void knapsack_function(int i, int profit, int weight) {
		if (weight <= W && profit > maxprofit) {
			maxprofit = profit;
			numbest = i;
			bestset = include;
		}

		if (promising(i, profit, weight)) {
			include[i + 1] = true;
			knapsack_function(i + 1, profit + prod[i + 1].p, weight + prod[i + 1].w);

			include[i + 1] = false;
			knapsack_function(i + 1, profit, weight);
		}
	}

	void main() {
		knapsack_function(0, 0, 0);
		cout << maxprofit << endl;
	}
};


int main() {
	knapsack test = knapsack();
	test.main();
	return 0;
}