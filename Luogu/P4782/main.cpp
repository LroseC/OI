#include <vector>
#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 2e6 + 10;

int n, m;
std::vector<int> G[N];
int stk[N], top;
bool instk[N];
int dfn[N], low[N], dfnCnt;
int scc[N], sccCnt;

void add(int u, int v) { G[u].emplace_back(v); }
void tarjan(int u)
{
	dfn[u] = low[u] = ++dfnCnt;
	stk[++top] = u, instk[u] = 1;
	for (int v : G[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (instk[v])
			low[u] = std::min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++sccCnt;
		int tmp;
		do {
			tmp = stk[top--];
			scc[tmp] = sccCnt;
			instk[tmp] = 0;
		} while(tmp != u);
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int x, a, y, b;
		read >> x >> a >> y >> b;
		add(x << 1 | !a, y << 1 | b);
		add(y << 1 | !b, x << 1 | a);
	}
	for (int i = 2; i <= (n << 1 | 1); ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i)
		if (scc[i << 1] == scc[i << 1 | 1]) {
			puts("IMPOSSIBLE");
			return 0;
		}
	puts("POSSIBLE");
	for (int i = 1; i <= n; ++i) {
		if (scc[i << 1] > scc[i << 1 | 1])
			printf("1 ");
		else
			printf("0 ");
	}
	puts("");
	return 0;
}
