#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; read >> tt;
	while (tt--) {
		int n;
		read >> n;
		vint a(n), arr(n), pos(n), cnt(n + 1);
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			arr[i] = i;
		}
		auto cmp = [&](int x, int y)
		{ return a[x] > a[y]; };
		std::sort(arr.begin(), arr.end(), cmp);
		int it = 1;
		i64 res = 0;
		for (auto i : arr) {
			if (cnt[it] == 2) ++it;
			++cnt[it];
			pos[i] = cnt[it] == 1 ? it : -it;
			res += 1ll * it * a[i];
		}
		std::cout << res * 2 << '\n';
		std::cout << 0 << ' ';
		for (int i = 0; i < n; ++i)
			std::cout << pos[i] << ' ';
		std::cout << '\n';
	}
	return 0;
}
