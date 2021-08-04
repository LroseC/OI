#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long
const int N = 2e6 + 10;

int n, m;
char str[N];
int last = 1, tot = 1;
struct Node
{
	int len, fa, ch[26];
} node[N];
int idx, head[N], nex[N], to[N];
ll ans, f[N];

void extend(int c)
{
	int p = last, np = last = ++tot;
	f[np] = 1;
	node[np].len = node[p].len + 1;
	for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
	if (!p) node[np].fa = 1;
	else {
		int q = node[p].ch[c];
		if (node[q].len == node[p].len + 1) node[np].fa = q;
		else {
			int nq = ++tot;
			node[nq] = node[q];
			node[nq].len = node[p].len + 1;
			node[q].fa = node[np].fa = nq;
			for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
		}
	}
}

void Add_Edge(int u, int v)
{
	nex[++idx] = head[u];
	head[u] = idx, to[idx] = v;
}

void dfs(int u)
{
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		dfs(v);
		f[u] += f[v];
	}
	if (f[u] > 1) ans = max(f[u] * node[u].len, ans);
}

int main(void)
{
	scanf("%s", str + 1);
	for (n = 1; str[n]; ++n) extend(str[n] - 'a');
	for (int i = 2; i <= tot; ++i) Add_Edge(node[i].fa, i);

	dfs(1);
	printf("%lld\n", ans);
	return 0;
}