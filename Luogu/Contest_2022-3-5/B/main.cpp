#include <vector>
#include <cctype>
#include <cstdio>
#include <cassert>

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
const int mod = 998244353;

int n, m;
std::vector< std::vector<int> > val, sum;

int Mod(int x) { return x >= mod ? x - mod : x; }
int calc1(void)
{
	int res = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			res = Mod(res + 1ll * val[i][j] * i % mod * j % mod * (n - i + 1) % mod * (m - j + 1) % mod);
	return res;
}
int calc2(void)
{
	int ans = 0, top;
	std::vector<int> stk(m + 1);
	std::vector< std::vector<int> > up, v;
	v.resize(n + 1);
	up.resize(n + 1);
	for (int i = 0; i <= n; ++i) {
		v[i].resize(m + 1);
		up[i].resize(m + 1);
	}

	for (int k = 0; k < 32; ++k) {
		int res = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				v[i][j] = (val[i][j] >> k & 1);

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				up[i][j] = v[i - 1][j] == 0 ? 1 : up[i - 1][j] + 1;
				if (v[i][j] == 0) up[i][j] = 0;
			}

		for (int i = 1; i <= n; ++i) {
			top = 0;
			int tot = 0;
			for (int j = 1; j <= m; ++j) {
				while (top && up[i][stk[top]] >= up[i][j]) {
					tot -= (up[i][stk[top]] - up[i][j]) * (stk[top] - stk[top - 1]);
					--top;
				}
				tot += (up[i][j]);
				stk[++top] = j;
				res = Mod(res + tot);
			}
		}
		ans = (ans + (1ll * res << k) % mod) % mod;
	}
	return ans;
}
int calc3(void)
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			val[i][j] ^= (1ll << 32) - 1;

	i64 ans = 1ll * n * (n + 1) / 2 * m * (m + 1) / 2 % mod;
	ans = (ans * (((1ll << 32) - 1) % mod)) % mod;
	ans -= calc2();
	ans = (ans % mod + mod) % mod;

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			val[i][j] ^= (1ll << 32) - 1;
	return ans % mod;
}
int calc4(void)
{
	int res = 0;
	if (1ll * n * (n - 1) / 2 * m * (m - 1) / 2 > 1e8)
		return -1;
	sum.resize(n + 1);
	sum[0].resize(m + 1);
	for (int i = 1; i <= n; ++i) {
		sum[i].resize(m + 1);
		for (int j = 1; j <= m; ++j)
			sum[i][j] = sum[i - 1][j] ^ sum[i][j - 1] ^ sum[i - 1][j - 1] ^ val[i][j];
	}
	for (int lx = 1; lx <= n; ++lx)
		for (int ly = 1 ; ly <= m; ++ly)
			for (int rx = lx; rx <= n; ++rx)
				for (int ry = ly; ry <= m; ++ry) {
					int t = res;
					res = (res + (sum[rx][ry] ^ sum[lx - 1][ry] ^ sum[rx][ly - 1] ^ sum[lx - 1][ly - 1])) % mod;
				}
	return res;
}

int main(void)
{
	read >> n >> m;
	val.resize(n + 1);
	val[0].resize(m + 1);
	for (int i = 1; i <= n; ++i) {
		val[i].resize(m + 1);
		for (int j = 1; j <= m; ++j)
			read >> val[i][j];
	}
	printf("%d %d %d %d\n", calc1(), calc2(), calc3(), calc4());
	return 0;
}
