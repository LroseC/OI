#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

struct Query
{
	int d, s, t;
};

int n, m;
int r[N];
Query q[N];
int f[N];

inline bool check(int x)
{
	memset(f, 0, sizeof f);
	for (int i = 1; i <= x; ++i) {
		f[q[i].s] -= q[i].d;
		f[q[i].t + 1] += q[i].d;
	}
	for (int i = 1; i <= n; ++i) f[i] += f[i - 1];
	for (int i = 1; i <= n; ++i) {
		f[i] += r[i];
		if (f[i] < 0) return 0;
	}
	return 1;
}

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> r[i];
	for (int i = 1; i <= m; ++i)
		scanf("%d%d%d", &q[i].d, &q[i].s, &q[i].t);
	int l = 0, r = m, mid;
	while (l < r) {
		mid = l + r + 1 >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	if (l == m) cout << 0 << endl;
	else cout << -1 << endl << l + 1 << endl;
	return 0;
}