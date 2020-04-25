#include <cstdio>
#include <iostream>
#include <ctime>
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

	// low ~ pivot_point 까지 정렬을 해보자
	// 하지만 pivot_point 는 처음 정하지 않는다.
	// 먼저 해당 범위에 있는 값 중 맨 앞에 위치한 값을 선택한 다음에 
	// 그 값보다 작은 것들은 앞으로 보내기 위해 자릴 바꿔줘야 한다.
	// pivot_point 보다 아래에 있는 값들은 정렬된 상태로 출력된다

	void partition(int low, int high, int* pivot_point) {
		int pivot_item = S[low];
		int j = low;
		
		for (int i = low + 1; i <= high; i++) {
			// i <-> j++ 와 교환
			if (S[i] < pivot_item) {
				j++;
				exchange(&S[j], &S[i]);
			}

			*pivot_point = j;
			// j <-> low 교환
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

	void rand_partition(int low, int high, int* pivot_point) {
		int i = rand() % (high - low + 1) + low;
		exchange(&S[low], &S[i]);
		partition(low, high, pivot_point);
	}

	void quick_rand_function(int low, int high) {
		int pivot_point = -1;
		if (low < high) {
			rand_partition(low, high, &pivot_point);
			quick_rand_function(low, pivot_point);
			quick_rand_function(pivot_point + 1, high);
		}
	}

	void quick() {
		// not stable
		// in-place
		char answer = 0;
		cout << "random? (y/n) : ";
		cin >> answer;
		if (answer == 'y') {
			srand(time(NULL));
			quick_rand_function(1, n);
		}
		else {
			quick_function(1, n);
		}
		print_S();
	}

	void add_heap_func(int index, int* heap_S) {
		int temp_value = -1, temp_index = index;

		while (temp_index / 2 > 0) {
			if (heap_S[temp_index / 2] < heap_S[temp_index]) {
				temp_value = heap_S[temp_index];
				heap_S[temp_index] = heap_S[temp_index / 2];
				heap_S[temp_index / 2] = temp_value;
			}
			temp_index = temp_index / 2;
		}
	}

	void add_heap(int index, int* heap_S, int value) {
		heap_S[index] = value;
		add_heap_func(index, heap_S);
	}

	int big_value_index(int *heap_S, int a, int b) {
		if (heap_S[a] > heap_S[b]) {
			return a;
		}
		else {
			return b;
		}
	}

	void del_heap_func(int index, int *heap_S) {
		int temp_index = 1, big_index = -1;
		while (2 * temp_index <= index) {
			if (2 * temp_index + 1 <= index) { //자식이 두개 있을 때
				big_index = big_value_index(heap_S, 2 * temp_index, 2 * temp_index + 1);
			}
			else { //자식이 하나밖에 없음
				big_index = 2 * temp_index;
			}

			if (heap_S[big_index] > heap_S[temp_index]) {
				exchange(&heap_S[big_index], &heap_S[temp_index]);
			}
			temp_index = big_index;
		}
	}

	void del_heap(int index, int* heap_S) {
		cout << heap_S[1] << " ";
		exchange(&heap_S[1], &heap_S[index]);
		if (index > 1) {
			del_heap_func(index - 1, heap_S);
		}
	}

	void heap() {
		// not stable
		// in-place
		int* heap_S = new int[n + 1];

		for (int i = 1; i <= n; i++) {
			add_heap(i, heap_S, S[i]);
		}

		for (int i = n; i >= 1; i--) {
			del_heap(i, heap_S);
		}
	}

	int get_max_value() {
		int result = S[1];
		for (int i = 1; i <= n; i++) {
			if (result < S[i]) {
				result = S[i];
			}
		}
		return result;
	}

	void count() {
		// O(n + k)
		// 뒤에서부터 loop 를 돌면 stable, 앞에서부터 돌면 unstable

		int k = get_max_value();
		int* result = new int[n + 1];
		int* count = new int[k + 1];

		for (int i = 1; i <= k; i++) {
			count[i] = 0;
		}

		for (int j = 1; j <= n; j++) {
			count[S[j]]++;
		}

		for (int i = 2; i <= k; i++) {
			count[i] += count[i - 1];
		}

		/*
			stability 를 위해서 뒤에서부터 loop 를 시작한다
			예를 들어 1(1), 3, 6, 4, 1(2) 를 sort 할 때

			# stable 한 sort
			: 1(1), 1(2), 3, 4, 6	

			# unstable 한 sort :
			: 1(2), 1(1), 3, 4, 6
		*/

		for (int j = n; j >= 1; j--) {
			result[count[S[j]]--] = S[j];
		}

		for (int i = 1; i <= n; i++) {
			cout << result[i] << " ";
		}
	}

	int get_max_size() {
		int value = get_max_value();
		int digit = 1, count = 0;
		while (1) {
			if (value / digit != 0) {
				digit = digit * 10;
				count = count + 1;
			}
			else {
				break;
			}
		}
		return count;
	}

	int get_digit_value(int m, int origin) {
		int digit = 1, result = -1;
		for (int i = 1; i < m; i++) {
			digit *= 10;
		}

		result = (origin % (digit * 10)) - (origin % (digit));
		return result / digit ;
	}


	void radix() {
		// O(d(n + k))
		int d = get_max_size(); // d == 1 : 1의자리, d == 2 : 10의 자리
		int k = 10;
		int* result = new int[n + 1];
		int* count = new int[k + 1];

		for (int m = 1; m <= d; m++) {
			for (int i = 0; i <= k; i++) {
				count[i] = 0;
			}

			for (int j = 1; j <= n; j++) {
				count[get_digit_value(m, S[j])]++;
			}

			for (int i = 1; i <= k; i++) {
				count[i] += count[i - 1];
			}

			for (int j = n; j >= 1; j--) {
				int temp = get_digit_value(m, S[j]);
				result[count[temp]--] = S[j];
			}

			for (int i = 1; i <= n; i++) {
				S[i] = result[i];
			}
		}
		for (int i = 1; i <= n; i++) {
			cout << result[i] << " ";
		}
	}
};

int main() {
	sort temp = sort();
	temp.radix();
	return 0;
}