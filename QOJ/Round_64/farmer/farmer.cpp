#include <cctype>
#include <cstdio>
#include <climits>
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

using i64 = long long;
using PII = std::pair<int, int>;
const int N = 1e5 + 10;

int n, m, root;
int ch[N][2];
int val[N], type[N];
int idx, L[N], R[N], invL[N];
int sz[N], fa[N], son[N], dep[N], top[N];
int minx[N << 2][2], maxx[N << 2][2], typex[N << 2], tag[N << 2];
bool isSon[N];

PII merge(PII a, PII b) { return std::make_pair(std::min(a.first, b.first), std::max(a.second, b.second)); }
void getSon(int u, int depth)
{
	sz[u] = 1;
	dep[u] = depth;
	for (int i = 0; i < 2; ++i)
		if (ch[u][i]) {
			fa[ch[u][i]] = u;
			getSon(ch[u][i], depth + 1);
			sz[u] += sz[ch[u][i]];
			if (sz[ch[u][i]] > sz[son[u]])
				son[u] = ch[u][i];
		}
	type[u] = (son[u] == ch[u][1]);
}
void initCut(int u, int tp)
{
	top[u] = tp;
	L[u] = ++idx;
	invL[idx] = u;
	if (son[u])
		initCut(son[u], tp);
	for (int i = 0; i < 2; ++i)
		if (ch[u][i] && ch[u][i] != son[u])
			initCut(ch[u][i], ch[u][i]);
	R[u] = idx;
}
void revnode(int u)
{
	tag[u] ^= 1;
	typex[u] ^= 1;
	std::swap(minx[u][0], minx[u][1]);
	std::swap(maxx[u][0], maxx[u][1]);
}
void maintain(int u)
{
	for (int i = 0; i < 2; ++i) {
		minx[u][i] = std::min(minx[u << 1][i], minx[u << 1 | 1][i]);
		maxx[u][i] = std::max(maxx[u << 1][i], maxx[u << 1 | 1][i]);
	}
}
void spread(int u)
{
	if (tag[u]) {
		revnode(u << 1);
		revnode(u << 1 | 1);
		tag[u] = 0;
	}
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		int ty = type[invL[l]];
		int vl = val[invL[l]];
		typex[u] = ty;
		minx[u][ty] = vl;
		maxx[u][ty] = vl;
		minx[u][ty ^ 1] = INT_MAX;
		maxx[u][ty ^ 1] = INT_MIN;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void changeVal(int pos, int v, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		int ty = typex[u];
		minx[u][ty] = v;
		maxx[u][ty] = v;
		minx[u][ty ^ 1] = INT_MAX;
		maxx[u][ty ^ 1] = INT_MIN;
		return;
	}
	spread(u);
	int mid = l + r >> 1;
	if (pos <= mid)
		changeVal(pos, v, u << 1, l, mid);
	else
		changeVal(pos, v, u << 1 | 1, mid + 1, r);
	maintain(u);
}
void reverse(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		revnode(u);
		return;
	}
	spread(u);
	int mid = l + r >> 1;
	if (L <= mid)
		reverse(L, R, u << 1, l, mid);
	if (R > mid)
		reverse(L, R, u << 1 | 1, mid + 1, r);
	maintain(u);
}
std::pair<int, int> query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return std::make_pair(minx[u][0], maxx[u][1]);
	spread(u);
	int mid = l + r >> 1;
	std::pair<int, int> res = std::make_pair(INT_MAX, INT_MIN);
	if (L <= mid)
		res = merge(res, query(L, R, u << 1, l, mid));
	if (R > mid)
		res = merge(res, query(L, R, u << 1 | 1, mid + 1, r));
	return res;
}
int queryType(int pos, int u = 1, int l = 1, int r = n)
{
	if (l == r)
		return typex[u];
	spread(u);
	int mid = l + r >> 1;
	if (pos <= mid)
		return queryType(pos, u << 1, l, mid);
	else
		return queryType(pos, u << 1 | 1, mid + 1, r);
}
std::pair<int, int> queryPath(int u)
{
	std::pair<int, int> res = std::make_pair(INT_MAX, INT_MIN);
	while (fa[u]) {
		if (top[u] == u) {
			u = fa[u];
			int tp = queryType(u) ^ 1;
			if (tp == 0)
				res.first = std::min(res.first, val[u]);
			else
				res.second = std::max(res.second, val[u]);
			if (!fa[u]) return res;
		}
		u = fa[u];
		res = merge(res, query(L[top[u]], L[u]));
		u = top[u];
	}
	return res;
}
bool check(int u)
{
	if (u == root) return 1;
	auto t = queryPath(u);
	return val[u] < t.first && val[u] > t.second;
}

int main(void)
{
//	freopen("farmer.in", "r", stdin);
//	freopen("farmer.out", "w", stdout);
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		read >> ch[i][0] >> ch[i][1];
		isSon[ch[i][0]] = isSon[ch[i][1]] = 1;
	}
	for (int i = 1; i <= n; ++i)
		if (!isSon[i]) {
			root = i;
			break;
		}
	getSon(root, 1);
	initCut(root, root);
	build();
	while (m--) {
		int opt, x;
		read >> opt >> x;
		if (opt == 1) {
			read >> val[x];
			changeVal(L[x], val[x]);
		}
		else if (opt == 2)
			reverse(L[x], R[x]);
		else
			puts(check(x) ? "YES" : "NO");
	}
	return 0;
}
