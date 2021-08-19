#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

struct Bus
{
	int u, v, tx, ty;
};

int n, m;
Bus BUS[N];
int truev[N];
vector<pair<int, int>> out[N << 1];

int dfs(int x)
{
	if (truev[x]) return truev[x];
	int v = BUS[x].v, ty = BUS[x].ty;
	auto it = upper_bound(out[v].begin(), out[v].end(), make_pair(ty, -1));
	return truev[x] = it == out[v].end() ? BUS[x].v : dfs(it->second);
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int u, v, tx, ty;
		scanf("%d%d%d%d", &u, &v, &tx, &ty);
		BUS[i] = {u, v, tx, ty};
		out[u].emplace_back(make_pair(tx, i));
	}
	for (int i = 1; i <= n << 1; ++i) {
		sort(out[i].begin(), out[i].end());
	}
	for (int i = 1; i <= n; ++i) {
		if (!truev[i]) dfs(i);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		int st, t;
		scanf("%d%d", &t, &st);
		auto it = upper_bound(out[st].begin(), out[st].end(), make_pair(t, -1));
		printf("%d\n", it == out[st].end() ? st : truev[it->second]);
	}
	return 0;
}