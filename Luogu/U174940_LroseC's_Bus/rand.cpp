#include <set>
#include <random>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, m;
set<int> out[N << 1];
int maxin[N << 1], minout[N << 1];
int fa[N << 1];

random_device srd;
mt19937 rd(srd());

int myrand(int l, int r)
{
	return (int)(1.0 * rd() / UINT_MAX * (r - l) + l + 0.5);
}

int main(void)
{
	ios::sync_with_stdio(false);
	n = 1e5, m = 1e5;
	for (int i = 1; i <= n << 1; ++i) {
		fa[i] = i;
		minout[i] = 1e8;
	}
	cout << n << endl;
	for (int i = 1; i <= n; ++i) {
		int u = myrand(1, n * 2), v = myrand(1, n * 2);
		int tx;
		do tx = myrand(1, 1e8 - 1);
		while (out[u].find(tx) != out[u].end());
		int ty = myrand(tx + 1, 1e8);
		cout << u << ' ' << v << ' ' << tx << ' ' << ty << endl;
	}
	cout << m << endl;
	for (int i = 1; i <= m; ++i) {
		int X = myrand(1, 1e9), Y = myrand(1, n * 2);
		cout << X << ' ' << Y << endl;
	}
	return 0;
}