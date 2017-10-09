// algospot genius 문제.
// 최초 답안의 sliding window 의 index 계산 부분(5 modular 연산)이 복잡해보여서 변경.
// 곱셈연산이 오래 걸려서 log 덧셈연산으로 바꾸면 될 지 검토했으나,
// log 변환 하지 않고 곱셈을 덧셈으로 변경 해 보았으나 여전히 시간초과ㅠㅠ
// <해결!> vector 를 배열로 바꿔서 속도 향상.
// 2차원 vector 대신 2차원 배열을 사용하니 200배 이상(!!) 빠르다!
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

const int MAX_N = 50 + 1;
const int MAX_M = 10 + 1;

int main() {
	//USE_TEXTFILE;
	//USE_STOPWATCH; PRINT_TIME(start);

	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cout << fixed;
	cout.precision(10);

	int musicLen[MAX_N];
	double mat[MAX_N][MAX_N];
	int likes[MAX_M];
	double dp[5][MAX_N];

	int cs; cin >> cs;
	while (cs--) {
		int n, k, m; cin >> n >> k >> m;

		for (int i = 0; i < n; i++) cin >> musicLen[i];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> mat[i][j];

		for (int i = 0; i < m; i++) cin >> likes[i];

		memset(dp, 0, sizeof(dp));
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
					dp[cur][i] += dp[prev][j] * mat[j][i];
				}
			}
		}

		//PRINT_TIME(start);

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
