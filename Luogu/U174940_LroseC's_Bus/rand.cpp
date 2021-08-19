#include <random>
#include <climits>
#include <iostream>

using namespace std;

int n, m;

mt19937 rd(time(NULL));

int myrand(int l, int r)
{
	return 1.0 * rd() / UINT_MAX * (r - l + 1) + l + 0.5;
}

int main(void)
{
	ios::sync_with_stdio(false);
	n = 10, m = 10;
	cout << n << endl;
	for (int i = 1; i <= 10; ++i) {
		int u = myrand(1, 20), v = myrand(1, 20);
		int tx = myrand(1, 9), ty = myrand(tx + 1, 10);
		cout << u << ' ' << v << ' ' << tx << ' ' << ty << endl;
	}
	cout << m << endl;
	for (int i = 1; i <= 10; ++i) {
		int X = myrand(1, 10), Y = myrand(1, 20);
		cout << X << ' ' << Y << endl;
	}
	return 0;
}