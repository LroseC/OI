#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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

struct PII
{
	int x, y;
	PII(void) { x = y = 0; }
	PII(int x, int y) : x(x), y(y) {}
};

using LL = long long;
const int N = 1e5, M = 3e5;

int n, m;
int cnt[N];
PII edge[M];
LL ans[3], totans;
LL tans[2];
vector<int> G[N];
int fa[N];

void dfs(int u, int fa, int root, int dep)
{
	if (dep == 3) {
		++ans[u == root];
		return;
	}
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u, root, dep + 1);
	}
}

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x != y)
		fa[x] = y;
}

bool check(int i, int j, int k)
{
	vector<int> tmp;
	tmp.emplace_back(edge[i].x);
	tmp.emplace_back(edge[i].y);
	tmp.emplace_back(edge[j].x);
	tmp.emplace_back(edge[j].y);
	tmp.emplace_back(edge[k].x);
	tmp.emplace_back(edge[k].y);
	for (int u : tmp) fa[u] = u;
	merge(edge[i].x, edge[i].y);
	merge(edge[j].x, edge[j].y);
	merge(edge[k].x, edge[k].y);
	for (int i = 0; i < tmp.size(); ++i)
		for (int j = i + 1; j < tmp.size(); ++j)
			if (find(tmp[i]) != find(tmp[j])) return 0;
	sort(tmp.begin(), tmp.end());
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	if (tmp.size() == 3) ++tans[1];
	else ++tans[0];
	return 1;
}

int calc(int x)
{
	if (x < 3) return 0;
	return 1ll * x * (x - 1) * (x - 2) / 6;
}

int main(void)
{
	IO >> n >> m;
	for (int i = 1; i <= m; ++i) {
		IO >> edge[i].x >> edge[i].y;
		G[edge[i].x].emplace_back(edge[i].y);
		G[edge[i].y].emplace_back(edge[i].x);
	}
//	for (int i = 1; i <= m; ++i)
//		for (int j = i + 1; j <= m; ++j)
//			for (int k = j + 1; k <= m; ++k)
//				if (check(i, j, k)) ++totans;
	for (int i = 1; i <= n; ++i) dfs(i, i, i, 0);
	for (int i = 1; i <= n; ++i)
		ans[2] += calc(G[i].size());
	printf("%lld\n", ans[0] / 2 + ans[1] / 6 + ans[2]);
	return 0;
}
