#include <vector>
#include <iostream>
#include <queue>

using namespace std;

struct obj {
	int x;
	int y;
	int z;
	int h;
	obj(int _x = 0, int _y = 0, int _z = 0, int _h = 0) :
			x(_x), y(_y), z(_z), h(_h) {
	}
};

struct Graph {
	queue<obj*> q;
	obj**** arr = new obj***[99];

	Graph() {
		q.push(new obj(0, 0, 0, 0));

		for (int x = 0; x < 99; x++) {
			arr[x] = new obj**[99];
			for (int y = 0; y < 99; y++) {
				arr[x][y] = new obj*[19];
				for (int z = 0; z < 19; z++) {
					arr[x][y][z] = new obj(x, y, z, 0);
				}
			}
		}
	}
};

void valid(Graph* g, obj* o, vector<int>& j) {

	int x = o->x + j[0];
	int y = o->y + j[1];
	int z = o->z + j[2];
	int h = o->h + 1;

	if (x == 99 && y == 99 && z == 19) {
		cout << h << endl;
		string s;
		cin >> s;
	}

	if (x >= 99 || x < 0 || y >= 99 || y < 0 || z >= 19 || z < 0)
		return;

	if (g->arr[x][y][z]->h == 0) {
		g->arr[x][y][z]->h = h;
		g->q.push(g->arr[x][y][z]);
	}

}

int main() {
	Graph* g = new Graph();
	// 6 heylett 4 és 5
	vector<vector<int>> jump { { 2, 3, 6 }, { 2, 6, 3 }, { 3, 2, 6 },
			{ 3, 6, 2 }, { 6, 2, 3 }, { 6, 3, 2 }, { -2, 3, 6 }, { -2, 6, 3 }, {
					-3, 2, 6 }, { -3, 6, 2 }, { -6, 2, 3 }, { -6, 3, 2 }, { 2,
					-3, 6 }, { 2, -6, 3 }, { 3, -2, 6 }, { 3, -6, 2 }, { 6, -2,
					3 }, { 6, -3, 2 }, { 2, 3, -6 }, { 2, 6, -3 }, { 3, 2, -6 },
			{ 3, 6, -2 }, { 6, 2, -3 }, { 6, 3, -2 }, { 2, -3, -6 },
			{ 2, -6, -3 }, { 3, -2, -6 }, { 3, -6, -2 }, { 6, -2, -3 }, { 6, -3,
					-2 }, { -2, 3, -6 }, { -2, 6, -3 }, { -3, 2, -6 }, { -3, 6,
					-2 }, { -6, 2, -3 }, { -6, 3, -2 }, { -2, -3, 6 }, { -2, -6,
					3 }, { -3, -2, 6 }, { -3, -6, 2 }, { -6, -2, 3 }, { -6, -3,
					2 }, { -2, -3, -6 }, { -2, -6, -3 }, { -3, -2, -6 }, { -3,
					-6, -2 }, { -6, -2, -3 }, { -6, -3, -2 } };

	while (!g->q.empty()) {
		obj* o = g->q.front();
		g->q.pop();
		for (vector<int>& a : jump)
			valid(g, o, a);
	}
	cout << "vege" << endl;

	return 0;
}
