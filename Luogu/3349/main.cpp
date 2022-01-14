#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 20;
using LL = long long;
inline int lowbit(int x) { return x & -x; }

int n, m;
LL f[N][N], ans;
vector<int> G[N], OG[N], list;

int GetCnt(int x)
{
	int res = 0;
	while (x) {
		++res;
		x -= lowbit(x);
	}
	return res;
}

void dp(int u, int fa, int limit)
{
	for (int i = 1; i <= n; ++i) {
		if (limit >> i - 1 & 1 == 0) continue;
		f[u][i] = 1;
	}
	for (int v : G[u]) {
		if (v == fa) continue;
		dp(v, u, limit);
		for (int i = 1; i <= n; ++i) { //i -> u;
			if (limit >> i - 1 & 1 == 0)
				continue;
			LL sum = 0;
			for (int j : OG[i]) //j -> v;
				if (limit >> j - 1 & 1)
					sum += f[v][j];
			f[u][i] *= sum;
		}
	}
}

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		OG[u].emplace_back(v);
		OG[v].emplace_back(u);
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = (1 << n) - 1; i >= 0; --i) {
		memset(f, 0, sizeof f);
		dp(1, 0, i);
		LL res = 0;
		for (int j = 1; j <= n; ++j)
			if (i >> j - 1 & 1)
				res += f[1][j];
		res *= (n - GetCnt(i) & 1) ? -1 : 1;
		ans += res;
	}
	printf("%lld\n", ans);
	return 0;
}
/*
	f[u][id] 表示节点 u 编号为 id 的方案数.
	大力容斥, 最终答案 res = (|S| == n 的方案数) - (|S| == n - 1 的方案数) + (|S| == n - 2 的方案数) - ...
*/