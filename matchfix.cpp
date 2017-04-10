#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAX_PLAYER_NUM = 13;
const int MAX_GAME_NUM = 101;
const int MAX_V_NUM = 2 + MAX_PLAYER_NUM + MAX_GAME_NUM;
const int INF = 1 << 30;
const int MAX_WIN = 1200;

int n, m;
int win[MAX_PLAYER_NUM];
int game[MAX_GAME_NUM][2];
int capa[MAX_V_NUM][MAX_V_NUM];

// 포드-풀커슨
int networkFlow(int networkSize) {
	int src = 0, sink = 1;
	int totalFlow = 0;
	int parent[MAX_GAME_NUM];
	int flow[MAX_V_NUM][MAX_V_NUM];
	memset(flow, 0, sizeof(flow));

	while (true) {
		// 초기화
		memset(parent, -1, sizeof(parent));
		queue<int> q;
		q.push(src);
		
		// 너비 우선 탐색
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();

			for (int there = 0; there < networkSize; there++) {
				if (capa[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					parent[there] = here;
					q.push(there);
				}
			}
		}

		// 증가경로가 없으면 종료
		if (parent[sink] == -1) break;

		// 증가경로를 따라 유량 증가
		int amount = INF;
		for (int i = sink; i != src; i = parent[i]) {
			amount = min(amount, capa[parent[i]][i] - flow[parent[i]][i]);
		}
		for (int i = sink; i != src; i = parent[i]) {
			flow[parent[i]][i] += amount;
			flow[i][parent[i]] -= amount;
		}
		totalFlow += amount;
	}

	return totalFlow;
}

int main() {
	ifstream cin("jinput.txt");
	ofstream cout("joutput.txt");

	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cout << fixed;
	cout.precision(0);

	int cases; cin >> cases;
	while (cases--) {
		cin >> n >> m;
		int networkSize = 2 + m + n;

		for (int i = 0; i < n; i++) cin >> win[i];
		for (int i = 0; i < m; i++)
			for (int j = 0; j < 2; j++)
				cin >> game[i][j];

		for (int g = 0; g < m; g++) {
			capa[0][2 + g] = 1;
			for (int p = 0; p < 2; p++) {
				capa[2 + g][2 + m + game[g][p]] = 1;
			}
		}

		for (int totalWins = 1; totalWins <= MAX_WIN; totalWins++) {
			bool canWin = true;
			for (int p = 0; p < n; p++) {
				if (win[p] >= totalWins) {
					canWin = false;
					break;
				}
			}
			if (!canWin) continue;

			int playersCut = 0;
			for (int p = 0; p < n; p++) {
				int maxWin = (p == 0 ? totalWins : totalWins - 1);
				capa[2 + m + p][1] = maxWin - win[p];
				playersCut += capa[2 + m + p][1];
			}
			if (playersCut > m) {
				// palyers -> sink edge들을 cut 한 비용이 m 보다 큰 경우
				// 이미 최대유량 m 을 지나침. 즉, 승리 불가능
				cout << -1 << '\n';
				break;
			}

			if (networkFlow(networkSize) == m) {
				cout << totalWins << '\n';
				break;
			}
		}
	}

	return 0;
}
