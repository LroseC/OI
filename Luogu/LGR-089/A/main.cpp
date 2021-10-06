#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
#define int long long
const int MOD = 1e9 + 7;
__int128_t a;

int T;
LL n, k;

__int128_t qpow(__int128_t x, __int128_t k)
{
	__int128_t base = x, res = 1;
	while (k) {
		if (k & 1) res = res * base % MOD;
		base = base * base % MOD;
		k >>= 1;
	}
	return res;
}

__int128_t get_sum(__int128_t a1, __int128_t num)
{
	return (1ll * a1 + (1ll * a1 - num + 1)) * num % MOD * qpow(2, MOD - 2) % MOD;
}

signed main(void)
{
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld%lld", &n, &k);
		if (k == 0) puts("0");
		else {
			__int128_t first = 1ll * n * (n + 1) / 2;
			__int128_t ans = get_sum(first, (k + 1) / 2);
			first = 1ll * n * (n - 1) / 2;
			ans = (ans + get_sum(first, k / 2)) % MOD;
			printf("%lld\n", (long long)(ans % MOD + MOD) % MOD);
		}
	}
	return 0;
}