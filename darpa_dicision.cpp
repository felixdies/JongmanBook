#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_CAMERA_NUM = 100 + 1;
const int MAX_STATION_NUM = 200 + 1;

int cameraNum;
int stationNum;
double stationArr[MAX_STATION_NUM];

/// 결정 문제: 정렬되어 있는 locations 중 cameras 를 선택해
/// 모든 카메라 간의 간격이 gap 이상이 되는 방법이 있는지를 반환한다.
bool decision(const vector<double>& location, int cameras, double gap) {
	return false;
}

/// 최적화 문제: 정렬되어 있는 locations 중 cameras 를 선택해 최소 간격을 최대화한다.
double optimize(const vector<double>& location, int cameras) {
	return 0;
}

double solve() {
	return 0;
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

		cin >> cameraNum >> stationNum;

		for (int s = 0; s < stationNum; s++) cin >> stationArr[s];

		if (cameraNum <= 1) cout << 0.00 << endl;
		else {
			cout << solve() << endl;
		}
	}

	return 0;
}
