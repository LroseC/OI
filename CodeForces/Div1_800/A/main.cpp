#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using u64 = unsigned long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		int n; read >> n;
		vint a(n);
		std::vector<i64> b(n);
		for (int i = 0; i < n; ++i) {
			read >> a[i];
		}
		for (int i = n - 1, flag = 0; i >= 1; --i) {
			if (a[i] == 0 && flag == 0) continue;
			flag = 1;
			i64 del = std::max(1ll, b[i] - a[i]);
			b[i] -= del;
			b[i - 1] += del;
		}
		bool fail = 0;
		for (int i = 0; i < n; ++i)
			if (a[i] != b[i]) fail = 1;
		puts(fail ? "No" : "Yes");
	}
	return 0;
}
