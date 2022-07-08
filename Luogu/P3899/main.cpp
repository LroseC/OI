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
const int N = 3e5 + 10;
inline int lowbit(int x) { return x & -x; }

int n, m, idx;
vint G[N];
int dep[N], sz[N], L[N], R[N], invL[N];
i64 tr[N], ans[N];
std::vector<PII> q[N];

void add(int x, int v)
{
	for (int i = x; i < N; i += lowbit(i))
		tr[i] += v;
}
i64 query(int x)
{
	i64 res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
void getSz(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	sz[u] = 1;
	L[u] = ++idx;
	invL[idx] = u;
	for (int v : G[u])
		if (v != fa) {
			getSz(v, u);
			sz[u] += sz[v];
		}
	R[u] = idx;
}
void calc(void)
{
	for (int i = 1; i <= n; ++i) {
		int u = invL[i];
		add(dep[u], sz[u] - 1);
		for (auto v : q[i]) {
			if (v.first > 0)
				ans[v.first] += query(v.second);
			else
				ans[-v.first] -= query(v.second);
		}
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	getSz(1, 0);
	for (int i = 1; i <= m; ++i) {
		int a, d;
		read >> a >> d;
		ans[i] += 1ll * std::min(dep[a] - 1, d) * (sz[a] - 1);
		q[L[a]].emplace_back(-i, d + dep[a]);
		q[R[a]].emplace_back(i, d + dep[a]);
	}
	calc();
	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}
