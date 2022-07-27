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

i32 n, k, lim;
i32 cnt[N], a[N];

int check(int gap)
{
	i32 tot = 0;
	for (int i = 1; i <= gap; ++i)
		tot += cnt[i];
	for (int i = 1, j = i + gap - 1; j <= n; i += 1, j += 1) {
		if (tot >= lim) return i;
		tot -= cnt[i];
		tot += cnt[j + 1];
	}
	return 0;
}

void work(void)
{
	read >> n >> k;
	lim = (n - k + 1) / 2 + k;
	std::fill(cnt + 1, cnt + 1 + n, 0);
	for (i32 i = 1; i <= n; ++i) {
		read >> a[i];
		cnt[a[i]] += 1;
	}
	i32 l = 1, r = n, mid;
	while (l < r) {
		mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	i32 lbound = check(l);
	i32 rbound = lbound + l - 1;
	printf("%d %d\n", lbound, rbound);
	i32 tot = 0;
	i32 last = 1;
	for (int i = 1; i <= n; ++i) {
		tot += (lbound <= a[i] && a[i] <= rbound) ? 1 : -1;
		if (tot == 1 && k > 1) {
			printf("%d %d\n", last, i);
			tot = 0;
			last = i + 1;
			k -= 1;
		}
	}
	printf("%d %d\n", last, n);
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
}
