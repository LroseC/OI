#include <vector>
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
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 5e4 + 10;

int n, m;
int prime[N], v[N], idx;
i64 g[N], sum[N], mu[N];

void init(void)
{
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!v[i]) {
			v[i] = i;
			mu[i] = -1;
			prime[++idx] = i;
		}
		for (int j = 1; j <= idx && i * prime[j] < N; ++j) {
			v[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) mu[i * prime[j]] = 0;
			else mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i < N; ++i) {
		sum[i] = sum[i - 1] + mu[i];
		for (int l = 1, r; l <= i; l = r + 1) {
			r = i / (i / l);
			g[i] += 1ll * (i / l) * (r - l + 1);
		}
	}
}

int main(void)
{
	//Think twice, code once.
	init();
	int tt; read >> tt;
	while (tt--) {
		read >> n >> m;
		i64 ans = 0;
		for (int l = 1, r; l <= std::min(n, m); l = r + 1) {
			r = std::min(n / (n / l), m / (m / l));
			ans += 1ll * g[n / l] * g[m / l] * (sum[r] - sum[l - 1]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
