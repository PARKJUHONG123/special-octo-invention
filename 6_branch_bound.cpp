#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

class knapsack_branch_bound_pruning {
private:
	struct product {
		int level; // level
		int w; //weight
		int p; //profit
		int p_w; //profit per weight
	};
	product* prod;
	queue<product> Q;
	int n, W; 
	int max_profit = 0;

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
		queue<product> Q;
		product v;
		v.level = v.p = v.w = 0;
		max_profit = 0;
		Q.push(v);

		while (!Q.empty() && v.level < n) {
			v = Q.front();
			Q.pop();
			product u;
			u.level = v.level + 1;
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

int main() {
	knapsack_branch_bound_pruning temp = knapsack_branch_bound_pruning();
	temp.knapsack_function();
	return 0;
}