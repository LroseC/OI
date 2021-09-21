#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 2e6 + 10, mod = 998244353;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
inline int qpow(int base, int k)
{
	base = base % mod;
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		k >>= 1;
	}
	return res;
}
inline int GetInv(int x)
{
	return qpow(x, mod - 2);
}

int n, q;
int a[N], sum[N];
int inv[N], suminv[N];

int Solve(int l, int r, int k)
{
	int half = r - l >> 1;
	int tmp = min(r - k, k - l);
	int left = 1ll * (sum[k - 1] - sum[l - 1] + mod) * inv[k - l] % mod * (1 + tmp) % mod * tmp % mod * inv[2] % mod;
	int right = 1ll * (sum[r] - sum[k] + mod) * inv[r - k] % mod * (1 + tmp) % mod * tmp % mod * inv[2] % mod;
	int ans = (1ll * (tmp + 1) * a[k] % mod + left + right) % mod;
	ans = 1ll * ans * inv[half + 1] % mod;
	return ans;
}

int main(void)
{
	int t = read();
	// if (t == 0) puts("499122189");
	// else {
		for (int i = 1; i <= 2e6; ++i) {
			inv[i] = GetInv(i);
			suminv[i] = (suminv[i - 1] + inv[i]) % mod;
		}
		n = read(), q = read();
		for (int i = 1; i <= n; ++i) {
			a[i] = read();
			sum[i] = (sum[i - 1] + a[i]) % mod;
		}
		int ans = 0;
		for (int i = 1; i <= q; ++i) {
			int l = read(), r = read(), k = read();
			ans ^= Solve(l, r, k);
		}
		printf("%d\n", ans);
	// }
	return 0;
}