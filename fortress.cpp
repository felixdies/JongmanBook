#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

class Point {
public:
	Point() {}
	double x;
	double y;
	bool operator < (const Point& p) const { return false; }
};

vector<pair<double, Point> > nodes;
vector<int> parent;

int longest; // 현재 탐색 하는 node 를 root 로 하는 
// 트리의 높이를 반환한다.
int solve(int nodeIdx) {
	int subTreeNum = 0;
	vector<int> subTreeDepth;

	for (int i = 0; i < parent.size(); i++) {
		if (parent[i] == nodeIdx)
			subTreeDepth.push_back(solve(i));
	}

	int childrenNum = subTreeDepth.size();

	if (childrenNum == 0) return 0;

	sort(subTreeDepth.rbegin(), subTreeDepth.rend());

	if (childrenNum >= 2) {
		longest = max(longest, subTreeDepth[0] + subTreeDepth[1] + 2);
	}

	return subTreeDepth[0] + 1;
}

int main() {
	cout << fixed;
	cout.precision(10);

	int cases;
	cin >> cases;

	while (cases--) {
		nodes.clear();
		parent.clear();
		
		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			Point p;
			double r;
			cin >> p.x >> p.y >> r;
			nodes.push_back(make_pair(r, p));
		}

		sort(nodes.rbegin(), nodes.rend());

		parent.push_back(-1); // root node
		for (int i = 0; i < nodes.size(); i++) {
			for (int j = i; j >= 0; j--) {
				if (i == j) continue;

				double xdist = nodes[j].second.x - nodes[i].second.x;
				double ydist = nodes[j].second.y - nodes[i].second.y;

				// 두 점 사이의 거리가 j번째 반지름 이하이면
				// node[i] 는 node[j] 에 속해 있다.
				if (sqrt(pow(xdist, 2) + pow(ydist, 2)) <= nodes[j].first + 1e-10) {
					parent.push_back(j);
					break;
				}
			}
		}

		int h = solve(0);
		cout << max(longest, h) << endl;
	}

	return 0;
}

/* 4, 4, 5, 4, 4, 5
6
5
10 10 2
10 10 4
20 20 2
20 20 4
15 15 10
6
10 10 2
10 10 4
20 20 2
20 20 4
15 15 10
15 15 100
9
10 10 2
10 10 4
20 20 2
20 20 4
15 15 10
30 30 2
15 15 100
15 15 101
15 15 102
3
5 5 15
5 5 10
5 5 5
6
15 15 100
15 15 99
5 15 3
25 15 3
5 15 2
25 15 2
8 
21 15 20 
15 15 10 
13 12 5 
12 12 3 
19 19 2 
30 24 5 
32 10 7 
32 9 4 
*/
