#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;

int n, m;
LL s;
int w[N], v[N];
int cnt[N], val[N];
int L[N], R[N];

inline LL check(int x)
{
	for (int i = 1; i <= n; ++i)
		if (w[i] >= x) {
			cnt[i] = cnt[i - 1] + 1;
			val[i] = val[i - 1] + v[i];
		}
		else {
			cnt[i] = cnt[i - 1];
			val[i] = val[i - 1];
		}
	LL res = 0;
	for (int i = 1; i <= m; ++i)
		res += 1ll * (cnt[R[i]] - cnt[L[i] - 1]) * (val[R[i]] - val[L[i] - 1]);
	return s - res;
}

int main(void)
{
	cin >> n >> m >> s;
	for (int i = 1; i <= n; ++i) cin >> w[i] >> v[i];
	for (int i = 1; i <= m; ++i) cin >> L[i] >> R[i];
	int l = 0, r = 1e6, mid;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(mid) <= 0) l = mid;
		else r = mid - 1;
	}
	cout << min(abs(check(l)), abs(check(l + 1))) << endl;
	return 0;
}