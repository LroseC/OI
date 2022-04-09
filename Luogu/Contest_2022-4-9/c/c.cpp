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

int n, m, K;
int val[N];
int idx, L[N], R[N], invL[N];
int sz[N], dep[N], son[N], fa[N], top[N];
std::vector<int> G[N];
int covTag[N << 2], addTag[N << 2];
int valx[N << 2], sumx[N << 2];

void getSon(int u, int depth)
{
	sz[u] = 1;
	dep[u] = depth;
	for (int v : G[u]) {
		getSon(v, depth + 1);
		sz[u] += sz[v];
		if (sz[v] > sz[son[u]])
			son[u] = v;
	}
}
void initCut(int u, int tp)
{
	L[u] = ++idx;
	invL[idx] = u;
	top[u] = tp;
	if (son[u])
		initCut(son[u], tp);
	for (int v : G[u])
		if (v != son[u])
			initCut(v, v);
	R[u] = idx;
}
void coverNode(int val, int u, int l, int r)
{
	addTag[u] = 0;
	covTag[u] = val;
	valx[u] = (r - l + 1ll) * val % mod;
}
void addNode(int val, int u, int l, int r)
{
	addTag[u] = Mod(addTag[u] + val);
	valx[u] = (valx[u] + (r - l + 1ll) * val) % mod;
}
void maintain(int u)
{
	valx[u] = Mod(valx[u << 1] + valx[u << 1 | 1]);
	sumx[u] = Mod(sumx[u << 1] + sumx[u << 1 | 1]);
}
void spread(int u, int l, int r)
{
	int mid = l + r >> 1;
	if (covTag[u]) {
		coverNode(covTag[u], u << 1, l, mid);
		coverNode(covTag[u], u << 1 | 1, mid + 1, r);
		covTag[u] = 0;
	}
	if (addTag[u]) {
		addNode(addTag[u], u << 1, l, mid);
		addNode(addTag[u], u << 1 | 1, mid + 1, r);
		addTag[u] = 0;
	}
}
void buildVal(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		valx[u] = val[invL[l]];
		return;
	}
	int mid = l + r >> 1;
	buildVal(u << 1, l, mid);
	buildVal(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void addVal(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L > R) return;
	if (L <= l && r <= R) {
		addNode(val, u, l, r);
		return;
	}
	spread(u, l, r);
	int mid = l + r >> 1;
	if (L <= mid)
		addVal(L, R, val, u << 1, l, mid);
	if (R > mid)
		addVal(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
void coverVal(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L > R) return;
	if (L <= l && r <= R) {
		coverNode(val, u, l, r);
		return;
	}
	spread(u, l, r);
	int mid = l + r >> 1;
	if (L <= mid)
		coverVal(L, R, val, u << 1, l, mid);
	if (R > mid)
		coverVal(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int queryVal(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L > R) return 0;
	if (L <= l && r <= R)
		return valx[u];
	spread(u, l, r);
	int mid = l + r >> 1;
	int res = 0;
	if (L <= mid)
		res = Mod(res + queryVal(L, R, u << 1, l, mid));
	if (R > mid)
		res = Mod(res + queryVal(L, R, u << 1 | 1, mid + 1, r));
	return res;
}
void changeSum(int pos, int val, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		sumx[u] = val;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
		changeSum(pos, val, u << 1, l, mid);
	else
		changeSum(pos, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int querySum(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L > R) return 0;
	if (L <= l && r <= R)
		return sumx[u];
	int mid = l + r >> 1;
	int res = 0;
	if (L <= mid)
		res = Mod(res + querySum(L, R, u << 1, l, mid));
	if (R > mid)
		res = Mod(res + querySum(L, R, u << 1 | 1, mid + 1, r));
	return res;
}
void buildSum(int u)
{
	int nowsum = queryVal(L[u] + 1, R[u]);
	if (son[u])
		nowsum = Mod(nowsum + mod - queryVal(L[son[u]], R[son[u]]));
	changeSum(L[u], qpow(nowsum, K));
	for (int v : G[u])
		buildSum(v);
}
void addPath(int u, int v, int w)
{
	addVal(L[u], L[u], w);
	addVal(L[v], L[v], w);
	while (top[fa[u]] != top[fa[v]]) {
		if (dep[top[fa[u]]] < dep[top[fa[v]]])
			std::swap(u, v);
		if (u == top[u]) {
			addVal(L[fa[u]], L[fa[u]], w);
			int tmp = queryVal(L[fa[u]] + 1, R[fa[u]]);
			tmp = Mod(tmp + mod - queryVal(L[son[fa[u]]], R[son[fa[u]]]));
			changeSum(L[fa[u]], tmp);
			u = fa[u];
		}
		else {
			addVal(L[top[u]], L[fa[u]], w);
			u = top[u];
		}
	}
	if (L[fa[u]] > L[fa[v]]) std::swap(u, v);
	addVal(L[fa[u]] + 1, L[fa[v]], w);
	int tmp = queryVal(L[fa[u]] + 1, R[fa[u]]);
	tmp = Mod(tmp + mod - queryVal(L[son[fa[u]]], R[son[fa[u]]]));
	changeSum(fa[u], tmp);
}
void coverPath(int u, int v, int w)
{
	coverVal(L[u], L[u], w);
	coverVal(L[v], L[v], w);
	while (top[fa[u]] != top[fa[v]]) {
		if (dep[top[fa[u]]] < dep[top[fa[v]]])
			std::swap(u, v);
		if (u == top[u]) {
			coverVal(L[fa[u]], L[fa[u]], w);
			int tmp = queryVal(L[fa[u]] + 1, R[fa[u]]);
			tmp = Mod(tmp + mod - queryVal(L[son[fa[u]]], R[son[fa[u]]]));
			changeSum(L[fa[u]], tmp);
			u = fa[u];
		}
		else {
			coverVal(L[top[u]], L[fa[u]], w);
			u = top[u];
		}
	}
	if (L[fa[u]] > L[fa[v]]) std::swap(u, v);
	coverVal(L[fa[u]] + 1, L[fa[v]], w);
	int tmp = queryVal(L[fa[u]] + 1, R[fa[u]]);
	tmp = Mod(tmp + mod - queryVal(L[son[fa[u]]], R[son[fa[u]]]));
	changeSum(fa[u], tmp);
}
int queryPath(int u, int v)
{
	int res = qpow(queryVal(L[u] + 1, R[u]), K);
	res = Mod(res + qpow(queryVal(L[v] + 1, R[v]), K));
	while (top[fa[u]] != top[fa[v]]) {
		if (dep[top[fa[u]]] < dep[top[fa[v]]])
			std::swap(u, v);
		if (u == top[u]) {
			int tmp = queryVal(L[fa[u]] + 1, R[fa[u]]);
			tmp = Mod(tmp + mod - queryVal(L[u], R[u]));
			res = Mod(res + qpow(tmp, K));
			u = fa[u];
		}
		else {
			res = Mod(res + querySum(L[top[u]], L[fa[u]]));
			u = top[u];
		}
	}
	if (L[fa[u]] > L[fa[v]]) std::swap(u, v);
	res = Mod(res + querySum(L[fa[u]] + 1, L[fa[v]]));
	int tmp = queryVal(L[fa[u]] + 1, R[fa[u]]);
	tmp = Mod(tmp + mod - queryVal(L[u], R[u]));
	if (fa[v] == fa[u])
		tmp = Mod(tmp + mod - queryVal(L[v], R[v]));
	else
		tmp = Mod(tmp + mod - queryVal(L[son[fa[u]]], R[son[fa[u]]]));
	res = Mod(res + qpow(tmp, K));
	return res;
}

int main(void)
{
	read >> n >> m >> K;
	for (int i = 2; i <= n; ++i) {
		read >> fa[i] >> val[i];
		G[fa[i]].emplace_back(i);
	}
	getSon(1, 1);
	initCut(1, 1);
	buildVal();
	buildSum(1);
	for (int TIME = 1; TIME <= m; ++TIME) {
		int op, x, y, w;
		read >> op >> x >> y;
		if (op == 1) {
			read >> w;
			addPath(x, y, w);
		}
		else if (op == 2) {
			read >> w;
			coverPath(x, y, w);
		}
		else
			printf("%d\n", queryPath(x, y));
	}
	return 0;
}
