#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n;
char str[N];
int now[N], ans[N];
struct Node
{
	int len, fa;
	int ch[26];
} node[N];
int tot = 1, last = 1;
int idx, head[N], nex[N], to[N];

void extend(int c)
{
	int p = last, np = last = ++tot;
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
			node[np].fa = node[q].fa = nq;
			for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
		}
	}
}

void Add_Edge(int u, int v)
{
	nex[++idx] = head[u];
	head[u] = idx; to[idx] = v;
}
void dfs(int u)
{
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		dfs(v);
		now[u] = max(now[u], now[v]);
	}
}

int main(void)
{
	scanf("%d", &n);
	scanf("%s", str + 1);
	for (int i = 1; str[i]; ++i) extend(str[i] - 'a');
	for (int i = 2; i <= tot; ++i) Add_Edge(node[i].fa, i);

	for (int i = 1; i <= tot; ++i) ans[i] = node[i].len;
	for (int i = 1; i < n; ++i) {
		scanf("%s", str + 1);
		memset(now, 0, sizeof now);
		int p = 1, t = 0;
		for (int j = 1; str[j]; ++j) {
			int c = str[j] - 'a';
			while (p > 1 && !node[p].ch[c]) p = node[p].fa, t = node[p].len;
			if (node[p].ch[c]) p = node[p].ch[c], ++t;
			now[p] = max(now[p], t);
		}
		dfs(1);
		for (int j = 1; j <= tot; ++j) ans[j] = min(ans[j], now[j]);
	}

	int res = 0;
	for (int i = 1; i <= tot; ++i) res = max(res, ans[i]);
	printf("%d\n", res);

	return 0;
}