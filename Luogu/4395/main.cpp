#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 1e4 + 10;

int n;
vector<int> G[N];
int f[N][1010];

void dfs(int u, int fa)
{
	f[u][0] = 1, f[u][1] = 2;
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
	}
}

int main(void)
{
	n = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1, -1);
	printf("%d\n", min(f[1][0], f[1][1]));
	return 0;
}