#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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
const int mod = 1e9 + 7, N = 210;
inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline int getSum(int l, int r)
{
	return (1ll * (l + r) * (r - l + 1) / 2) % mod;
}

int n, K, maxR, res1, res2;
std::vector<int> G[N];
int l[N], r[N];
int f[(int)2e5 + 10][2];
int g[(int)2e5 + 10][2];

void dfs(int u, int fa)
{
}

int main(void)
{
	read >> n >> K;
	for (int i = 1; i <= n; ++i) {
		read >> l[i] >> r[i];
		maxR = std::max(maxR, r[i]);
	}
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i) {
		std::memset(f, 0, sizeof f);
		std::memset(g, 0, sizeof g);
		for (int j = l[i]; j <= r[i]; ++j) {
			f[j][1] = 1;
			g[j][1] = j;
			if (j != r[i]) {
				f[j][0] = (r[i] - j);
				g[j][0] = getSum(j + 1, r[i]);
			}
		}
		for (int j = 1; j < l[i]; ++j) {
			f[j][1] = 0;
			g[j][1] = 0;
			int left = std::max(j, l[i]);
			int right = std::min(j + K, r[i]);
			if (left <= right) {
				f[j][0] = right - left + 1;
				g[j][0] = getSum(left, right);
			}
		}
		dfs(i, 0);
		printf("%d %d\n", res1, res2);
	}
	printf("%d %d\n", res1, res2);
	return 0;
}
