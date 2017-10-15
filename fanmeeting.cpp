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
	addTo(ret, z0, half*half);
	addTo(ret, z2, half);
	addTo(ret, z1, 0);
	return ret;
}

int main() {
	USE_TEXTFILE;
	USE_STOPWATCH; //PRINT_TIME(start);

	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cout << fixed;
	cout.precision(10);
	
	// test karatsuba()
	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		int a1 = rand() % 10000;
		int a2 = a1;
		int b1 = rand() % 10000;
		int b2 = b1;

		vector<int> arr1;
		while (a2) {
			arr1.push_back(a2 % 10);
			a2 /= 10;
		}

		vector<int> arr2;
		while (b2) {
			arr2.push_back(b2 % 10);
			b2 /= 10;
		}

		vector<int> mulRet = multiply(arr1, arr2);
		int mulRetNum = 0;
		while (!mulRet.empty()) {
			mulRetNum = mulRetNum * 10 + mulRet.back();
			mulRet.pop_back();
		}

		vector<int> karRet = karatsuba(arr1, arr2);
		int karRetNum = 0;
		while (!karRet.empty()) {
			karRetNum = karRetNum * 10 + karRet.back();
			karRet.pop_back();
		}

		string equal = mulRetNum == karRetNum ? "O" : "X";
		cout << equal << ' '
			<< a1 << ' '
			<< b1 << ' '
			<< mulRetNum << ' '
			<< karRetNum << '\n';
	}

	return 0;

	
	int cs; cin >> cs;
	while (cs--) {
		string member;
		string fan;
		cin >> member >> fan;

		bitset<MAX_SIZE> members;
		bitset<MAX_SIZE> fans;

		for (int i = 0; i < member.size(); i++) if (member[i] == 'M') members.set(i);
		for (int i = 0; i < fan.size(); i++) if (fan[i] == 'M') fans.set(i);

		int midx = 0;
		int fidx = 0;
		int cnt = fan.size() - member.size() + 1;
		int ret = 0;
		while (cnt--) {
			bool hug = true;
			for (int i = fidx, j = 0; j < member.size(); i++, j++) {
				if (fans[i] & members[j]) {
					hug = false;
					break;
				}
			}
			if (hug) ret++;
			fidx++;
		}

		PRINT_TIME(start);
		cout << ret << '\n';
	}

	return 0;
}
