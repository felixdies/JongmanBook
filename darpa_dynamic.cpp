#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_CAMERA_NUM = 100 + 1;
const int MAX_STATION_NUM = 200 + 1;

int cameraNum;
int stationNum;
double stationArr[MAX_STATION_NUM];
double cache[MAX_STATION_NUM][MAX_CAMERA_NUM];

double solve(int remainCameraNum, int lastStationIdx, int stationIdx) {
	if (remainCameraNum == 0 || remainCameraNum > stationNum - stationIdx) return -1;

	double& ret = cache[stationIdx][remainCameraNum];
	if (ret > -0.5) return ret;

	ret = lastStationIdx == -1 ? -1 : stationArr[stationIdx] - stationArr[lastStationIdx];

	double put = solve(remainCameraNum - 1, stationIdx, stationIdx + 1);
	if (ret < -0.5) ret = put;
	else if (put > -0.5) ret = min(ret, put);

	double notput = solve(remainCameraNum, lastStationIdx, stationIdx + 1);
	
	return ret = max(ret, notput);
}

int main() {
	ifstream cin("jinput.txt");
	ofstream cout("joutput.txt");

	int caseN;
	cin >> caseN;
	cout << fixed;
	cout.precision(2);
	
	for (int caseCnt = 0; caseCnt < caseN; caseCnt++) {
		memset(stationArr, -1, sizeof(stationArr));
		memset(cache, -1, sizeof(cache));

		cin >> cameraNum >> stationNum;

		for (int s = 0; s < stationNum; s++) cin >> stationArr[s];

		if (cameraNum <= 1) cout << 0.00 << endl;
		else cout << solve(cameraNum, -1, 0) << endl;
	}

	return 0;
}
