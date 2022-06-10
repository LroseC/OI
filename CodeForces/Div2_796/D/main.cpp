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
i64 sum[N];

int main(void)
{
	int tt; read >> tt;
	while (tt--) {
		read >> n >> K;
		for (int i = 1; i <= n; ++i) {
			read >> a[i];
			sum[i] = sum[i - 1] + a[i];
		}
		if (K <= n) {
			i64 res = 0;
			for (int i = K; i <= n; ++i) {
				res = std::max(res, sum[i] - sum[i - K]);
			}
			res += 1ll * (0 + K - 1) * K / 2;
			printf("%lld\n", res);
		}
		else {
			i64 res = sum[n];
			res += 1ll * (K - 1 + (K - n)) * n / 2;
			printf("%lld\n", res);
		}
	}
	return 0;
}
