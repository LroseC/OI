#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

char str[110];
i64 pw10[100];

inline int getLen(i64 x)
{
	int res = 0;
	while (x) {
		++res;
		x /= 10;
	}
	return res;
}

int main(void)
{
	pw10[0] = 1;
	for (int i = 1; i < 19; ++i)
		pw10[i] = pw10[i - 1] * 10;
	int tt; read >> tt;
	while (tt--) {
		i64 n;
		read >> n;
		int len = getLen(n);
		i64 ans = -1;
		for (int i = 1; i < len; ++i)
			if (len % i == 0) {
				i64 res = 0;
				i64 x = n / pw10[len - i];
				for (int j = 0; j < len / i; ++j)
					res = res * pw10[i] + x;
				if (res <= n) ans = std::max(ans, res);
				--x;
				if (getLen(x) == i) {
					i64 res = 0;
					for (int j = 0; j < len / i; ++j)
						res = res * pw10[i] + x;
					ans = std::max(ans, res);
				}
			}
		if (ans == -1) {
			for (int i = 0; i < len - 1; ++i)
				putchar('9');
			putchar('\n');
		}
		else printf("%lld\n", ans);
	}
	return 0;
}
