#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

int n, m;
int len[N];

int get(LL x)
{
	int cnt = 0;
	LL codelen = 0;
	for (int i = 1; i <= n; ++i) {
		codelen += len[i];
		if (codelen >= x) ++cnt, codelen = 0;
		else if (codelen < 0) codelen = 0;
	}
	return cnt;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> len[i];
	LL l = 1, r = 1e18, mid;
	while (l < r) {
		mid = l + r >> 1;
		if (get(mid) > m) l = mid + 1;
		else r = mid;
	}
	if (get(l) != m) {
		cout << -1 << '\n';
		return 0;
	}
	cout << l << ' ';
	l = 1, r = 1e18, mid;
	while (l < r) {
		mid = l + r + 1 >> 1;
		if (get(mid) >= m) l = mid;
		else r = mid - 1;
	}
	cout << l << '\n';
	return 0;
}