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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 5e6 + 10;

struct Edge
{
	int v, ch;

	Edge(int _v, int _ch)
	{
		v = _v, ch = _ch;
	}
};

struct Node
{
	int link, len, cnt, ch[3];
	i64 res;
} node[N];

int n;
int idx = 1;
std::vector<Edge> G[N];
char str[(int)8e6 + 10];

int insert(int last, int son)
{
	int u = ++idx;
	if (node[last].ch[son]) {
		int q = node[last].ch[son];
		if (node[q].len == node[last].len + 1)
			++node[q].cnt;
		else {
			node[u] = node[q];
			node[u].len = node[last].len + 1;
			node[q].link = u;
			node[u].cnt = 1;
			for (int p = last; p && node[p].ch[son] == q; p = node[p].link)
				node[p].ch[son] = u;
		}
		return u;
	}
	node[last].ch[son] = u;
	node[u].len = node[last].len + 1;
	node[u].cnt = 1;
	for (last = node[last].link; last && !node[last].ch[son]; last = node[last].link)
		node[last].ch[son] = u;
	if (!last) node[u].link = 1;
	else {
		int q = node[last].ch[son];
		if (node[q].len == node[last].len + 1)
			node[u].link = q;
		else {
			int clone = ++idx;
			node[clone] = node[q];
			node[clone].len = node[last].len + 1;
			node[clone].cnt = 1;
			node[q].link = clone;
			node[u].link = clone;
			for (int p = last; p && node[p].ch[son] == q; p = node[p].link)
				node[p].ch[son] = clone;
		}
	}
	++node[node[u].link].cnt;
	return u;
}
std::vector<int> G2[N];
void calc1(int u, int fa)
{
	for (int v : G2[u])
		if (v != fa) {
			calc1(v, u);
			node[u].cnt += node[v].cnt;
		}
}
void calc2(int u, int fa)
{
	if (u != 1) {
		node[u].res += 1ll * node[u].cnt * (node[u].len - node[node[u].link].len);
	}
	for (int v : G2[u])
		if (v != fa) {
			if (u != 1)
				node[v].res += node[u].res;
			calc2(v, u);
		}
}
void build(void)
{
	for (int i = 2; i <= idx; ++i)
		G2[node[i].link].emplace_back(i);
	calc1(1, 1);
	calc2(1, 1);
}

void dfs(int u, int fa, int pos, int ch)
{
	if (u != 1)
		pos = insert(pos, ch);
	for (auto t : G[u])
		if (t.v != fa) dfs(t.v, u, pos, t.ch);
}

int main(void)
{
	read >> n;
	for (int i = 2; i <= n; ++i) {
		char ch;
		int fa; read >> fa;
		do ch = getchar();
		while (isspace(ch));
		G[fa].emplace_back(i, ch - 'a');
	}
	dfs(1, 1, 1, 0);
	build();
	scanf("%s", str + 1);
	int pos = 1;
	i64 res = 0;
	for (int i = 1; str[i]; ++i) {
		str[i] -= 'a';
		while (!node[pos].ch[str[i]] && node[pos].link) {
			pos = node[pos].link;
		}
		if (node[pos].ch[str[i]]) {
			pos = node[pos].ch[str[i]];
			res += node[pos].res;
		}
	}
	printf("%lld\n", res);
	return 0;
}
