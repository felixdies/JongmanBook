#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

const int MAX_WIDTH = 1000;
const int MOD_NUM = 1000000007;

int cache[MAX_WIDTH];

int solve(int width) {
	if (width <= 2) return width;
	
	int& ret = cache[width];
	if (ret != -1) return ret;

	return ret = (solve(width - 1) + solve(width - 2)) % MOD_NUM;
}

int main() {
	ifstream cin("jinput.txt");
	ofstream cout("joutput.txt");

	int caseN;
	cin >> caseN;
	cout << fixed;
	cout.precision(10);

	for (int caseCnt = 0; caseCnt < caseN; caseCnt++) {
		memset(cache, -1, sizeof(cache));
		
		int width;
		cin >> width;
		
		cout << solve(width) - solve(width / 2) << endl;
	}

	return 0;
}

/*
0
2
2
913227494
*/
