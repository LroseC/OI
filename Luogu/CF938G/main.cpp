#include <map>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

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
} IO;

const int N = 1e6 + 10;
using pii = pair<int, int>;

struct Edge
{
	int x, y, d;
	Edge(void) { x = y = d = 0; }
	Edge(int x, int y, int d) : x(x), y(y), d(d) {}
};

int n, m, q;
pii query[N];
map<pii, pii> M;

pii stk[N]; int top;
int fa[N], sz[N], dis[N];

vector<Edge> tr[N << 2];

int find(int x)
{
	return x == fa[x] ? x : find(fa[x]);
}
int getdis(int x)
{
	return x == fa[x] ? 0 : getdis(fa[x]) ^ dis[x];
}
void merge(int x, int y, int d)
{
	x = find(x), y = find(y);
	if (sz[x] > sz[y]) swap(x, y);
	fa[x] = y;
	dis[x] = d;
	sz[y] += sz[x];
	stk[++top] = make_pair(x, y);
}
void undo(void)
{
	auto t = stk[top]; --top;
	int x = t.first, y = t.second;
	fa[x] = x;
	dis[x] = 0;
	sz[y] -= sz[x];
}

int base[32];
void insert(int x)
{
	for (int k = 31; k >= 0; --k)
		if (x >> k & 1) {
			if (!base[k]) {
				base[k] = x;
				return;
			}
			x ^= base[k];
		}
}
int Query(int x)
{
	for (int k = 31; k >= 0; --k)
		if (x >> k & 1) x ^= base[k];
	return x;
}

void add(int L, int R, int x, int y, int d, int u = 1, int l = 1, int r = q)
{
	if (L <= l && r <= R) {
		tr[u].emplace_back(x, y, d);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, x, y, d, u << 1, l, mid);
	if (R > mid) add(L, R, x, y, d, u << 1 | 1, mid + 1, r);
}
void calc(int u = 1, int l = 1, int r = q)
{
	int g[32]; memcpy(g, base, sizeof g);
	int bk = top;
	for (auto t : tr[u]) {
		int x = find(t.x), y = find(t.y);
		int d = t.d ^ getdis(t.x) ^ getdis(t.y);
		if (x == y) insert(d);
		else merge(x, y, d);
	}
	if (l == r) {
		if (query[l].first) {
			int d = getdis(query[l].first) ^ getdis(query[l].second);
			printf("%d\n", Query(d));
		}
	}
	else {
		int mid = l + r >> 1;
		calc(u << 1, l, mid);
		calc(u << 1 | 1, mid + 1, r);
	}
	while (top != bk) undo();
	memcpy(base, g, sizeof base);
}

int main(void)
{
	IO >> n >> m;
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		sz[i] = 1;
	}
	for (int i = 1; i <= m; ++i) {
		int x, y, d; IO >> x >> y >> d;
		M[make_pair(x, y)] = make_pair(1, d);
	}
	IO >> q;
	for (int i = 1; i <= q; ++i) {
		int op; IO >> op;
		if (op == 1) {
			int x, y, d; IO >> x >> y >> d;
			M[make_pair(x, y)] = make_pair(i, d);
		}
		if (op == 2) {
			int x, y; IO >> x >> y;
			if (!M.count(make_pair(x,y))) continue;
			auto t = M[make_pair(x, y)];
			M.erase(make_pair(x, y));
			add(t.first, i, x, y, t.second);
		}
		if (op == 3) {
			int x, y; IO >> x >> y;
			query[i] = make_pair(x, y);
		}
	}
	for (auto t : M) {
		auto fir = t.first, sec = t.second;
		add(sec.first, q, fir.first, fir.second, sec.second);
	}
	calc();
	return 0;
}
