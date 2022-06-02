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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 2e5 + 10;

int n, K, S, T, ans;
int key[N], isKey[N], dep[N];
std::vector<int> G[N];

void clear(void)
{
	ans = 0;
	for (int i = 1; i <= n; ++i)
		G[i].clear();
	std::memset(dep + 1, 0, 4 * n);
	std::memset(key + 1, 0, 4 * K);
	std::memset(isKey + 1, 0, 4 * n);
}

void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	for (int v : G[u])
		if (v != fa) {
			dfs(v, u);
			isKey[u] += isKey[v];
		}
}
void getAns(int u, int fa)
{
	for (int v : G[u])
		if (v != fa && isKey[v]) {
			ans += 2;
			getAns(v, u);
		}
}

void work(void)
{
	read >> n >> K;
	read >> S >> T;
	for (int i = 1; i <= K; ++i) {
		read >> key[i];
		isKey[key[i]] = 1;
	}
	if (!isKey[T]) {
		key[++K] = T;
		isKey[T] = 1;
	}
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(S, 0);
	getAns(S, 0);
	printf("%d\n", ans - dep[T] + 1);
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		work();
		clear();
	}
	return 0;
}
