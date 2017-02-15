#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

const int MAX_POINT_NUM = 100 + 2;

int n, m;
double xs[2][MAX_POINT_NUM];
double ys[2][MAX_POINT_NUM];

double at(double x) {
	double top[2];
	double bottom[2];

	for (int i = 0; i < n; i++) {
		double lx = min(xs[0][i], xs[0][i + 1]);
		double rx = max(xs[0][i], xs[0][i + 1]);

		if (lx <= x && x < rx) {

		}
	}

	return max(bottom[0], bottom[1]) - min(top[0], top[1]);
}

double solve() {
	double lx = max(*min_element(xs[0], xs[0]+n), *min_element(xs[1], xs[1]+m));
	double rx = min(*max_element(xs[0], xs[0]+n), *max_element(xs[1], xs[1]+m));



	return 0;
}

int main() {
	ifstream cin("jinput.txt");
	ofstream cout("joutput.txt");

	cout << fixed;
	cout.precision(10);

	int cs;
	cin >> cs;

	while (cs--) {
		cin >> n >> m;
		for (int i = 0; i < n; i++) cin >> xs[0][i] >> ys[0][i];
		xs[0][n] = xs[0][0];
		ys[0][n] = ys[0][0];
		for (int i = 0; i < m; i++) cin >> xs[1][i] >> ys[1][i];
		xs[1][m] = xs[1][0];
		ys[1][m] = ys[1][0];

		cout << solve() << endl;
	}

	return 0;
}

/*fossil
1.0
27.6529680365
0.000000
*/
