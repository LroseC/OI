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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

struct Query
{
	int op;
	int u, v;

	Query(void) {}
	Query(int _op, int _u, int _v) { op = _op, u = _u, v = _v; }
};

using i64 = long long;
const int N = 1e5 + 10;
inline int lowbit(int x) { return x & -x; }

int n, m;
int rt[N];
std::vector<Query> q;
std::vector<int> G[N];
int idx, L[N], R[N];
int fa[N], dep[N];
i64 tr[N];

int find(int x) { return x == rt[x] ? x : rt[x] = find(rt[x]); }
void add(int x, int val)
{
	++x;
	for (int i = x; i < N; i += lowbit(i))
		tr[i] += val;
}
i64 query(int x)
{
	++x;
	i64 res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
void getFa(int u)
{
	L[u] = ++idx;
	dep[u] = dep[fa[u]] + 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			getFa(v);
		}
	R[u] = idx;
}

int main(void)
{
	read >> n >> m;
	q.resize(m);
	for (int i = 0; i < m; ++i) {
		char op[3];
		scanf("%s", op);
		q[i].op = op[0] == 'Q';
		read >> q[i].u >> q[i].v;
		if (!q[i].op) {
			G[q[i].u].emplace_back(q[i].v);
			G[q[i].v].emplace_back(q[i].u);
		}
	}
	for (int i = 1; i <= n; ++i)
		if (!fa[i]) getFa(i);
	for (int i = 1; i <= n; ++i) {
		add(L[i], 1);
		add(L[fa[i]], -1);
	}
	for (int i = 1; i <= n; ++i)
		rt[i] = i;
	for (int i = 0; i < m; ++i) {
		int op = q[i].op, u = q[i].u, v = q[i].v;
		if (dep[u] < dep[v])
			std::swap(u, v);
		if (op == 0) {
			rt[find(u)] = find(v);
			int sz = query(R[u]) - query(L[u] - 1);
			add(L[v], sz);
			add(L[fa[find(v)]], -sz);
		}
		else {
			int root = find(u);
			int totsz = query(R[root]) - query(L[root] - 1);
			int szu = query(R[u]) - query(L[u] - 1);
			printf("%lld\n", 1ll * szu * (totsz - szu));
		}
	}
	return 0;
}
