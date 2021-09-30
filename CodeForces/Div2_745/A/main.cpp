#include <cstdio>

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

int inv2;
int factor[N];

int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}

int main(void)
{
	inv2 = qpow(2, mod - 2);
	factor[0] = 1;
	for (int i = 1; i < N; ++i) factor[i] = 1ll * factor[i - 1] * i % mod;

	int t;
	scanf("%d", &t);
	while (t--) {
		int n; scanf("%d", &n); n *= 2;
		printf("%d\n", 1ll * factor[n] * inv2 % mod);
	}
	return 0;
}