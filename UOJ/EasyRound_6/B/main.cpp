#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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
using PII = std::pair<int, int>;
const int N = 1e6;

int n, m, idx;
bool instk[N];
int stk[N], top;
int scc[N], sccCnt;
std::vector<int> G[N];
int low[N], dfn[N], dfncnt;
std::vector<PII> word[N];

void tarjan(int u)
{
	stk[++top] = u;
	instk[u] = 1;
	dfn[u] = low[u] = ++dfncnt;
	for (int v : G[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (instk[v])
			low[u] = std::min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int tmp;
		++sccCnt;
		do {
			tmp = stk[top--];
			scc[tmp] = sccCnt;
			instk[tmp] = 0;
		} while (tmp != u);
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int x, y, t;
		read >> x >> y >> t;
		word[x].emplace_back(std::make_pair(y, t));
	}
	idx = n << 1 | 1;
	for (int i = 1; i <= n; ++i) {
		int sz = word[i].size();
		std::vector<int> pre(sz), suf(sz);
		for (int j = 0; j < sz; ++j) {
			pre[j] = ++idx;
			suf[j] = ++idx;
		}
		for (int j = 0; j < sz; ++j) {
			G[pre[j]].emplace_back(word[i][j].first << 1 | word[i][j].second);
			G[suf[j]].emplace_back(word[i][j].first << 1 | word[i][j].second);
			if (j != 0)
				G[pre[j]].emplace_back(pre[j - 1]);
			if (j != sz - 1)
				G[suf[j]].emplace_back(suf[j + 1]);
		}

		for (int j = 0; j < sz; ++j) {
			int u = word[i][j].first << 1 | (!word[i][j].second);
			if (j != 0)
				G[u].emplace_back(pre[j - 1]);
			if (j != sz - 1)
				G[u].emplace_back(suf[j + 1]);
			G[u].emplace_back(i << 1);
		}
		if (suf.size())
			G[i << 1 | 1].emplace_back(suf[0]);
	}
	for (int i = 1; i <= (n << 1 | 1); ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i)
		if (scc[i << 1] == scc[i << 1 | 1]) {
			puts("Impossible");
			return 0;
		}
	int cnt = 0;
	std::vector<int> res;
	for (int i = 1; i <= n; ++i) {
		if (scc[i << 1] < scc[i << 1 | 1]) {
			++cnt;
			res.emplace_back(i);
		}
	}
	std::sort(res.begin(), res.end());
	printf("%d\n", cnt);
	for (int v : res)
		printf("%d ", v);
	puts("");
	return 0;
}
