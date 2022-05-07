#include <cctype>
#include <cstdio>

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

int getCnt(void)
{
	int res = 0;
	std::memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++i) {
		int u = find(i);
		if (!vis[u]) {
			++res;
			vis[u] = 1;
		}
	}
}

int main(void)
{
	read >> n;
	idx = n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		fa[i] = i;
		insert(0, a[i]);
		insert(i, a[i]);
		val[i].emplace_back(i);
	}
	i64 res = 0;
	if (getCnt() != 1) {
		for (auto t : edge) {
			res += t.w;
			int u = find(t.u), v = find(t.v);
			if (sz[u] > sz[v])
				std::swap(u, v);
			sz[v] += sz[u];
			fa[u] = v;
			for (int x : val[u])
				insert(v, a[x]);
		}
	}
	return 0;
}
