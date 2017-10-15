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

#define MAX_SIZE 200000

// 자릿수 올림 처리
void normalize(vector<int>& num) {
	int up = 0;
	for (int i = 0; i < num.size(); i++) {
		num[i] += up;
		up = num[i] / 10;
		num[i] %= 10;
	}
	while (up) {
		num.push_back(up % 10);
		up /= 10;
	}
	
	while (num.size() > 1 && num.back() == 0)
		num.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> ret(a.size() + b.size(), 0);

	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			ret[i + j] += a[i] * b[j];
		}
	}

	normalize(ret);
	return ret;
}

// a+=b*(10^k)
void addTo(vector<int>& a, const vector<int>& b, int k) {
	int up = 0;

	while (a.size() < k)a.push_back(0);

	int idx = k;
	// assign to a[idx]
	for (; idx < a.size(); idx++) {
		int sum = a[idx] + up;
		if (idx - k < b.size()) sum += b[idx - k];
		up = sum / 10;
		a[idx] = sum % 10;
	}
	// push_back to a
	for (; up || idx - k < b.size(); idx++) {
		int sum = up;
		if (idx - k < b.size()) sum += b[idx - k];
		up = sum / 10;
		sum %= 10;
		a.push_back(sum);
	}

	return;
}

// a-=b, assume a>=b
void subFrom(vector<int>& a, const vector<int>& b) {
	assert(a.size() >= b.size()); // a<b!!

	for (int i = 0; i < b.size(); i++) {
		a[i] -= b[i];
		if (a[i] < 0) {
			assert(i < a.size() - 1); // a<b!!
			a[i + 1] -= 1;
			a[i] += 10;
		}
	}

	while (a.size() > 1 && a.back() == 0) a.pop_back();

	return;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	if (b.size() > a.size())
		return karatsuba(b, a);

	if (a.size() <= 2 || b.size() <= 2)
		return multiply(a, b);

	int half = a.size() / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + half);
	vector<int> b1(b.begin() + half, b.end());

	vector<int> z0 = karatsuba(a0, b0);
	vector<int> z1 = karatsuba(a1, b1);

	addTo(a0, a1, 0);
	addTo(b0, b1, 0);
	vector<int> z2 = karatsuba(a0, b0);
	subFrom(z2, z0);
	subFrom(z2, z1);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z2, half);
	addTo(ret, z1, half*2);
	return ret;
}

int main() {
	USE_TEXTFILE;
	//USE_STOPWATCH; //PRINT_TIME(start);

	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cout << fixed;
	cout.precision(10);
	
	int cs; cin >> cs;
	while (cs--) {
		string member;
		string fan;
		cin >> member >> fan;

		vector<int> members(member.size(), 0);
		vector<int> fans(fan.size(), 0);

		for (int i = 0; i < member.size(); i++) if (member[i] == 'F') members[i] = 1;
		for (int i = 0; i < fan.size(); i++) if (fan[i] == 'F') fans[i] = 1;

		vector<int> mulRet = karatsuba(fans, members);
		int ret = 0;
		for (int n : mulRet)
			if (n == members.size())
				ret++;

		cout << ret << '\n';
	}

	return 0;
}
