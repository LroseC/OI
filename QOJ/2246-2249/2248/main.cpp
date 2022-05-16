#include <queue>
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
using PII = std::pair<int, int>;
const int N = 2e5 + 10;

int n, m, mod;
PII f[N];
int inEdge[N];
int fac[N], inv[N];
std::vector<int> G[N];

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
inline int C(int n, int m)
{
	if (n < 0 || m < 0 || n < m) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
PII merge(PII a, PII b)
{
	PII res;
	res.first = a.first + b.first;
	res.second = 1ll * a.second * b.second % mod * C(res.first, a.first) % mod;
	return res;
}
void toposort(void)
{
	std::queue<int> q;
	for (int i = 1; i <= n; ++i) {
		if (!inEdge[i]) q.emplace(i);
		f[i] = std::make_pair(0, 1);
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		++f[u].first;
		for (int v : G[u]) {
			f[v] = merge(f[v], f[u]);
			--inEdge[v];
			if (inEdge[v] == 0)
				q.emplace(v);
		}
	}
}

void solve(void)
{
	read >> n >> m >> mod;

	fac[0] = 1;
	for (int i = 1; i < n + 10; ++i)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[n + 10 - 1] = getInv(fac[n + 10 - 1]);
	for (int i = n + 10 - 2; i >= 0; --i)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	for (int i = 1, u, v; i <= m; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		++inEdge[v];
	}
	toposort();
	PII res = std::make_pair(0, 1);
	//first->cnt, second->res;
	for (int i = 1; i <= n; ++i)
		if (!G[i].size())
			res = merge(res, f[i]);
	for (int i = 1; i <= n; ++i) {
		G[i].clear();
		inEdge[i] = 0;
	}
	printf("%d\n", res.second);
}

int main(void)
{
	int T; read >> T;
	while (T--)
		solve();
	return 0;
}
