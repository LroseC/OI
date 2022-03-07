#include <vector>
#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;

const int N = 2e5 + 10, mod = 998244353;
inline int lowbit(int x) { return x & -x; }
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int tr[N];
void add(int x, int val)
{
	for (int i = x; i < N; i += lowbit(i))
		tr[i] = Mod(tr[i] + val);
}
int query(int x)
{
	if (x == 0) return 0;
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		res = Mod(res + tr[i]);
	return res;
}

int n, m, ans;
int s[N], t[N], A[N];
int cnt[N], sum[N], tcnt[N];
int fac[N], inv[N];

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
int Getinv(int x) { return qpow(x, mod - 2); }

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> s[i];
	for (int i = 1; i <= m; ++i)
		read >> t[i];

	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[n] = Getinv(fac[n]);
	for (int i = n - 1; i >= 0; --i)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	int ALLA = fac[n];
	for (int i = 1; i <= n; ++i) {
		++cnt[s[i]]; ++tcnt[t[i]];
		add(s[i], Mod(mod - A[s[i]]));
		A[s[i]] = 1ll * fac[cnt[s[i]]] * inv[cnt[s[i]] - 1] % mod;
		add(s[i], A[s[i]]);
		ALLA = 1ll * ALLA * fac[cnt[s[i]] - 1] % mod;
		ALLA = 1ll * ALLA * inv[cnt[s[i]]] % mod;
	}

	for (int i = 1; i <= std::min(n, m); ++i) {
		ALLA = 1ll * ALLA * inv[n - i + 1] % mod * fac[n - i] % mod;
		ALLA = 1ll * ALLA * fac[cnt[t[i]]] % mod * inv[cnt[t[i]] - 1] % mod;
		ans = Mod(ans + 1ll * query(t[i] - 1) * ALLA % mod);
		if (!cnt[t[i]]) break;
		--cnt[t[i]];
		add(t[i], Mod(mod - A[t[i]]));
		if (cnt[t[i]] == 0) A[t[i]] = 0;
		else A[t[i]] = 1ll * fac[cnt[t[i]]] * inv[cnt[t[i]] - 1] % mod;
		add(t[i], A[t[i]]);
	}
	printf("%d\n", ans);
	return 0;
}
