#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

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

using LL = long long;
const int N = 1e5 + 10;

int n, m;
int w[N];
vector<int> G[N];

namespace SAM
{
	int idx = 1;
	struct Node
	{
		int len, link, ch[11];
	} node[(int)2e6 + 10];

	int extend(int ch, int last)
	{
		int np = ++idx, p = last;
		node[np].len = node[p].len + 1;
		while (p && !node[p].ch[ch]) {
			node[p].ch[ch] = np;
			p = node[p].link;
		}
		if (p == 0) node[np].link = 1;
		else {
			int to = node[p].ch[ch];
			if (node[to].len == node[p].len + 1)
				node[np].link = to;
			else {
				int clone = ++idx;
				node[clone] = node[to];
				node[clone].len = node[p].len + 1;
				node[np].link = clone;
				node[to].link = clone;
				while (node[p].ch[ch] == to) {
					node[p].ch[ch] = clone;
					p = node[p].link;
				}
			}
		}
		return np;
	}
	LL calc(void)
	{
		LL res = 0;
		for (int i = 2; i <= idx; ++i)
			res += node[i].len - node[node[i].link].len;
		return res;
	}
}

void dfs(int u, int fa, int last)
{
	last = SAM::extend(w[u], last);
	for (int v : G[u])
		if (v != fa) dfs(v, u, last);
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> w[i];
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		if (G[i].size() == 1) dfs(i, i, 1);
	printf("%lld\n", SAM::calc());
	return 0;
}
