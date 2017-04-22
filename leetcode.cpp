#pragma region include std
#include <cctype>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
#pragma endregion

class Solution {
public:
	bool solve(string word) {
		return true;
	}
};

class IO {
private:
	ifstream cin;
	ofstream cout;
public:
	IO() {
		cin = ifstream("jinput.txt");
		cout = ofstream("joutput.txt");
	}

	void string_bool() {
		int cases; cin >> cases;
		while (cases--) {
			string str; cin >> str;
			string ret = Solution().solve(str) ? "true" : "false";
			cout << ret << '\n';
		}
	}

	void vint_vint() {
		int cases; cin >> cases;
		while (cases--) {
			vector<int> nums;
			int nsz; cin >> nsz;
			while (nsz--) {
				int num; cin >> num;
				nums.push_back(num);
			}

			vector<int> ret;
			//ret = Solution().solve(nums);
			for (int i = 0; i < ret.size() - 1; i++) {
				cout << ret[i] << ',';
			}
			cout << ret[ret.size() - 1] << '\n';
		}
	}
};

void main() {
	IO().string_bool();
	
	//IO().vint_vint();
}
