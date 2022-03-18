#include <queue>
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
const int N = 1e5 + 10;

int n;
int cnt[N], fa[N];
std::queue<int> q[N];
std::vector<int> G[N];

inline i64 C3(i64 x)
{
	if (x < 3) return 0;
	return x * (x - 1) * (x - 2) / 6;
}
inline i64 C2(i64 x)
{
	if (x < 2) return 0;
	return x * (x - 1) / 2;
}

void dfs(int u, int fath)
{
	fa[u] = fath;
	for (int v : G[u])
		if (v != fath) dfs(v, u);
}
void bfs(std::queue<int> &q)
{
	int t = q.size();
	for (int i = 1; i <= t; ++i) {
		int u = q.front(); q.pop();
		for (int v : G[u])
			if (v != fa[u]) q.emplace(v);
	}
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
		bool flag = 1;
		dfs(i, 0);
		for (int j = 0; j < G[i].size(); ++j)
			q[j].emplace(G[i][j]);
		res += C3(G[i].size());
		while (flag) {
			flag = 0;
			int sum = 0;
			for (int j = 0; j < G[i].size(); ++j)
				if (q[j].size()) {
					flag = 1;
					bfs(q[j]);
				}
			for (int j = 0; j < G[i].size(); ++j)
				sum += q[j].size();
			res += C3(sum);
			for (int j = 0; j < G[i].size(); ++j) {
				res -= C3(q[j].size());
				res -= C2(q[j].size()) * (sum - q[j].size());
			}
		}
	}
	printf("%lld\n", res);
	return 0;
}
