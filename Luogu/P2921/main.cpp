#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n;
int nex[N];
int dis[N];
bool vis[N], del[N];

void dfs(int u)
{
	printf("u = %d\n", u);
	if(del[u]) {
		dis[u] = 1;
		printf("dis[%d] = %d\n", u, dis[u]);
		return;
	}
	del[u] = 1;
	dfs(nex[u]);
	dis[u] = dis[nex[u]] + 1;
	printf("dis[%d] = %d\n", u, dis[u]);
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) {
		nex[i] = read();
		vis[nex[i]] = 1;
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			dfs(i);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", dis[i]);
	return 0;
}