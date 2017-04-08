/*
32.3 network modeling
- practice:mileage
cases
m(mileage num) p(price num)
m1 m2
p1 p2
num_of_m_for_p1 list_of_m_for_p1
num_of_m_for_p2 list_of_m_for_p2
- input
2

2 2
8 5
8 6
1 0
2 0 1

2 2
5 8 
8 6
1 0
2 0 1
- output
1
3
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_V_NUM = 6;
const int INF = 1 << 30;

int V;

int capacity[MAX_V_NUM][MAX_V_NUM];
int flow[MAX_V_NUM][MAX_V_NUM];

// 포드-풀커슨 알고리즘
int networkFlow(int source, int sink) {
	memset(flow, 0, sizeof(flow));

	int total = 0;
	
	while (true) {
		vector<int> parent(V, -1);
		queue<int> q;
		q.push(source);

		// 너비 우선 탐색
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();

			for (int there = 0; there < V; there++) {
				if (parent[there] == -1 && capacity[here][there] - flow[here][there] > 0) {
					parent[there] = here;
					q.push(there);
				}
			}
		}

		// 증가경로가 없으면 종료
		if (parent[sink] == -1) break;

		// 증가경로가 있으면 flow 흘림
		int amt = INF;
		for (int here = sink; here != source; here = parent[here]) {
			amt = min(amt, capacity[parent[here]][here] - flow[parent[here]][here]);
		}
		for (int here = sink; here != source; here = parent[here]) {
			flow[parent[here]][here] += amt;
			flow[here][parent[here]] -= amt;
		}
		total += amt;
	}

	return total;
}

int main() {
	int cases; cin >> cases;
	while (cases--) {
		memset(capacity, 0, sizeof(capacity));

		int s = 0;
		int t = 1;
		int m, n; cin >> m >> n;
		int psum = 0;

		V = 2 + m + n;

		for (int i = 2; i < 2 + m; i++) {
			int mcapa; cin >> mcapa;
			capacity[s][i] = mcapa;
		}
		for (int i = 2 + m; i < 2 + m + n; i++) {
			int pcapa; cin >> pcapa;
			capacity[i][t] = pcapa;
			psum += pcapa;
		}

		for (int i = 0; i < n; i++) {
			int v = i;
			v += 2 + m;
			int msz; cin >> msz;
			for (int j = 0; j < msz; j++) {
				int u; cin >> u;
				u += 2;
				capacity[u][v] = INF;
			}
		}

		cout << psum - networkFlow(s, t) << '\n';
	}
	
	return 0;
}
