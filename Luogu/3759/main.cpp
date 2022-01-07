#include <cstdio>
#include <iostream>

using namespace std;

using LL = long long;
const int N = 5e4 + 10, mod = 1e9 + 7;
inline int lowbit(int x) { return x & -x; }

int n, m;
LL ans;
LL pos[N], page[N];
LL sum[N];
LL cnt[N];

void add(int k, int val)
{
	for (int i = k; i; i -= lowbit(i)) {
		++cnt[i];
		sum[i] = sum[i] + val;
	}
}
pair<LL, LL> query(int k)
{
	pair<LL, LL> res = make_pair(0, 0);
	for (int i = k; i < N; i += lowbit(i)) {
		res.first = res.first + cnt[i];
		res.second = res.second + sum[i];
	}
	return res;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> pos[i] >> page[i];
		auto t = query(pos[i]);
		ans = ans + t.first * page[i] + t.second;
		add(pos[i], page[i]);
	}
	for (int i = 1; i <= m; ++i) {
		int x, y;
		cin >> x >> y;
		if (x > y) swap(x, y);
		for (int i = x + 1; i < y; ++i) {
			if (pos[i] < pos[x])
				ans -= page[i] + page[x];
			if (pos[i] > pos[x])
				ans += page[i] + page[x];
			if (pos[i] > pos[y])
				ans -= page[i] + page[y];
			if (pos[i] < pos[y])
				ans += page[i] + page[y];
		}
		if (pos[x] > pos[y])
			ans -= page[x] + page[y];
		if (pos[x] < pos[y])
			ans += page[x] + page[y];
		swap(pos[x], pos[y]);
		swap(page[x], page[y]);
		printf("%d\n", (ans % mod + mod) % mod);
	}
	return 0;
}
