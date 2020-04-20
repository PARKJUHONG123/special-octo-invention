#include <cstdio>
#include <iostream>

using namespace std;

class sort {
private:
	struct data {
		int key;
		data* link;
	};

	int n;
	int* S;
	data* root;

	void print_S() {
		for (int i = 1; i <= n; i++) {
			cout << S[i] << " ";
		}
		cout << endl;
	}

	void exchange(int* a, int* b) {
		int temp = -1;
		temp = *a;
		*a = *b;
		*b = temp;
	}
	
	void copyArray(int* from, int* to, int n) {
		for (int i = 1; i <= n; i++) {
			to[i] = from[i];
		}
	}

public:
	sort() {
		FILE* in = NULL;
		fopen_s(&in, "input_file\\sort_input.txt", "r");
		if (in == NULL) {
			cout << "file open error";
			exit(1);
		}
		fscanf_s(in, "%d", &n);
		S = new int[n + 1];

		for (int i = 1; i <= n; i++) {
			fscanf_s(in, "%d", &S[i]);
		}

		root = new data;
		root->key = -1;
		root->link = nullptr;
		data* before = root;

		for (int i = 1; i <= n; i++) {
			data* temp = new data;
			temp->key = S[i];
			temp->link = nullptr;
			before->link = temp;
			before = temp;
		}
	}

	void insertion() { 
		// O(n^2), Stable, On-line, In-place
		// Worst T.C = n(n-1) / 2, Avg T.C = n^2 / 4
		int temp = -1;
		int j = -1;

		for (int i = 2; i <= n; i++) {
			temp = S[i];
			j = i - 1;
			while (j > 0 && S[j] > temp) {
				S[j + 1] = S[j];
				j--;
			}
			S[j + 1] = temp;
			cout << "Phase " << i << " : ";
			print_S();
     	}
	}

	void selection() { 
		// O(n^2), Stable, On-line, In-place
		// Every-case T.C = n(n-1) / 2
		int smallest = -1;
		for (int i = 1; i <= n - 1; i++) {
			smallest = i;

			for (int j = i + 1; j <= n; j++) {
				if (S[j] < S[smallest]) {
					smallest = j;
				}
			}

			exchange(&S[i], &S[smallest]);
			cout << "Phase " << i << " : ";
			print_S();
		}
	}

	int min(int a, int b) {
		return (a > b) ? b : a;
	}

	void merge_iterative_function(int* unsorted, int *sorted, int iLeft, int iRight, int iEnd) {
		int i = iLeft, j = iRight;
		int index = iLeft;
		while (i < iRight && j < iEnd) {
			if (unsorted[i] < unsorted[j]) {
				sorted[index++] = unsorted[i++];
			}
			else {
				sorted[index++] = unsorted[j++];
			}
		}

		while (i < iRight) {
			sorted[index++] = unsorted[i++];
		}
		while (j < iEnd) {
			sorted[index++] = unsorted[j++];
		}
	}

	void merge_iterative() {
		int* sorted = new int[n + 1];
		for (int width = 1; width <= n; width = 2 * width) {
			for (int i = 1; i <= n; i = i + 2 * width) {
				merge_iterative_function(S, sorted, i, min(i + width, n + 1), min(i + 2 * width, n + 1));
			}

			copyArray(sorted, S, n);
			print_S();
		}
		delete[] sorted;
	}

	void merge_linked() {
		
	}

	void partition(int low, int high, int* pivot_point) {
		int pivot_item = S[low];
		int low_temp = low;

		for (int i = low + 1; i <= high; i++) {
			// i 와 low_temp 와 교환
			if (S[i] < pivot_item) {
				low_temp++;
				exchange(&S[low_temp], &S[i]);
			}
			*pivot_point = low_temp;
			exchange(&S[low], &S[*pivot_point]);
		}
	}

	void quick_function(int low, int high) {
		int pivot_point = -1;
		if (low < high) {
			partition(low, high, &pivot_point);
			quick_function(low, pivot_point);
			quick_function(pivot_point + 1, high);
		}
	}

	void quick() {
		// not stable
		quick_function(1, n);
		print_S();
	}


	void heap() {

	}

	void count() {

	}

	void radix() {

	}
};

int main() {
	sort temp = sort();
	temp.quick();
	return 0;
}