#include <map>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

using PII = pair<int, int>;

int n, idx;
PII P[N];
map<PII, int> M;
int cnt[10];
int color[N];
vector<int> G[N];
int gox[] = {1, -1, 0, 0};
int goy[] = {0, 0, 1, -1};

void dfs(int u, int c)
{
	++cnt[c];
	color[u] = c;
	for (int v : G[u]) {
		if (!color[v]) dfs(v, 3 - c);
	}
}
inline int Paint(int x)
{
	cnt[1] = cnt[2] = 0;
	dfs(x, 1);
	return max(cnt[1], cnt[2]);
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		M[PII({u, v})] = ++idx;
		P[idx] = PII({u, v});
	}
	
	for (int i = 1; i <= n; ++i)
		for (int k = 0; k < 4; ++k) {
			int xx = P[i].first + gox[k];
			int yy = P[i].second + goy[k];
			if (M.count(PII({xx, yy})))
				G[i].emplace_back(M[PII({xx, yy})]);
		}

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (!color[i]) ans += Paint(i);
	}
	printf("%d\n", ans);
	return 0;
}