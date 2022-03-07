#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;

int main(void)
{
	int T; read >> T;
	while (T--) {
		int n; read >> n;
		std::vector<int> a(n);
		bool flag = 1;
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			if (a[i] != 0) flag = 0;
		}
		if (flag) {
			puts("0");
			continue;
		}
		sort(a.begin(), a.end());
		i64 tot = 0;
		for (int i = 0; i < n - 1; ++i) tot += a[i];
		printf("%lld\n", std::max(1ll, a[n - 1] - tot));
	}
	return 0;
}
