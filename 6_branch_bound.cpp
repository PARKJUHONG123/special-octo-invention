#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

class knapsack_branch_bound_pruning {
private:
	struct product {
		int w; //weight
		int p; //profit
		int p_w; //profit per weight		
		int level; // level
	};
	product* prod;
	queue<product> Q;
	int n, W; 

public:
	knapsack_branch_bound_pruning() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\knapsack_input.txt", "r");
		if (in == NULL) {
			cout << "file open error";
			exit(1);
		}
		fscanf_s(in, "%d %d", &n, &W);
		prod = new product[n + 1];

		for (int i = 1; i <= n; i++) {
			fscanf_s(in, "%d", &(prod[i].p));
		}

		for (int i = 1; i <= n; i++) {
			fscanf_s(in, "%d", &(prod[i].w));
			prod[i].p_w = prod[i].p / prod[i].w;
		}
		fclose(in);
		sort();

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

	void knapsack_function() {
		int max_profit = 0;
		queue<product> Q;
		product v;
		v.level = v.p = v.w = 0;
		Q.push(v);

		while (!Q.empty()) {
			v = Q.front();
			Q.pop();
			product u;
			u.level = v.level + 1;
			if (u.level <= n) {
				u.w = v.w + prod[u.level].w;
				u.p = v.p + prod[u.level].p;
				if (u.w <= W && u.p > max_profit) {
					max_profit = u.p;
				}
				if (bound(u) > max_profit) {
					Q.push(u);
				}
				u.w = v.w;
				u.p = v.p;
				if (bound(u) > max_profit) {
					Q.push(u);
				}
			}
		}
		printf("Best Profit : %d", max_profit);
	}

	int bound(product u) {
		int result = u.p;
		int in_count = 0, total_count = 0;
		for (int i = u.level + 1; i <= n; i++) {
			in_count = 0;
			while (prod[i].w != in_count) {
				result += prod[i].p_w;
				total_count++;
				in_count++;
				if (total_count == W - u.w) {
					return result;
				}
			}
		}
		return result;
	}
};

class TSP_approximation {
private:
	const int INF = 99999;
	int n = -1;
	int** V = nullptr;
	bool* VC = nullptr;

public:
	TSP_approximation() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\TSP_input.txt", "r");
		if (in == NULL) {
			printf("file open error");
			exit(1);
		}
		fscanf_s(in, "%d", &n);
		V = new int*[n + 1];
		VC = new bool[n + 1];

		for (int i = 1; i <= n; i++) {
			V[i] = new int[n + 1];
			VC[i] = false;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fscanf_s(in, "%d", &V[i][j]);
				if (V[i][j] == 0) {
					V[i][j] = INF;
				}
			}
		}
	}

	~TSP_approximation() {
		delete[] V;
		delete[] VC;
	}

	int bound() {
		int old_start = 1, start = 1, result = 0;
		for (int i = 1; i <= n; i++) {
			VC[start] = true;
			old_start = start;
			start = column_bound(V[start]);
			printf("%d -> %d : %d\n", old_start, start, V[old_start][start]);
			result += V[old_start][start];
		}
		return result;
	}

	int column_bound(int* VA) {
		int weight = INF;
		int index = 1;

		for (int i = 1; i <= n; i++) {
			if (VC[i] != true) {
				if (weight > VA[i]) {
					weight = VA[i];
					index = i;
				}
			}
		}
		return index;
	}

	void main() {
		printf("%d", bound());
	}
};

class TSP_branch_bound {
private:
	struct vertex {
		int bound = 0;
		int level = 0;
		int length = 0;
		queue<int> path;
	};

	const int INF = 99999;
	int n = -1;
	int min_length = INF;
	vertex** V = nullptr;
	queue<int> opt_tour;

public:
	TSP_branch_bound() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\TSP_input.txt", "r");
		if (in == NULL) {
			printf("file open error");
			exit(1);
		}
		fscanf_s(in, "%d", &n);

		V = new vertex * [n + 1];
		for (int i = 1; i <= n; i++) {
			V[i] = new vertex[n + 1];
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fscanf_s(in, "%d", &V[i][j].length);
				if (V[i][j].length == 0) {
					V[i][j].length = INF;
				}
			}
		}
	}

	~TSP_branch_bound() {
		delete[] V;
	}

	int bound(vertex u) {
		int result = 0, old_value = -1, value = -1, min_result = INF;;
		bool first = true;
		queue<int> temp;
		while (!u.path.empty()) {
			value = u.path.front();
			temp.push(value);
			if (!first) {
				result += V[old_value][value].length;
			}
			first = false;
			old_value = value;
			u.path.pop();
		}
		u.path = temp;
		
		int index = -1;
		for (int i = 1; i <= n; i++) {
			if (u.path.size() == 1 || !inside(u, i)) {
				for (int j = 1; j <= n; j++) {
					if (min_result > V[i][j].length) {
						min_result = V[i][j].length;
						index = j;
					}
				}
				result += min_result;
			}
			min_result = INF;
		}
		return result;
	}

	int length(vertex u) {
		int len = 0, old_value = -1, value = -1;
		bool first = true;
		queue<int> temp;
		while (!u.path.empty()) {
			value = u.path.front();
			temp.push(value);
			if (!first) {
				len += V[old_value][value].length;
			}
			first = false;
			old_value = value;
			u.path.pop();
		}
		u.path = temp;
		return len;
	}

	bool inside(vertex u, int i) {
		int value = -1;
		bool result = false;
		queue<int> temp;
		while (!u.path.empty()) {
			value = u.path.front();
			if (value == i) {
				result = true;
			}
			temp.push(value);
			u.path.pop();
		}
		return result;
	}

	int left_over(vertex u) {
		int value = -1, total = 0;
		queue<int> temp;

		for (int i = 1; i <= n; i++) {
			total += i;
		}

		while (!u.path.empty()) {
			value = u.path.front();
			temp.push(value);
			u.path.pop();
			total -= value;
		}
		return total;
	}

	void travel(){
		queue<vertex> Q;
		vertex v;
		v.level = 0;

		v.path.push(1);
		v.bound = bound(v);
		Q.push(v);

		while (!Q.empty()) {
			v = Q.front();
			Q.pop();
			if (v.bound < min_length) {
				vertex u;
				u.level = v.level + 1;
				if (u.level == n - 1) {
					u.path = v.path;
					
					u.path.push(left_over(u));
					u.path.push(1);
					if (length(u) < min_length) {
						min_length = length(u);
						opt_tour = u.path;
					}
				}
				else {
					for (int i = 2; i <= n; i++) {
						if (!inside(v, i)) {
							u.path = v.path;
							u.path.push(i);
							u.bound = bound(u);
							if (u.bound < min_length) {
								Q.push(u);
							}
						}
					}
				}
			}
		}
		cout << "Minimum Length : " << min_length << endl << "Optimal Route : ";
		while(!opt_tour.empty()) {
			cout << opt_tour.front();
			opt_tour.pop();
			if (!opt_tour.empty()) {
				cout << " -> ";
			}
		}
	}
};

int main() {
	TSP_branch_bound temp = TSP_branch_bound();
	temp.travel();
	return 0;
}