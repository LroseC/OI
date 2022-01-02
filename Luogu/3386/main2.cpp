#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

vector<int> G[N];
int n, m, edgecnt;
int tim[N], match[N];

bool Match(int u, int time)
{
	if (tim[u] == time) return 0;
	tim[u] = time;
	for (int v : G[u]) {
		if (!match[v] || Match(match[v], time)) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	cin >> n >> m >> edgecnt;
	for (int i = 1; i <= edgecnt; ++i) {
		int u, v; cin >> u >> v;
		G[u].emplace_back(v + n);
	}
	memset(tim, 0, sizeof tim);
	memset(match, 0, sizeof match);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += Match(i, i);
	}
	printf("%d\n", ans);
	return 0;
}
