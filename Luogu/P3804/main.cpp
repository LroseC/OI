#include <vector>
#include <cstdio>

using namespace std;

using LL = long long;

const int N = 1e6 + 10;

LL ans;
LL cnt[N << 1];
char str[N];
vector<int> G[N << 1];

namespace SAM
{
	int idx = 1, last = 1;
	struct Node
	{
		int ch[26];
		int len, link;
	} node[N << 1];

	void extend(int id)
	{
		int ch = str[id] - 'a';
		int p = last;
		int cur = last = ++idx;
		node[cur].len = node[p].len + 1;
		while (p && !node[p].ch[ch]) {
			node[p].ch[ch] = cur;
			p = node[p].link;
		}
		if (!p) node[cur].link = 1;
		else {
			int to = node[p].ch[ch];
			if (node[to].len == node[p].len + 1)
				node[cur].link = to;
			else {
				int clone = ++idx;
				node[clone] = node[to];
				node[clone].len = node[p].len + 1;
				node[to].link = node[cur].link = clone;
				while (p && node[p].ch[ch] == to) {
					node[p].ch[ch] = clone;
					p = node[p].link;
				}
			}
		}
		cnt[cur] = 1;
	}
	void init_tree(void)
	{
		for (int i = 2; i <= idx; ++i)
			G[node[i].link].emplace_back(i);
	}
}

void dfs(int u)
{
	for (int v : G[u]) {
		dfs(v);
		cnt[u] += cnt[v];
	}
	if (cnt[u] > 1)
		ans = max(ans, 1ll * SAM::node[u].len * cnt[u]);
}

int main(void)
{
	scanf("%s", str + 1);
	for (int i = 1; str[i]; ++i)
		SAM::extend(i);
	SAM::init_tree();
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}
