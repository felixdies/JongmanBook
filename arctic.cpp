#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_STATION_NUM = 100;

int stationNum;
double stations[MAX_STATION_NUM][2];
bool reachable[MAX_STATION_NUM];

bool decision(double gap) {
	memset(reachable, 0, sizeof(reachable));

	for (int s = 0; s < stationNum; s++) {
		if (reachable[s]) continue;

		for (int n = 0; n < stationNum; n++) {
			if (s == n) continue;

			double xd = stations[s][0] - stations[n][0];
			double yd = stations[s][1] - stations[n][1];

			if (sqrt(xd*xd + yd*yd) <= gap) {
				reachable[s] = reachable[n] = true;
			}
		}

		if (!reachable[s]) return false;
	}

	return true;
}

double solve() {
	int cnt = 0;
	double gap = 1000.0;
	double adj = gap / 2.0;

	while (cnt < 100) {
		bool result = decision(gap);
		
		if (result) gap -= adj;
		else gap += adj;

		adj /= 2.0;
		cnt++;
	}

	return gap;
}

int main() {
	ifstream cin("jinput.txt");
	ofstream cout("joutput.txt");

	int caseN;
	cin >> caseN;
	cout << fixed;
	cout.precision(2);
	
	for (int caseCnt = 0; caseCnt < caseN; caseCnt++) {
		cin >> stationNum;

		for (int s = 0; s < stationNum; s++) cin >> stations[s][0] >> stations[s][1];

		if (stationNum <= 1) cout << 0.00 << endl;
		else cout << solve() << endl;
	}

	return 0;
}
