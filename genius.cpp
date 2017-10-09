#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <bitset>

using namespace std;

int main() {
	//ifstream cin("jinput.txt");
	//ofstream cout("joutput.txt");

	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cout << fixed;
	cout.precision(10);

	int cs; cin >> cs;
	while (cs--) {
		int n, k, m; cin >> n >> k >> m;
		
		vector<int> musicLen(n);
		for (int i = 0; i < n; i++) cin >> musicLen[i];

		vector<vector<double>> mat(n, vector<double>(n, 0));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> mat[i][j];

		vector<int> likes(m);
		for (int i = 0; i < m; i++) cin >> likes[i];

		vector<vector<double>> dp(5, vector<double>(n, 0));
		dp[0][0] = 1;

		int past = 0;
		int cur;
		while (k--) {
			past = (past - 1) % 5;
			cur = (5 + past) % 5;
			for (int i = 0; i < n; i++) {
				dp[cur][i] = 0;
				for (int j = 0; j < n; j++) {
					int prev = (5 + musicLen[j] + past) % 5;
					dp[cur][i] += dp[prev][j] * mat[j][i];
				}
			}
		}

		for (int i = 0; i < m; i++) {
			int idx = likes[i];
			double ret = 0;
			for (int j = 0; j < musicLen[idx]; j++)
				ret += dp[(cur + j) % 5][idx];
			cout << ret << ' ';
		}
		cout << '\n';
	}

	return 0;
}
