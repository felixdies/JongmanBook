#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <bitset>

#define USE_TEXTFILE ifstream cin("jinput.txt"); ofstream cout("joutput.txt");
#define USE_STOPWATCH std::clock_t start; double duration; start = std::clock();
#define PRINT_TIME(start) cout << "\n[Time]" << (std::clock() - (start)) / (double)CLOCKS_PER_SEC << '\n';

using namespace std;

#define MAX_SIZE 200001

vector<int> multiply(int* a, int asz, int* b, int bsz) {
	vector<int> ret(asz + bsz, 0);

	for (int i = 0; i < asz; i++) {
		for (int j = 0; j < bsz; j++) {
			ret[i + j] += a[i] * b[j];
		}
	}

	return ret;
}

// a+=b*(10^k)
void addTo(vector<int>& a, const vector<int>& b, int k) {
	if (a.size() < k + b.size()) {
		vector<int> temp(k + b.size(), 0);
		for (int i = 0; i < a.size(); i++)
			temp[i] = a[i];
		a = temp;
	}

	for (int i = 0; i < b.size(); i++) {
		a[k + i] += b[i];
	}

	return;
}

// a-=b, assume a>=b
void subFrom(vector<int>& a, const vector<int>& b) {
	// b.size() could be larger than a.size() when the leading number is 0
	for (int i = 0; i < a.size() && i < b.size(); i++)
		a[i] -= b[i];
	return;
}

vector<int> karatsuba(int* a, int asz, int* b, int bsz) {
	if (bsz > asz)
		return karatsuba(b, bsz, a, asz);

	if (asz <= 50)
		return multiply(a, asz, b, bsz);

	int half = asz / 2;

	/*
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
	*/

	vector<int> z0 = karatsuba(a, half, b, min(bsz, half));
	vector<int> z1;
	if (bsz > half)
		z1 = karatsuba(a + half, asz - half, b + half, bsz - half);

	int* a0 = new int[half];
	for (int i = 0; i < half; i++) a0[i] = a[i];
	for (int i = half; i < asz; i++) a0[i-half] += a[i];

	int* b0 = new int[min(bsz, half)];
	for (int i = 0; i < min(bsz, half); i++) b0[i] = b[i];
	for (int i = half; i < bsz; i++) b0[i - half] += b[i];

	vector<int> z2 = karatsuba(a0, half, b0, min(bsz, half));
	
	delete[] a0;
	delete[] b0;

	subFrom(z2, z0);
	subFrom(z2, z1);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z2, half);
	addTo(ret, z1, half + half);
	return ret;
}

int main() {
	USE_TEXTFILE;
	USE_STOPWATCH; //PRINT_TIME(start);

	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cout << fixed;
	cout.precision(10);
	
	int cs; cin >> cs;
	while (cs--) {
		string member;
		string fan;
		cin >> member >> fan;

		int M = member.size();
		int F = fan.size();

		int* members = new int[M];
		memset(members, 0, M);
		int* fans = new int[F];
		memset(fans, 0, F);

		for (int i = 0; i < M; i++) members[M - i - 1] = member[i] == 'M';
		for (int i = 0; i < F; i++) fans[i] = fan[i] == 'M';
		
		vector<int> mulRet = karatsuba(fans, F, members, M);
		
		int ret = 0;
		for (int i = M - 1; i < F; i++)
			if (mulRet[i] == 0)
				ret++;

		PRINT_TIME(start);
		cout << ret << '\n';

		delete[] members;
		delete[] fans;
	}

	return 0;
}
