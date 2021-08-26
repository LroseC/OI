#include <iostream>

using namespace std;

typedef long long LL;
const int N = 5e5 + 10, M = 1e6 + 10;

int n, S;
LL ans;
LL d[N];
int idx, head[N], nex[M], to[M], w[M];

void AddEdge(int u, int v, int wi)
{
	nex[++idx] = head[u]; w[idx] = wi;
	head[u] = idx; to[idx] = v;
}
void dfs(int u, int fa)
{
	d[u] = 0;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		dfs(v, u);
		d[u] = max(d[u], d[v] + w[e]);
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		ans += (d[u] - d[v] - w[e]);
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin >> n >> S;
	for (int i = 1; i < n; ++i) {
		int u, v, t;
		cin >> u >> v >> t;
		AddEdge(u, v, t); AddEdge(v, u, t);
	}
	dfs(S, -1);
	cout << ans << endl;
	return 0;
}