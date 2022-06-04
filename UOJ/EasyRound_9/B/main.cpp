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
		for (auto v : Gp2b[u])
			invGp2b[v].emplace_back(u);
	std::memset(dis, 0x3f, sizeof dis);
	for (int k = 1; k <= K; ++k)
		if (k != _id)
			for (auto u : invGp2b[k])
				for (auto v : Gb2p[k])
}

void unique(std::vector<int> &t)
{
	std::sort(t.begin(), t.end());
	t.erase(std::unique(t.begin(), t.end()), t.end());
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
		Gp2p[u].emplace_back(v);
		Gp2p[v].emplace_back(u);
		Gp2b[u].emplace_back(id[v]);
		Gp2b[v].emplace_back(id[u]);
		Gb2p[id[u]].emplace_back(v);
		Gb2p[id[v]].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		unique(Gp2b[i]);
	for (int i = 1; i <= K; ++i)
		unique(Gb2p[i]);
	for (int i = 1; i <= K; ++i)
		solve(i);
	for (int i = 1; i <= 2 * k + 1; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
