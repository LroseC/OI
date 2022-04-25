#include <vector>
#include <cctype>
#include <cstdio>
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
using PII = std::pair<int, int>;
const int N = 1e6 + 10, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int n, L, K;
int f[N];
std::vector<int> G[N];

PII dfs(int u, int fa, int st)
{
	PII res = std::make_pair(0, 0);
	bool flag = 0;
	for (int v : G[u])
		if (v != fa && (st >> (v - 1) & 1)) {
			flag = 1;
			auto t = dfs(v, u, st);
			res.first += t.first;
			res.second = std::max(res.second, t.second);
		}
	++res.first;
	res.second += flag;
	return res;
}
bool check(int st)
{
	int cnt = __builtin_popcount(st);
	for (int i = 0; i < n; ++i)
		if (st >> i & 1) {
			auto t = dfs(i + 1, 0, st);
			if (t.first == cnt && t.second <= K)
				return 1;
		}
	return 0;
}
void getCnt(int u, int fa)
{
	f[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			getCnt(v, u);
			f[u] = 1ll * f[u] * Mod(f[v] + 1) % mod;
		}
}

int main(void)
{
	freopen("hope.in", "r", stdin);
	freopen("hope.out", "w", stdout);
	read >> n >> L >> K;
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	if (n <= 16 && K == 1) {
		int res = 0;
		for (int st = 1; st < 1 << n; ++st)
			if (check(st)) ++res;
		printf("%d\n", res);
		return 0;
	}
	if (L == n && K == 1) {
		getCnt(1, 0);
		int res = 0;
		for (int i = 1; i <= n; ++i)
			res = Mod(res + f[i]);
		printf("%d\n", res);
		return 0;
	}
	return 0;
}
