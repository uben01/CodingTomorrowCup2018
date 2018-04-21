#include <iostream>
#include <vector>
using namespace std;

// [oszlop][sor]

struct Solution {
	int szamok[4];

	Solution(int szamok1, int szamok2, int szamok3, int szamok4) {
		szamok[0] = szamok1;
		szamok[1] = szamok2;
		szamok[2] = szamok3;
		szamok[3] = szamok4;
	}
	int get(int x) {
		return szamok[x];
	}

	bool contains(Solution* a) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (szamok[i] == a->get(j))
					return true;
			}
		}
		return false;
	}

};

bool constraint_c(int i0, int** s) {

	if (i0 == 0)
		return (s[0][2] == 0) ?
				false : (((s[0][0] + s[0][1]) / (float) s[0][2]) - s[0][3]) == 3;
	else if (i0 == 1)
		return (((s[1][0] + s[1][1]) * s[1][2]) * s[1][3]) == 600;
	else if (i0 == 2)
		return (((s[2][0] + s[2][1]) * s[2][2]) * s[2][3]) == 1320;
	else
		return (s[3][3] == 0) ?
				false :
				(((s[3][0] + s[3][1]) + s[3][2]) / (float) s[3][3]) == 12;

}
bool constraint_r(Solution* s0, Solution* s1, Solution* s2, Solution* s3) {

	return ((((s0->get(0) + s1->get(0)) + s2->get(0)) - s3->get(0)) == 13)
			&& ((((s0->get(1) + s1->get(1)) + s2->get(1)) + s3->get(1)) == 40)
			&& ((((s0->get(2) * s1->get(2)) * s2->get(2)) * s3->get(2)) == 5005)
			&& (((s3->get(3) == 0) ?
					(false) :
					(((s0->get(3) * s1->get(3)) * s2->get(3))
							/ (float) s3->get(3))) == 50);

}

int main() {
	int **szamok = new int*[4];
	for (unsigned int i = 0; i < 4; i++) {
		szamok[i] = new int[4];
		for (unsigned int j = 0; j < 4; j++) {
			szamok[i][j] = 0;
		}
	}
	vector<vector<Solution*>> rows;

// sorok
	for (int i0 = 0; i0 < 4; i0++) {
		vector<Solution*> v;
		rows.push_back(v);
		for (unsigned int i1 = 1; i1 <= 16; i1++) {
			szamok[i0][0] = i1;
			for (unsigned int i2 = 1; i2 <= 16; i2++) {
				if (i1 == i2)
					continue;
				szamok[i0][1] = i2;
				for (unsigned int i3 = 1; i3 <= 16; i3++) {
					if (i1 == i3 || i2 == i3)
						continue;
					szamok[i0][2] = i3;
					for (unsigned int i4 = 1; i4 <= 16; i4++) {
						if (i1 == i4 || i2 == i4 || i3 == i4)
							continue;
						szamok[i0][3] = i4;
						if (constraint_c(i0, szamok))
							rows[i0].push_back(
									new Solution(szamok[i0][0], szamok[i0][1],
											szamok[i0][2], szamok[i0][3]));
					}
				}
			}
		}
	}
	int counter = 0;
	int max = 0;

	for (unsigned int i1 = 0; i1 < rows[0].size(); i1++) {
		for (unsigned int i2 = 0; i2 < rows[1].size(); i2++) {
			if (rows[0][i1]->contains(rows[1][i2]))
				continue;
			for (unsigned int i3 = 0; i3 < rows[2].size(); i3++) {
				if (rows[0][i1]->contains(rows[2][i3])
						|| rows[1][i2]->contains(rows[2][i3]))
					continue;
				for (unsigned int i4 = 0; i4 < rows[3].size(); i4++) {
					if (rows[0][i1]->contains(rows[3][i4])
							|| rows[1][i2]->contains(rows[3][i4])
							|| rows[2][i3]->contains(rows[3][i4]))
						continue;
					if (constraint_r(rows[0][i1], rows[1][i2], rows[2][i3],
							rows[3][i4])) {
						counter++;
						int d = rows[0][i1]->get(0) + rows[1][i2]->get(1)
								+ rows[2][i3]->get(3) + rows[3][i4]->get(2);
						if (d > max)
							max = d;
					}
				}
			}
		}
	}

	cout << "Vége\n - Megfejtések száma: " << counter << endl;
	cout << "Maximális érték: " << max << endl;

	for (auto a : rows) {
		for (auto b : a)
			delete b;
	}

	return 0;
}
