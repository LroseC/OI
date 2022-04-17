#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>

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
const int N = 1510, M = N * N, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int n;
int fa[N << 1], sz[N << 1], cnt[N << 1];
int idcnt, L[N << 1], R[N << 1];
bool isGood[N << 1];
std::pair<int, int> e[M];
std::vector<int> G[N << 1], left[N];
int f[N][N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void getId(int u)
{
	L[u] = INT_MAX;
	R[u] = INT_MIN;
	if (!G[u].size())
		L[u] = R[u] = ++idcnt;
	for (int v : G[u]) {
		getId(v);
		L[u] = std::min(L[u], L[v]);
		R[u] = std::max(R[u], R[v]);
	}
	if (isGood[u]) {
		left[R[u]].emplace_back(L[u]);
	}
}

int main(void)
{
	read >> n;
	int maxv = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int v; read >> v;
			maxv = std::max(v, maxv);
			e[v] = std::make_pair(i, j);
		}
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		sz[i] = 1;
		cnt[i] = 0;
		isGood[i] = 1;
	}
	int idx = n;
	for (int i = 1; i <= maxv; ++i) {
		auto t = e[i];
		int u = find(t.first);
		int v = find(t.second);
		if (u != v) {
			int id = ++idx;
			fa[id] = id;
			G[id].emplace_back(u);
			G[id].emplace_back(v);
			fa[u] = fa[v] = id;
			sz[id] = sz[u] + sz[v];
			cnt[id] = cnt[v] + cnt[u] + 1;
			auto check = [](int sz, int cnt) { return cnt == sz * (sz - 1) / 2; };
			isGood[id] |= check(sz[id], cnt[id]);
		}
		else {
			int id = u;
			++cnt[id];
			auto check = [](int sz, int cnt) { return cnt == sz * (sz - 1) / 2; };
			isGood[id] |= check(sz[id], cnt[id]);
		}
	}
	getId(idx);
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int v : left[i])
			for (int j = 1; j <= n; ++j)
				f[i][j] = Mod(f[i][j] + f[v - 1][j - 1]);
	for (int i = 1; i <= n; ++i)
		printf("%d ", f[n][i]);
	puts("");
	return 0;
}
