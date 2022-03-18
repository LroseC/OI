#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

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

const int N = 1e5 + 10;
using i64 = long long;

int n;
int cnt[N];
std::vector<int> G[N];

i64 C(int x)
{
	if (x < 3) return 0;
	return 1ll * x * (x - 1) * (x - 2) / 6;
}
void dfs(int u, int fa, int dep)
{
	++cnt[dep];
	for (int v : G[u])
		if (v != fa) dfs(v, u, dep + 1);
}

int main(void)
{
	read >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	i64 res = 0;
	for (int i = 1; i <= n; ++i) {
		dfs(i, 0, 1);
		i64 tres = res;
		for (int j = 1; j <= n; ++j) {
			if (!cnt[j]) break;
			res += C(cnt[j]);
		}
		printf("%d: %lld\n", i, res - tres);
		for (int j = 1; j <= n; ++j) {
			if (!cnt[j]) break;
		std::memset(cnt, 0, sizeof cnt);
	}
	printf("%lld\n", res);
	return 0;
}
