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

const int N = 1e6 + 10;

int n;
int val[N], fa[N];
std::vector<int> G[N];
void dfs(int u, int dis, int &res)
{
	res ^= (val[u] + dis);
	for (int v : G[u])
		if (v != fa[u]) {
			dfs(v, dis + 1, res);
		}
}

int main(void)
{
//	freopen("tree.in", "r", stdin);
//	freopen("tree.out", "w", stdout);
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> val[i];
	for (int i = 2; i <= n; ++i) {
		read >> fa[i];
		G[fa[i]].emplace_back(i);
	}
	i64 res = 0;
	for (int i = 1; i <= n; ++i) {
		int tmp = 0;
		dfs(i, 0, tmp);
		res += tmp;
	}
	printf("%lld\n", res);
	return 0;
}
