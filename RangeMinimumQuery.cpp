#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class RMQ {
	int n;
	vector<int> rangeMin; // 각 구간의 최소치

	int init(const vector<int>& arr, int node, int left, int right);
	int query(int left, int right, int node, int nodeLeft, int nodeRight);
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight);
public:
	RMQ(const vector<int>& arr) {
		n = arr.size();
		rangeMin.resize(4 * n);
		init(arr, 1, 0, n-1);
	}
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
	void update(int index, int newValue) {
		update(index, newValue, 1, 0, n - 1);
	}
};

int RMQ::init(const vector<int>& arr, int node, int left, int right) {
	if (left == right) return rangeMin[node] = arr[left];

	int mid = (left + right) / 2;
	int leftMin = init(arr, node * 2, left, mid);
	int rightMin = init(arr, node * 2 + 1, mid + 1, right);

	return rangeMin[node] = min(leftMin, rightMin);
}

int RMQ::query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight) return 1 << 30;

	if (left <= nodeLeft && right >= nodeRight) return rangeMin[node];

	int mid = (nodeLeft + nodeRight) / 2;
	return min(query(left, right, node * 2, nodeLeft, mid)
		, query(left, right, node * 2+1, mid+1, nodeRight));
}

int RMQ::update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight) return rangeMin[node];
	if (nodeLeft == nodeRight) return rangeMin[node] = newValue;

	int mid = (nodeLeft + nodeRight) / 2;
	return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid)
		, update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
}

int main() {
	vector<int> vect({ 5, 4, 2, 8, 9, 1, 6, 3, 7 });
	
	RMQ rmq(vect);
	cout << "1 = " << rmq.query(3, 5) << endl;
	cout << "2 = " << rmq.query(1, 4) << endl;
	cout << "3 = " << rmq.query(6, 8) << endl;

	rmq.update(5, 10);
	cout << "8 = " << rmq.query(3, 5) << endl;
	cout << "2 = " << rmq.query(0, 8) << endl;

	return 0;
}
