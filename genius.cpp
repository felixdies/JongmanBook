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
#include <ctime>

#define USE_TEXTFILE ifstream cin("jinput.txt"); ofstream cout("joutput.txt");
#define USE_STOPWATCH std::clock_t start; double duration; start = std::clock();
#define PRINT_TIME(start) cout << "\n[Time]" << (std::clock() - (start)) / (double)CLOCKS_PER_SEC << '\n';

using namespace std;

int main() {
	//USE_TEXTFILE;
	//USE_STOPWATCH; PRINT_TIME(start);

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
		int cur = 0;
		while (k--) {
			// 0-4 까지의 시계를 시계 반대방향으로 한칸 돌린다고 생각하자
			past++;
			if (past == 5) past = cur = 0;
			else cur = 5 - past;

			for (int i = 0; i < n; i++) {
				dp[cur][i] = 0;
				for (int j = 0; j < n; j++) {
					// j번째 음악이 musicLen 전에 시작했을 확률은
					// 시계방향으로 musicLen[j] 만큼 이동한 위치에 기록돼 있다
					int prev = (cur + musicLen[j]) % 5; 
					dp[cur][i] += dp[prev][j] + mat[j][i]; // 곱셈만 덧셈으로 바꾸어 봄-여전히 TLE
				}
			}
		}

		//PRINT_TIME(start); n=4, k=1,000,000 일 때 50초 이상 소요

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
