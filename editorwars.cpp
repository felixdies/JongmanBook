#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<int> parent, ranks, sizes, enemy;

int find(int u) {
	if (parent[u] == u) return u;
	return parent[u] = find(parent[u]);
}

int merge(int u, int v) {
	if (u == -1 || v == -1) return max(u, v);
	u = find(u);
	v = find(v);

	if (u == v) return u;

	if (ranks[u] > ranks[v]) swap(u, v);
	parent[u] = v;
	if (ranks[u] == ranks[v]) ranks[v]++;
	sizes[v] += sizes[u];

	return v;
}

bool ack(int u, int v) {
	u = find(u);
	v = find(v);

	if (enemy[u] == v) return false; // 이미 적

	int a = merge(u, v);
	int b = merge(enemy[u], enemy[v]);
	enemy[a] = b;
	if (b != -1) enemy[b] = a;

	return true;
}

bool dis(int u, int v) {
	u = find(u);
	v = find(v);

	if (u == v) return false; // 이미 동지

	int a = merge(u, enemy[v]);
	int b = merge(v, enemy[u]);
	enemy[a] = b;
	enemy[b] = a;

	return true;
}

int maxParty(int n) {
	vector<bool> checked(n, false);

	int ret = 0;
	for (int i = 0; i < n; i++) {
		int u = find(i);
		int v = enemy[u] == -1 ? u : find(enemy[u]);
		if (!checked[u]) {
			ret += max(sizes[u], sizes[v]);
			checked[u] = true;
			checked[v] = true;
		}
	}
	return ret;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	int cs; cin >> cs;
	while (cs--) {
		int n, m; cin >> n >> m;

		parent = vector<int>(n, 0);
		ranks = vector<int>(n, 0);
		sizes = vector<int>(n, 1);
		enemy = vector<int>(n, -1);

		for (int i = 0; i < n; i++) parent[i] = i;

		bool toggle = true;
		for (int i = 0; i < m; i++) {
			string strLike;
			int u, v;
			cin >> strLike >> u >> v;

			if (!toggle) continue; // continue 해서 input 을 모두 받아야 한다.

			if (strLike == "ACK" && (toggle = ack(u, v)) == false) {
				cout << "CONTRADICTION AT " << i + 1 << '\n';
				//break; 안됨! input 을 모두 받아야 한다.
			}
			else if (strLike == "DIS" && (toggle = dis(u, v)) == false) {
				cout << "CONTRADICTION AT " << i + 1 << '\n';
				//break; 안됨! input 을 모두 받아야 한다.
			}
		}
		if (toggle)
			cout << "MAX PARTY SIZE IS " << maxParty(n) << '\n';
	}

	return 0;
}
