#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 5e4 + 10;

int T;
int n, m;
int cnt, mu[N], sum[N], prime[N], v[N], h[N];

int g(int k, int x)
{
	return k / (k / x);
}

void init(void)
{
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!v[i]) {
			v[i] = i;
			mu[i] = -1;
			prime[++cnt] = i;
		}
		for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
			v[i * prime[j]] = prime[j];
			if (v[i] == prime[j]) break;
			mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i < N; ++i) sum[i] = sum[i - 1] + mu[i];
	for (int x = 1; x < N; ++x)
		for (int l = 1, r; l <= x; l = r + 1) {
			r = min(x, g(x, l));
			h[x] += (r - l + 1) * (x / l);
		}
}

int main(void)
{
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		LL res = 0;
		int k = min(n, m);
		for (int l = 1, r; l <= k; l = r + 1) {
			r = min(k, min(g(n, l), g(m, l)));
			res += 1ll * (sum[r] - sum[l - 1]) * h[n / l] * h[m / l];
		}
		printf("%lld\n", res);
	}
	return 0;
}