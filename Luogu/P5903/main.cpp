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
using ui = unsigned int;
const int N = 5e5 + 10, LG = 21;

int n, m, root;
ui Seed;
int lg2[N];
int fa[N][LG], son[N], top[N];
int dep[N], deepest[N];
std::vector<int> G[N], up[N], down[N];

inline ui get(ui x)
{
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return Seed = x;
}
void initSon(int u)
{
	dep[u] = deepest[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : G[u]) {
		initSon(v);
		if (deepest[v] > deepest[son[u]]) {
			son[u] = v;
			deepest[u] = deepest[v];
		}
	}
}
void initCut(int u, int _top)
{
	top[u] = _top;
	if (u == _top) {
		for (int i = 0, v = u; i <= deepest[u] - dep[u]; ++i) {
			up[u].emplace_back(v);
			v = fa[v][0];
		}
		for (int i = 0, v = u; i <= deepest[u] - dep[u]; ++i) {
			down[u].emplace_back(v);
			v = son[v];
		}
	}
	if (son[u]) initCut(son[u], _top);
	for (int v : G[u])
		if (v != son[u]) initCut(v, v);
}
int query(int u, int k)
{
	if (!k) return u;
	u = fa[u][lg2[k]];
	k ^= 1 << lg2[k];
	k -= dep[u] - dep[top[u]];
	u = top[u];
	return k >= 0 ? up[u][k] : down[u][-k];
}

int main(void)
{
	read >> n >> m >> Seed;

	lg2[1] = 0;
	for (int i = 2; i <= n; ++i)
		lg2[i] = lg2[i >> 1] + 1;

	for (int i = 1; i <= n; ++i) {
		read >> fa[i][0];
		if (fa[i][0]) G[fa[i][0]].emplace_back(i);
		else root = i;
	}
	initSon(root);
	initCut(root, root);

	i64 res = 0;
	for (int i = 1, lastans = 0; i <= m; ++i) {
		int x = (get(Seed) ^ lastans) % n + 1;
		int k = (get(Seed) ^ lastans) % dep[x];
		res ^= 1ll * i * (lastans = query(x, k));
	}
	printf("%lld\n", res);
	return 0;
}
