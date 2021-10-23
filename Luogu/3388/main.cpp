#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

const int N = 2e4 + 10;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int anscnt;
vector<int> G[N];
int tim, dfn[N], low[N];
bool iscut[N];

void tarjan(int u, int fa)
{
	int child = 0;
	dfn[u] = low[u] = ++tim;
	for (int v : G[u]) {
		if (!dfn[v]) {
			++child;
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (dfn[u] != 1 && low[v] >= dfn[u] && !iscut[u]) {
				++anscnt;
				iscut[u] = 1;
			}
		}
		else if (v != fa) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == 1 && child >= 2 && !iscut[u]) {
		++anscnt;
		iscut[u] = 1;
	}
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) {
			tim = 0;
			tarjan(i, i);
		}
	printf("%d\n", anscnt);
	for (int i = 1; i <= n; ++i)
		if (iscut[i]) printf("%d ", i);
	return 0;
}