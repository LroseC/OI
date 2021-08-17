#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 5e4 + 10;

int T;
int prime[N], cnt, v[N], sum[N], mu[N];

void shai(void)
{
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!v[i]) {
			v[i] = i; mu[i] = -1;
			prime[++cnt] = i;
		}
		for (int j = 1; j <= cnt; ++j) {
			if (prime[j] > v[i] || prime[j] * i >= N) break;
			v[prime[j] * i] = prime[j];
			mu[prime[j] * i] = -mu[i];
			if (v[i] == prime[j]) mu[prime[j] * i] = 0;
		}
	}
	for (int i = 1; i < N; ++i) sum[i] = sum[i - 1] + mu[i];
}

int g(int k, int x)
{
	return k / (k / x);
}

LL f(int a, int b, int k)
{
	LL res = 0;
	a = a / k, b = b / k;
	int n = min(a, b);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = min(g(a, l), g(b, l));
		r = min(n, r);
		res += 1ll * (sum[r] - sum[l - 1]) * (a / l) * (b / l);
	}
	return res;
}

int main(void)
{
	scanf("%d", &T);
	shai();
	while (T--) {
		int a, b, c, d, k;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		printf("%lld\n", f(b, d, k) - f(a - 1, d, k) - f(b, c - 1, k) + f(a - 1, c - 1, k));
	}
}