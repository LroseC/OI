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

const int N = 5e4 + 10, mod = 201314;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct Query
{
	int pos, z, f, id;
	Query(int _p, int _z, int _f, int _id) { pos = _p, z = _z, f = _f, id = _id; }
	bool operator<(const Query &other) { return pos < other.pos; }
};

int n, m;
int ans[N];
int tag[N << 2], sum[N << 2];
int sz[N], son[N], fa[N], top[N];
int idx, L[N], R[N];
std::vector<int> G[N];
std::vector<Query> q;

void addnode(int u, int val, int l, int r)
{
	tag[u] += val;
	sum[u] += val * (r - l + 1);
}
void maintain(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }
void spread(int u, int l, int r)
{
	if (tag[u]) {
		int mid = l + r >> 1;
		addnode(u << 1, tag[u], l, mid);
		addnode(u << 1 | 1, tag[u], mid + 1, r);
		tag[u] = 0;
	}
}
void add(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		addnode(u, val, l, r);
		return;
	}
	spread(u, l, r);
	int mid = l + r >> 1;
	if (L <= mid)
		add(L, R, val, u << 1, l, mid);
	if (R > mid)
		add(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return sum[u];
	spread(u, l, r);
	int mid = l + r >> 1;
	int res = 0;
	if (L <= mid)
		res = Mod(res + query(L, R, u << 1, l, mid));
	if (R > mid)
		res = Mod(res + query(L, R, u << 1 | 1, mid + 1, r));
	return res;
}
void getSz(int u)
{
	sz[u] = 1;
	son[u] = 0;
	for (int v : G[u])
		if (v != fa[u]) {
			getSz(v);
			if (sz[v] > sz[son[u]])
				son[u] = v;
			sz[u] += sz[v];
		}
}
void initCut(int u, int tp)
{
	L[u] = ++idx;
	top[u] = tp;
	if (son[u])
		initCut(son[u], tp);
	for (int v : G[u])
		if (v != fa[u] && v != son[u])
			initCut(v, v);
	R[u] = idx;
}
void addPath(int u)
{
	do {
		add(L[top[u]], L[u], 1);
		u = fa[top[u]];
	} while (u);
}
int queryPath(int u)
{
	int tu = u;
	int res = 0;
	do {
		res = Mod(res + query(L[top[u]], L[u]));
		u = fa[top[u]];
	} while (u);
	return res;
}

int main(void)
{
	read >> n >> m;
	for (int i = 2; i <= n; ++i) {
		read >> fa[i];
		++fa[i];
		G[fa[i]].emplace_back(i);
	}
	for (int i = 1; i <= m; ++i) {
		int l, r, z;
		read >> l >> r >> z;
		++l, ++r, ++z;
		q.emplace_back(r, z, 1, i);
		if (l - 1 > 0)
			q.emplace_back(l - 1, z, -1, i);
	}
	std::sort(q.begin(), q.end());
	getSz(1);
	initCut(1, 1);
	for (int i = 1, j = 0; i <= n; ++i) {
		addPath(i);
		while (j < q.size() && q[j].pos == i) {
			ans[q[j].id] = (ans[q[j].id] + q[j].f * queryPath(q[j].z) + mod) % mod;
			++j;
		}
		if (j == q.size()) break;
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
