#include <vector>
#include <cctype>
#include <cstdio>

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
} read;

const int N = 5e5 + 10;

struct Edge
{
	int v, id;
	Edge(void) { v = id = 0; }
	Edge(int _v, int _id) : v(_v), id(_id) {}
};

int n, m;
using LL = long long;

vector<Edge> G[N];
vector<int> Add[N];
vector<int> Dec[N];

int idx;
int id[N], sz[N], fa[N], son[N], dep[N], top[N];

void Getsz(int u, int father)
{
	dep[u] = dep[father] + 1;
	sz[u] = 1;
	for (auto t : G[u])
		if (t.v != father) {
			Getsz(t.v, u);
			if (sz[t.v] > sz[son[u]])
				son[u] = t.v;
			sz[u] += sz[t.v];
		}
}
void dfs(int u, int tp)
{
	top[u] = tp;
	if (son[u]) dfs(son[u], tp);
	for (auto t : G[u]) {
		if (t.v == father || t.v == son[u]) continue;
		dfs(v, v);
	}
}
int LCA(int u, int v)
{
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v])
		swap(u, v); return v;
}

namespace SegmentTree
{
	const int M = 2e6 + 10;
	int cnt[M];
	namespace BIT
	{
		LL tr[M];
		inline int lowbit(int x) { return x & -x; }

		void add(int pos, int val)
		{
			for (int i = pos; i < M; i += lowbit(i))
				tr[i] += val;
		}
		int query(void)
		{
			int ans = 0;
			for (int i = 21; i >= 0; --i) {
				if (ans + (1 << i) >= M) continue;
				if (tr[ans + (1 << i)] == (1 << i))
					ans += 1 << i;
			}
			return ans;
		}
	}

	void add(int pos, int val)
	{
		if (cnt[pos] == 0) BIT::add(pos, 1);
		cnt[pos] += val;
		if (cnt[pos] == 0) BIT::add(pos, -1);
	}
	int query(void)
	{
		return BIT::query();
	}
}
void calc(int u, int father, int id)
{
	for (auto t : G[u])
		if (t.v != father)
			calc(t.v, u, t.id);
	for (int w : Add[u])
		SegmentTree::add(w, 1);
	for (int w : Dec[u])
		SegmentTree::add(w, -2);
	ans[id] = SegmentTree::query();
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v, i);
		G[v].emplace_back(u, i);
	}
	Getsz(1, 0);
	dfs(1, 1);
	for (int i = 1; i <= m; ++i) {
		int s, t, w;
		read >> s >> t >> w;
		Add[s].emplace_back(w);
		Add[t].emplace_back(w);
		Dec[LCA(s, t)].emplace_back(w);
	}
	calc(1, 1, 0);
	for (int i = 1; i < n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
