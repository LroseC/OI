#include <vector>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 2e5 + 10;
inline i32 lowbit(i32 x) { return x & -x; }

i32 n;
i32 a[N], cnt[N], vis[N], tr[N];

void add(i32 x, i32 v)
{
	x += 1;
	for (int i = x; i <= n + 1; i += lowbit(i)) {
		tr[i] += v;
	}
}
i32 query(i32 x)
{
	x += 1;
	i32 res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}

void work(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		++cnt[a[i]];
	}
	for (int i = 0; i <= n; ++i) {
		if (cnt[i] > 0)
			add(i, 1);
	}
	vi32 ans;
	i32 pos = 1;
	while (query(n) > 0) {
		int l = 0, r = n;
		while (l < r) {
			i32 mid = l + r + 1 >> 1;
			if (query(mid) == mid + 1)
				l = mid;
			else
				r = mid - 1;
		}
		if (query(l) != l + 1) {
			for (int i = pos; i <= n; ++i)
				ans.emplace_back(0);
			break;
		}
		ans.emplace_back(l + 1);
		i32 tot = l + 1;
		std::fill(vis, vis + l + 1, 0);
		while (tot) {
			if (!vis[a[pos]] && a[pos] <= l) {
				vis[a[pos]] = 1;
				tot -= 1;
			}
			cnt[a[pos]] -= 1;
			if (!cnt[a[pos]])
				add(a[pos], -1);
			pos += 1;
		}
	}
	std::fill(cnt, cnt + 1 + n, 0);
	std::fill(tr, tr + 2 + n, 0);
	printf("%d\n", ans.size());
	for (auto v : ans)
		printf("%d ", v);
	puts("");
}
int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
