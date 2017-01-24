#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_CAMERA_NUM = 100 + 1;
const int MAX_STATION_NUM = 200 + 1;

const int LOOP_CNT = 1000000;

int cameraNum;
int stationNum;

struct station {
	double location;
	int camIdx;
};

struct camera {
	int station;
	camera* prev;
	camera* next;
};

station stationArr[MAX_STATION_NUM];
camera camArr[MAX_CAMERA_NUM];

void preCalc() {
	camArr[0].station = 0;
	stationArr[0].camIdx = 0;

	camArr[cameraNum - 1].station = stationNum - 1;
	stationArr[stationNum - 1].camIdx = cameraNum - 1;

	for (int c = 0; c < cameraNum - 2; c++) {
		int stdIdx;
		do { stdIdx = rand() % stationNum; } while (stationArr[stdIdx].camIdx != -1);
		
		camArr[c].station = stdIdx;
		stationArr[stdIdx].camIdx = c;
	}

	camera prev;
	for (int s = 0; s < stationNum; s++) {
		int cam = stationArr[s].camIdx;
		if (cam != -1) {
			if (prev != NULL) {
				prev->next = &camArr[cam];
				camArr[cam].;
			}

			prev = &camArr[stationArr[s].camIdx];
		}
	}
}

double solve() {
	for (int loop = 0; loop < LOOP_CNT; loop++) {
		double curmin = *min_element(distanceToNext, distanceToNext + cameraNum);

		int cam = rand() % (cameraNum - 1) + 1;

		int next;
		do { next = rand() % stationNum; } while (cameraArr[next]);
		

	}

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
		memset(camArr, -1, sizeof(stationArr));

		cin >> cameraNum >> stationNum;

		for (int s = 0; s < stationNum; s++) cin >> stationArr[s].location;

		if (cameraNum <= 1) cout << 0.00 << endl;
		else {
			preCalc();
			cout << solve() << endl;
		}
	}

	return 0;
}
