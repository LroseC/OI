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

void solve(int _id)
{
	std::vector<int> &vc = point[_id];
	for (auto u : vc)
		for (int v : oG[u])
	for (int k = 1; k <= K; ++k)
		if (k != _id)
			for (auto 
}

int main(void)
{
	read >> n >> m >> K;
	for (int i = 1; i <= n; ++i) {
		read >> id[i];
		point[id[i]].emplace_back(i);
	}
	for (int i = 1, u, v; i <= m; ++i) {
		read >> u >> v;
		oG[u].emplace_back(v);
		oG[v].emplace_back(u);
	}
	for (int i = 1; i <= K; ++i)
		solve(i);
	for (int i = 1; i <= 2 * k + 1; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
