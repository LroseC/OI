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
const int N = 2e5 + 10;

int n, K;
int a[N];
int val[N];

void solve(void)
{
	read >> n >> K;
	i64 res = -1ll * K * (K - 1) / 2;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		res += a[i];
		val[i] = (n - i) - a[i];
	}
	std::sort(val + 1, val + 1 + n);
	for (int i = 1; i <= K; ++i)
		res += val[i];
	printf("%lld\n", res);
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		solve();
	}
	return 0;
}
