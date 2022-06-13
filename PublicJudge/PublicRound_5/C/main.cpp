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

int main(void)
{
	int n, m;
	read >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		read >> x >> y;
	}
	read >> m;
	for (int i = 1; i <= m; ++i) {
		int x, y;
		read >> x >> y;
		printf("%d\n", std::min(i, n));
	}
	return 0;
}
