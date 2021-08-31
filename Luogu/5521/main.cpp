#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n;
int w[N];
int flw[N];
vector<int> edge[N];

void AddEdge(int u, int v)
{
	edge[u].emplace_back(v);
}

bool cmp(int a, int b)
{
	return (flw[a] - w[a]) > (flw[b] - w[b]);
}

void dfs(int u)
{
	flw[u] = w[u];
	for (auto v : edge[u]) {
		dfs(v);
		flw[u] += w[v];
	}
	sort(edge[u].begin(), edge[u].end(), cmp);
	int sum = 0;
	for (auto v : edge[u]) flw[u] = max(flw[u], sum + flw[v]), sum += w[v];
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int v = 2; v <= n; ++v) {
		int u; cin >> u;
		AddEdge(u, v);
	}
	for (int i = 1; i <= n; ++i) cin >> w[i];
	dfs(1);
	for (int i = 1; i <= n; ++i) cout << flw[i] << ' ';
	cout << endl;
	return 0;
}