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
using uint = unsigned int;
const int N = 1e7 + 10;
uint SEED;

inline uint get_next(void)
{
	SEED ^= SEED << 13;
	SEED ^= SEED >> 17;
	SEED ^= SEED << 5;
	return SEED;
}

int n;
uint a[N], fa[N];

int main(void)
{
	read >> n >> SEED;
	for (int i = 1; i <= n; ++i) {
		a[i] = get_next();
	}
	fa[1] = 1;
	for (int i = 2; i <= n; ++i) {
		fa[i] = get_next() % (i - 1) + 1;
	}
	i64 res = 0;
	for (int i = 1; i <= n; ++i) {
		a[i] = std::min(a[i], a[fa[i]]);
		res += a[i];
	}
	printf("%lld\n", res);
	return 0;
}
