#include <queue>
#include <iostream>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int N = 1e3 + 10, M = 2e3 + 10;

int n;
int c[N], t[N];
bool chose[N];
LL ans = 1e18;
queue<int> q;
int idx, head[N], nex[M], to[M];
int dis[N];

void AddEdge(int u, int v)
{
	nex[++idx] = head[u];
	head[u] = idx; to[idx] = v;
}
LL calc(void)
{
	bool flag = 1;
	for (int i = 1; i <= n; ++i) {
		dis[i] = -1;
		if (chose[i]) flag = 0;
	}
	if (flag) return ans;
	while (q.size()) q.pop();
	for (int i = 1; i <= n; ++i)
		if (chose[i]) {
			q.emplace(i);
			dis[i] = 0;
		}
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int e = head[u]; e; e = nex[e]) {
			int v = to[e];
			if (dis[v] != -1) continue;
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}

	LL res = 0;
	for (int i = 1; i <= n; ++i)
		if (chose[i]) res += c[i];
	for (int i = 1; i <= n; ++i) res += t[dis[i]];
	return res;
}

void dfs(int x)
{
	if (x > n) {
		ans = min(ans, calc());
		return;
	}
	dfs(x + 1);
	chose[x] = 1;
	dfs(x + 1);
	chose[x] = 0;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> c[i];
	for (int i = 1; i <= n; ++i) cin >> t[i];
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
	dfs(1);
	cout << ans << endl;
	return 0;
}