#include <cctype>
#include <cstdio>
#include <vector>
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
using PII = std::pair<int, int>;
const int N = 5e3 + 10, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}
inline int getInv(int x) { return qpow(x, mod - 2); }

int fac[N], inv[N];
inline int C(int n, int m)
{
	if (n < m || n < 0 || m < 0) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
inline void sort(std::vector<PII> &tmp)
{
	static std::vector<PII> array[N];
	for (auto v : tmp) {
		array[v.first].emplace_back(v);
	}
	tmp.clear();
	for (int i = 0; i < N; ++i)
		if (array[i].size()) {
			for (auto v : array[i])
				tmp.emplace_back(v);
			array[i].clear();
		}
}

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = getInv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	int tt; read >> tt;
	while (tt--) {
		int n, m, maxE = -1;
		read >> n >> m;
		std::vector<PII> lim;
		for (int i = 0; i < m; ++i) {
			int x, y;
			read >> x >> y;
			if (x != y) {
				lim.emplace_back(std::make_pair(x, y));
			}
			else {
				maxE = std::max(maxE, x);
			}
		}
		int ans = 0;
		for (int type = 0; type < 3; ++type) {
			for (int i = 0; i <= n; ++i) {
				std::vector<PII> vc;
				for (auto v : lim) {
					int x = v.first, y = v.second;
					if (x > y) vc.emplace_back(x, y);
					else vc.emplace_back(n - y, i - x);
				}
				if (maxE != -1) {
					if (type == 0)
						vc.emplace_back(maxE, maxE);
					else if (type == 1)
						vc.emplace_back(n - maxE, i - maxE);
					else {
						vc.emplace_back(maxE, maxE);
						vc.emplace_back(n - maxE, i - maxE);
					}
				}
				vc.emplace_back(0, 0);
				vc.emplace_back(n, i);
				sort(vc);
				int res = 1;
				for (int j = 0; j < vc.size() - 1; ++j) {
					int delx = vc[j + 1].first - vc[j].first;
					int dely = vc[j + 1].second - vc[j].second;
					res = 1ll * res * C(delx, dely) % mod;
				}
				if (type != 2)
					ans = Mod(ans + res);
				else ans = Mod(ans + mod - res);
				// printf("res(i = %d, type = %d) = %d\n", i, type, res);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
