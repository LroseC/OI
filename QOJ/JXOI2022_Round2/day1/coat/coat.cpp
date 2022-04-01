#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

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
const int N = 2010, mod = 64123;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int n, K, W;
int d[N];
std::vector<int> G[N];

int dfs(int u, int fa, int state)
{
	int res = 1;
	for (int v : G[u])
		if (v != fa && (state >> v & 1))
			res += dfs(v, u, state);
	return res;
}

int main(void)
{
//	freopen("coat.in", "r", stdin);
//	freopen("caot.out", "w", stdout);
	read >> n >> K >> W;
	for (int i = 0; i < n; ++i)
		read >> d[i];
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		--u, --v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	int ans = 0;
	for (int i = 0; i < 1 << n; ++i) {
		int cnt = __builtin_popcount(i);
		if (cnt < K) continue;
		bool flag = 0;
		for (int j = 0; j < n; ++j)
			if (i >> j & 1) {
				if (dfs(j, j, i) == cnt)
					flag = 1;
				break;
			}
		if (flag) {
			std::vector<int> tmp;
			for (int j = 0; j < n; ++j)
				if (i >> j & 1)
					tmp.emplace_back(d[j]);
			std::nth_element(tmp.begin(), tmp.begin() + K - 1, tmp.end(), std::greater<int>());
			ans = Mod(ans + tmp[K - 1]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
