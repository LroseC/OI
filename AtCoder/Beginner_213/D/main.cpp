#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n;
vector<int> to[N];

void dfs(int u, int fa)
{
	printf("%d ", u);
	for (auto &x: to[u]) {
		if (x != fa) {
			dfs(x, u);
			printf("%d ", u);
		}
	}
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) sort(to[i].begin(), to[i].end());
	dfs(1, 0);
	return 0;
}
