#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

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
inline int lowbit(int x) { return x & -x; }

int val[N];
bool del[N];
int sz[N];
vector<int> G[N];
vector<int> tr1[N], tr2[N];
int fa[N], _fa[N][20], dep[N];
int n, m;

void Getroot(int u, int fa, int &root, int &minsize, int allnode);
void build(int u);
void Initdep(int u, int fa, int depth);
int Getdis(int u, int v);
void insert(int pos);
void remove(int pos);
int query(int pos, int K);

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i) read >> val[i];
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	Initdep(1, 1, 1);
	fprintf(stderr, "Init end.\n");

	int root, minsize = INT_MAX;
	Getroot(1, 1, root, minsize, n);
	tr1[root].resize(n + 10);
	tr2[root].resize(n + 10);
	build(root);
	for (int i = 1; i <= n; ++i)
		insert(i);
	fprintf(stderr, "Init2 end.\n");

	int lastans = 0;
	for (int i = 1; i <= m; ++i) {
		int op; read >> op;
		fprintf(stderr, "Operation begin. op is %d.\n", op);
		if (op == 0) {
			int x, k; read >> x >> k;
			x ^= lastans, k ^= lastans;
			printf("%d\n", lastans = query(x, k));
			fprintf(stderr, "ans = %d\n", lastans);
		}
		else {
			int x, v; read >> x >> v;
			x ^= lastans, v ^= lastans;
			remove(x);
			val[x] = v;
			insert(x);
		}
		fprintf(stderr, "Operation end.\n");
	}
	return 0;
}
void _add(int x, int val, vector<int> &tr)
{
	++x;
	for (int i = x; i < tr.size(); i += lowbit(i))
		tr[i] += val;
}
int _query(int x, vector<int> &tr)
{
	++x;
	if (x <= 0) return 0;
	x = min(x, (int)tr.size() - 1);
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
void insert(int pos)
{
	int u = pos, v = val[pos];
	_add(0, v, tr1[pos]);
	while (fa[pos]) {
		int dis = Getdis(u, fa[pos]);
		_add(dis, v, tr2[pos]);
		pos = fa[pos];
		_add(dis, v, tr1[pos]);
	}
}
void remove(int pos)
{
	int u = pos, v = val[pos];
	_add(0, v, tr1[pos]);
	while (fa[pos]) {
		int dis = Getdis(u, fa[pos]);
		_add(dis, v, tr2[pos]);
		pos = fa[pos];
		_add(dis, v, tr1[pos]);
	}
}
int query(int pos, int K)
{
	int res = _query(K, tr1[pos]);
	while (fa[pos]) {
		fprintf(stderr, "pos = %d\n", pos);
		int tmp = Getdis(pos, fa[pos]);
		fprintf(stderr, "Getdis finished.\n");
		res -= _query(K - tmp, tr2[pos]);
		res += _query(K - tmp, tr1[fa[pos]]);
		fprintf(stderr, "mid.\n");
		K -= tmp;
		pos = fa[pos];
		fprintf(stderr, "end.\n");
	}
	return res;
}
void Getroot(int u, int fa, int &root, int &minsize, int allnode)
{
	int sonsize = 0;
	sz[u] = 1;
	for (int v : G[u])
		if (v != fa && !del[v]) {
			Getroot(v, u, root, minsize, allnode);
			sz[u] += sz[v];
			sonsize = max(sonsize, sz[v]);
		}
	sonsize = max(sonsize, allnode - sz[u]);
	if (sonsize < minsize) {
		root = u;
		minsize = sonsize;
	}
}
void build(int u)
{
	del[u] = 1;
	for (int v : G[u])
		if (!del[v]) {
			int root, minsize = INT_MAX;
			Getroot(v, u, root, minsize, sz[v]);
			fa[root] = u;
			tr1[root].resize(sz[v] + 10);
			tr2[root].resize(sz[v] + 10);
			build(root);
		}
}
void Initdep(int u, int fa, int depth)
{
	for (int k = 1; k < 20; ++k)
		_fa[u][k] = _fa[_fa[u][k - 1]][k - 1];
	dep[u] = depth;
	for (int v : G[u])
		if (v != fa) {
			_fa[v][0] = u;
			Initdep(v, u, depth + 1);
		}
}
int Getdis(int u, int v)
{
	int res = 0;
	if (dep[u] > dep[v]) swap(u, v);
	for (int k = 19; k >= 0; --k)
		if (dep[u] <= dep[_fa[v][k]]) {
			res += 1 << k;
			v = _fa[v][k];
		}
	if (u == v) return res;
	for (int k = 19; k >= 0; --k)
		if (_fa[u][k] != _fa[v][k]) {
			res += 1 << k + 1;
			u = _fa[u][k], v = _fa[v][k];
		}
	return res + 1;
}
