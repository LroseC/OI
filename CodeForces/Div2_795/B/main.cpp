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
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		int n; read >> n;
		vint a(n), p(n);
		bool fail = 0;
		int last = 0;
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			if (a[i] != a[last]) {
				if (i - last == 1)
					fail = 1;
				for (int j = last; j < i; ++j)
					p[j] = j + 1;
				p[i - 1] = last;
				last = i;
			}
		}
		if (n - last == 1) fail = 1;
		for (int j = last; j < n; ++j)
			p[j] = j + 1;
		p[n - 1] = last;
		if (fail) puts("-1");
		else {
			for (int i = 0; i < n; ++i)
				printf("%d ", p[i] + 1);
			puts("");
		}
	}
	return 0;
}
