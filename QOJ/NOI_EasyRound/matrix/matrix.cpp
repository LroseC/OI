#include "grader.h"
#include <vector>
#include <algorithm>

using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
const int N = 1e6 + 10;

i32 n, dfncnt, top, idx;
i32 dfn[N], low[N], instk[N], stk[N], sccid[N], size[N], self[N];
vi32 G[N];

void clear(int n)
{
	dfncnt = top = idx = 0;
	std::fill(dfn, dfn + n, 0);
	std::fill(low, low + n, 0);
	std::fill(size, size + n, 0);
	std::fill(self, self + n, 0);
	std::fill(instk, instk + n, 0);
	std::fill(sccid, sccid + n, 0);
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++dfncnt;
	stk[++top] = u;
	instk[u] = 1;
	for (int v : G[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (instk[u]) {
			low[u] = std::min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		int t = ++idx;
		int tmp = -1;
		while (tmp != u) {
			tmp = stk[top--];
			instk[tmp] = 0;
			sccid[tmp] = t;
			size[t] += 1;
		}
	}
}
bool solve1(const uint32_t& subId,const uint32_t& N,const vector<vector<bool>>& Matrix){
	n = N;
	clear(n);
	for (int i = 0; i < n; ++i)
		G[i].clear();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			if (Matrix[i][j]) G[i].emplace_back(j);
		}
	idx = 0;
	dfncnt = 0;
	std::fill(dfn, dfn + n, 0);
	std::fill(low, low + n, 0);
	for (int i = 0; i < n; ++i)
		if (!dfn[i]) tarjan(i);
	if (idx > 1) return false;
	return true;
}

bool solve2(const uint32_t& subId,const uint32_t& N,const vector<pair<uint32_t,uint32_t>>& Matrix){
	n = N;
	clear(n);
	for (int i = 0; i < n; ++i)
		G[i].clear();
	std::fill(self, self + n, 0);
	for (auto t : Matrix)
	{
		if (t.first == t.second) self[t.first] = 1;
		G[t.first].emplace_back(t.second);
	}
	idx = 0;
	std::fill(dfn, dfn + n, 0);
	std::fill(low, low + n, 0);
	for (int i = 0; i < n; ++i)
		if (!dfn[i]) tarjan(i);
	if (idx > 1) return false;
	return true;
}
