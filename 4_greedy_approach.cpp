#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

//prim's algorithm (mst)
//kruskal's algorithm (mst)
//dijkstra's algorithm (single-source shrotest path)
//Bellman and Ford's algorithm (sssp)
//Knapsack Problem (Greedy vs DynamicProgramming)

class prim {
private:
	const int inf = 999;
	int content_size;
	int** W;
	int* nearest;
	int* distance;

public:
	prim() :content_size(-1), W(nullptr) {
		int** temp;
		int string_index = 0;
		int matrix_i = 1, matrix_j = 1;
		char input_string[1000];

		ifstream inFile("input_file\\prim_input.txt");
		inFile.getline(input_string, 1000);

		content_size = atoi(input_string);
		nearest = new int[content_size + 1];
		distance = new int[content_size + 1];

		temp = new int*[content_size + 1];
		for (int i = 0; i <= content_size; i++) {
			temp[i] = new int[content_size + 1];
			for (int j = 0; j <= content_size; j++) {
				temp[i][j] = inf;
			}
		}
		W = temp;
		
		while (!inFile.eof()) {
			inFile.getline(input_string, 1000);
			string_index = 0;
			while(input_string[string_index] != '\0'){
				if (input_string[string_index] != ' ') {
					W[matrix_i][matrix_j] = (int(input_string[string_index] - '0') != 0 ? int(input_string[string_index] - '0') : inf);
					matrix_j++;
					if (matrix_j > content_size) {
						matrix_j = 1;
						matrix_i++;
					}
				}
				string_index++;
			}
		}
		inFile.close();

		for (int i = 2; i <= content_size; i++) {
			nearest[i] = 1;
			distance[i] = W[1][i];
		}
	}

	~prim() {
		for (int i = 0; i <= content_size; i++) {
			delete[]W[i];
		}
		delete[]W;
		delete[]nearest;
		delete[]distance;
	}

	void main() {
		int near, min;
		for (int count = 2; count <= content_size; count++) {
			near = -1;
			min = inf;

			for (int i = 2; i <= content_size; i++) {
				if (distance[i] >= 0 && distance[i] < min) {
					min = distance[i];
					near = i;
				}
			}
			cout << "v" << near << " <-> " << "v" << nearest[near] << endl;
			distance[near] = -1;
			for (int i = 2; i <= content_size; i++) {
				if (W[i][near] < distance[i]) {
					distance[i] = W[i][near];
					nearest[i] = near;
				}
			}
		}
	}
};

class kruskal {
private:
	const int inf = 999;

	struct edge {
		int start;
		int end;
		int weight;
	};

	int content_size;
	int** W;
	int* P;
	
	edge* E;
	int struct_size;

public:
	kruskal() : content_size(-1), W(nullptr) {
		int** temp;
		int string_index = 0;
		int matrix_i = 1, matrix_j = 1;
		char input_string[1000];

		ifstream inFile("input_file\\kruskal_input.txt");
		inFile.getline(input_string, 1000);

		content_size = atoi(input_string);
		P = new int[content_size + 1];

		temp = new int* [content_size + 1];
		for (int i = 0; i <= content_size; i++) {
			temp[i] = new int[content_size + 1];
			for (int j = 0; j <= content_size; j++) {
				temp[i][j] = inf;
			}
		}
		W = temp;

		while (!inFile.eof()) {
			inFile.getline(input_string, 1000);
			string_index = 0;
			while (input_string[string_index] != '\0') {
				if (input_string[string_index] != ' ') {
					W[matrix_i][matrix_j] = (int(input_string[string_index] - '0') != 0 ? int(input_string[string_index] - '0') : inf);
					matrix_j++;
					if (matrix_j > content_size) {
						matrix_j = 1;
						matrix_i++;
					}
				}
				string_index++;
			}
		}
		inFile.close();

		for (int i = 1; i <= content_size; i++) {
			P[i] = i;
		}

		struct_size = (content_size - 1) % 2 == 1 ? (content_size / 2) * (content_size - 1) : ((content_size - 1) / 2) * content_size;
		E = new edge[struct_size + 1];
		
	}

	~kruskal() {
		for (int i = 0; i <= content_size; i++) {
			delete[]W[i];
		}
		delete[]W;
		delete[]P;
		delete[]E;
	}

	void sort() {
		int count = 1;
		int temp_start, temp_end, temp_weight;

		for (int i = 1; i <= content_size; i++) {
			for (int j = i + 1; j <= content_size; j++) {
				E[count].start = i;
				E[count].end = j;
				E[count].weight = W[i][j];
				count++;
			}
		}

		for (int i = 1; i < count; i++) {
			for (int j = i + 1; j < count; j++) {
				if (E[i].weight > E[j].weight) {
					temp_start = E[i].start;
					temp_end = E[i].end;
					temp_weight = E[i].weight;

					E[i].start = E[j].start;
					E[i].end = E[j].end;
					E[i].weight = E[j].weight;

					E[j].start = temp_start;
					E[j].end = temp_end;
					E[j].weight = temp_weight;
				}
			}
		}
	}

	int find(int num) {
		for (int i = 1; i <= struct_size; i++) {
			if (P[num] == num) {
				return num; // no cycle
			}
			else {
				num = P[num];
			}
		}
		return -1; // cycle
	}

