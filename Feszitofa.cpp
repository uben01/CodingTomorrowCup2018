#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

#define NUM 1000

struct Edge {
	int from;
	int to;

	int cost;

	Edge(int f, int t, int c) {
		from = f;
		to = t;
		cost = c;
	}
};

void build(vector<Edge*>& graph, unordered_map<int,bool>& points) {
	long long int sum = 0;
	sort(graph.begin(), graph.end(), []( const Edge* a, const Edge* b )
	{
		return a->cost < b->cost;
	});

	for(Edge*& e : graph)
	{
		if(points[e->from] == false || points[e->to] == false)
		{
			 points[e->to] = true;
			 sum += e->cost;
		}
	}
	cout << sum;
	std::cin.ignore();
}

int main() {
	vector<Edge*> graph;
	unordered_map<int,bool> points;
	string s;
	{
		ifstream myfile("Wtext");
		if (myfile.is_open()) {
			for (int i = 0; i < NUM; i++) {
				points[i] = false;
				for (int j = i; j < NUM; j++) {
					myfile >> s;
					if (s == "1") {
						graph.push_back(new Edge(i, j, 0));
					}
				}
			}
			myfile.close();
		} else
			cout << "Unable to open file";
	}
	{
		ifstream myfile("Stext");
		stringstream ss;
		int a;
		if (myfile.is_open()) {
			for (int i = 0; i < NUM; i++)
				for (int j = i; j < NUM; j++) {
					myfile >> s;
					if (s != "0") {
						ss.clear();
						ss << s;
						ss >> a;
						graph.push_back(new Edge(i, j, a));
					}
				}

			myfile.close();
		} else
			cout << "Unable to open file";
	}
	build(graph, points);
	for(int i = 0; i < NUM; i++)
		delete graph[i];

	return 0;
}
