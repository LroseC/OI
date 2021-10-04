#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, mod = 998244353;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, cnt, mincost = 0x3f3f3f3f;
int a[N], b[N];
int f[N][N];
int Max[N][N];
bool vis[N][N];
int cost[N][N];
int fuck = 0;

void dfs(int dep, int cost)
{
	if (cost > mincost) return;
	if (dep > n) {
		if (cost < mincost) {
			puts("NOO");
			mincost = cost;
			cnt = 1;
		}
		else ++cnt;
		return;
	}
	for (int i = 1; i <= n; ++i)
		if (b[i]) {
			b[i] = 0;
			int l = i - 1, r = i + 1;
			while (b[l]) --l;
			while (b[r]) ++r;
			dfs(dep + 1, cost + Max[l + 1][i - 1] + Max[i + 1][r - 1]);
			b[i] = a[i];
		}
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) b[i] = a[i];
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j)
			Max[i][j] = max(Max[i][j - 1], a[j]);
	memset(cost, 0x3f, sizeof cost);
	dfs(1, 0);
	printf("%d\n", cnt);
	return 0;
}