	void union_find() {
		for (int i = 1; i <= struct_size; i++) {
			if (find(E[i].start) != find(E[i].end)) { // no cycle
				P[E[i].end] = E[i].start;
			}
		}

		for (int i = 1; i <= content_size; i++) {
			cout << i << " - " << P[i] << endl;
		}
	}

	void main() {
		sort();
		union_find();
	}
};

class dijkstra {
private:
	const int inf = 999;
	int content_size;
	int** W;
	int* touch;
	int* length;

public:
	dijkstra() :content_size(-1), W(nullptr) {
		int** temp;
		int string_index = 0;
		int matrix_i = 1, matrix_j = 1;
		char input_string[1000];

		ifstream inFile("input_file\\dijkstra_input.txt");
		inFile.getline(input_string, 1000);

		content_size = atoi(input_string);
		touch = new int[content_size + 1];
		length = new int[content_size + 1];

		temp = new int* [content_size + 1];
		for (int i = 0; i <= content_size; i++) {
			temp[i] = new int[content_size + 1];
			for (int j = 0; j <= content_size; j++) {
				temp[i][j] = inf;
			}
		}
		W = temp;

		while (!inFile.eof()) {
			inFile.getline(input_string, 1000);
			string_index = 0;
			while (input_string[string_index] != '\0') {
				if (input_string[string_index] != ' ') {
					W[matrix_i][matrix_j] = (int(input_string[string_index] - '0') != 0 ? int(input_string[string_index] - '0') : inf);
					matrix_j++;
					if (matrix_j > content_size) {
						matrix_j = 1;
						matrix_i++;
					}
				}
				string_index++;
			}
		}
		inFile.close();

		for (int i = 2; i <= content_size; i++) {
			touch[i] = 1;
			length[i] = W[1][i];
		}
	}

	~dijkstra() {
		for (int i = 0; i <= content_size; i++) {
			delete[]W[i];
		}
		delete[]W;
		delete[]touch;
		delete[]length;
	}

	void main() {
		int near, min;
		for (int count = 2; count <= content_size; count++) {
			near = -1;
			min = inf;

			for (int i = 2; i <= content_size; i++) {
				if (length[i] >= 0 && length[i] < min) {
					min = length[i];
					near = i;
				}
			}
			cout << "v" << touch[near] << " -> " << "v" << near << endl;
			
			for (int i = 2; i <= content_size; i++) {
				if (length[near] + W[near][i] < length[i]) {
					length[i] = length[near] + W[near][i];
					touch[i] = near;
				}
			}
			length[near] = -1;
		}
	}
};

class bellman_ford {
private:
	const int inf = 999;
	int content_size;
	int** length;
	int* dist;
	int* check_point;

public:
	bellman_ford() :content_size(-1), length(nullptr) {
		int** temp;
		int string_index = 0;
		int matrix_i = 1, matrix_j = 1;
		char input_string[1000];

		ifstream inFile("input_file\\bellman_input.txt");
		inFile.getline(input_string, 1000);

		content_size = atoi(input_string);
		dist = new int[content_size + 1];
		check_point = new int[content_size + 1];

		temp = new int* [content_size + 1];
		for (int i = 0; i <= content_size; i++) {
			temp[i] = new int[content_size + 1];
			for (int j = 0; j <= content_size; j++) {
				temp[i][j] = inf;
			}
		}
		length = temp;

		while (!inFile.eof()) {
			inFile.getline(input_string, 1000);
			string_index = 0;
			while (input_string[string_index] != '\0') {
				if (input_string[string_index] != ' ') {
					if (input_string[string_index] == '-') {
						length[matrix_i][matrix_j] = - int(input_string[string_index + 1] - '0');
						string_index++;
					}
					else {
						length[matrix_i][matrix_j] = (int(input_string[string_index] - '0') != 0 ? int(input_string[string_index] - '0') : inf);
					}
					matrix_j++;
					if (matrix_j > content_size) {
						matrix_j = 1;
						matrix_i++;
					}
				}
				string_index++;
			}
		}
		inFile.close();
	}

	~bellman_ford() {
		for (int i = 0; i <= content_size; i++) {
			delete[]length[i];
		}
		delete[]length;
		delete[]dist;
		delete[]check_point;
	}

	void show_dist(int v) {
		for (int i = 1; i <= content_size; i++) {
			cout << v << "에서 " << i << "까지 가는데 최소거리 : ";
			cout << (dist[i] == 999 ? 0 : dist[i]) << endl;

			cout << "경로: " << v;
			show_route(i, -1);
			cout << endl;
		}
		cout << endl;
	}

	void show_route(int u, int u_before) {
		if (u == u_before) return;
		show_route(check_point[u], u);
		cout << " -> " << u;
	}

	void main() {
		int v = 1;
		bool check = false;
		for (int i = 1; i <= content_size; i++) {
			dist[i] = length[v][i];
			check_point[i] = i;
		}

		for (int k = 2; k <= content_size; k++) {
			for (int u = 1; u <= content_size; u++) {
				if (u != v) {
					for (int i = 1; i <= content_size; i++) {
						if (length[i][u] >= 1) {
							check = true;
							break;
						}
					}

					if (check == true) {
						for (int i = 1; i <= content_size; i++) {
							if (dist[u] > dist[i] + length[i][u]) {
								dist[u] = dist[i] + length[i][u];
								check_point[u] = i;
							}
						}
						check = false;
					}
				}
			}
		}
		show_dist(v);
	}
};

int main() {
	bellman_ford P = bellman_ford();
	P.main();
	return 0;
}