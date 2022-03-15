#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 510;

struct Edge
{
	int u, v;
	Edge(void) { u = v = 0; }
	Edge(int u, int v) : u(u), v(v) {}
};

int ans;
int Linecnt, n, m;
int w[N], edgecnt[N];
int match[N], tim[N];
int g[N][N], BG[N][N];
vector<int> nums;
vector<int> G[N];
vector<Edge> edge;

bool Match(int u, int time)
{
	if (tim[u] == time) return 0;
	tim[u] = time;
	for (int v : G[u])
		if (!match[v] || Match(match[v], time)) {
			match[v] = u;
			return 1;
		}
	return 0;
}

void ClearGraph(void)
{
	for (int i = 1; i <= n; ++i) G[i].clear();
	memset(g, 0, sizeof g);
	memset(tim, 0, sizeof tim);
	memset(match, 0, sizeof match);
}

bool check(int xx)
{
	int x = nums[xx];
	ClearGraph();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (BG[i][j] && w[i] <= x && w[j] <= x) G[i].emplace_back(j);
	int res = 0;
	for (int i = 1; i <= n; ++i)
		if (w[i] <= x) {
			res += 1 - Match(i, i);
		}
	return res <= Linecnt + 1;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin >> Linecnt >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> w[i] >> edgecnt[i];
		nums.emplace_back(w[i]);
		for (int j = 1; j <= edgecnt[i]; ++j) {
			int v; cin >> v;
			BG[i][v] = 1;
			edge.emplace_back(i, v);
		}
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				BG[i][j] |= (BG[i][k] & BG[k][j]);

	sort(nums.begin(), nums.end());
	int minw = INT_MAX, maxw = INT_MIN;
	for (int i = 1; i <= n; ++i) {
		minw = min(minw, w[i]);
		maxw = max(maxw, w[i]);
	}
	int l = 0, r = nums.size() - 1;
	if (check(r)) {
		puts("AK");
		return 0;
	}
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid;
	}
	printf("%d\n", nums[l]);
	return 0;
}
