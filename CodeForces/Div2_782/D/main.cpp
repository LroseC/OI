#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
inline int lowbit(int x) { return x & -x; }

void add(int x, int v, std::vector<i64> &tr)
{
	for (int i = x; i < tr.size(); i += lowbit(i))
		tr[i] += v;
}
i64 query(int x, std::vector<i64> &tr)
{
	i64 res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		vint a(n + 1);
		vint is(n + 1);
		std::vector<i64> tr(n + 2);
		i64 sum = 0;
		for (int i = 1; i <= n; ++i) {
			std::cin >> a[i];
			sum += a[i];
		}
		int cnt1 = sum / n;
		for (int i = 1; i <= n; ++i) {
			add(i, a[i] - a[i - 1], tr);
		}
		for (int i = n; i >= 1; --i) {
			add(i - cnt1 + 1, -1, tr);
			add(i + 1, 1, tr);
			is[i] = (bool)query(i, tr);
			if (i == 1) is[i] = cnt1 > 0;
			cnt1 -= is[i];
		}
		for (int i = 1; i <= n; ++i)
			std::cout << is[i] << ' ';
		std::cout << '\n';
	}
	return 0;
}
