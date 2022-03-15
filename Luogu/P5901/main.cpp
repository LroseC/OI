#include <cmath>
#include <cctype>
#include <cstdio>
#include <vector>

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

const int N = 2e5 + 10;
using i64 = long long;

int n, colornum, m, B;
int cnt[N];
int fa[N], sz[N], son[N], color[N], AppearCnt[N];
std::pair<int, int> q[N];
int ans[N];
std::vector<int> G[N];
std::vector< std::pair<int, int> > query1[N], query2[N];

void initSz(int u)
{
	sz[u] = 1;
	for (int v : G[u]) {
		initSz(v);
		sz[u] += sz[v];
		son[u] = sz[v] > sz[son[u]] ? v : son[u];
	}
}
void calc1(int u)
{
	++cnt[color[u]];
	for (int v : G[u])
		calc1(v);
	--cnt[color[u]];
	for (auto t : query1[color[u]]) {
		int q = t.first, id = t.second;
		ans[id] += cnt[q];
	}
}
void insert(int u)
{
	++cnt[color[u]];
	for (int v : G[u])
		insert(v);
}
void clear(int u)
{
	cnt[color[u]] = 0;
	for (int v : G[u])
		clear(v);
}
void calc2(int u, bool flag)
{
	for (int v : G[u])
		if (v != son[u]) calc2(v, 1);
	if (son[u]) calc2(son[u], 0);
	for (int v : G[u])
		if (v != son[u]) insert(v);
	for (auto t : query2[color[u]]) {
		int q = t.first, id = t.second;
		ans[id] += cnt[q];
	}
	if (flag) clear(u);
	else ++cnt[color[u]];
}

int main(void)
{
	read >> n >> colornum >> m;
	B = std::sqrt(n);
	read >> color[1];
	for (int i = 2; i <= n; ++i) {
		read >> fa[i] >> color[i];
		G[fa[i]].emplace_back(i);
		++AppearCnt[color[i]];
	}
	for (int i = 1; i <= m; ++i) {
		read >> q[i].first >> q[i].second;
		if (AppearCnt[q[i].second] <= B)
			query1[q[i].second].emplace_back(q[i].first, i);
		else
			query2[q[i].first].emplace_back(q[i].second, i);
	}
	initSz(1);
	calc1(1);
	calc2(1, 1);
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
