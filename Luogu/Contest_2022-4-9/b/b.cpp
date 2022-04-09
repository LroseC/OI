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

int n, m;
int a[N], b[N];

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> a[i] >> b[i];
	for (int i = 1; i < n; ++i) {
		int u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	i64 l = 1e-12, r = 1e12;
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid))
	}
	return 0;
}
