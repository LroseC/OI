#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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
const int N = 2e5 + 10, S = N * 31 * 2;

int n, idx;
int a[N], fa[N], root[N];
int sz[S], ch[S][2], id[S];
PII minx[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void insert(int u, int val, int valId)
{
	for (int i = 30; i >= 0; --i) {
		int c = val >> i & 1;
		if (!ch[u][c]) ch[u][c] = ++idx;
		++sz[u];
		u = ch[u][c];
	}
	++sz[u], id[u] = valId;
}
void merge(int &u, int v)
{
	if (!u || !v) {
		u = u + v;
		return;
	}
	merge(ch[u][0], ch[v][0]);
	merge(ch[u][1], ch[v][1]);
	sz[u] += sz[v];
}
PII query(int u, int v, int val)
{
	int res = 0;
	for (int i = 30; i >= 0; --i) {
		int c = val >> i & 1;
		if (sz[ch[u][c]] - sz[ch[v][c]] > 0) {
			u = ch[u][c];
			v = ch[v][c];
		}
		else {
			c ^= 1;
			u = ch[u][c];
			v = ch[v][c];
			res |= 1 << i;
		}
	}
	return std::make_pair(res, id[u]);
}

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	std::sort(a + 1, a + 1 + n);
	root[0] = idx = n + 1;
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		sz[i] = 1;
		root[i] = i;
		insert(root[i], a[i], i);
		insert(root[0], a[i], i);
	}
	bool flag = 1;
	i64 res = 0;
	while (flag) {
		flag = 0;
		std::memset(minx, 0x3f, sizeof minx);
		for (int i = 1; i <= n; ++i) {
			int u = find(i);
			auto t = query(root[0], root[u], a[i]);
			if (t.first <= minx[u].first)
				minx[u] = t;
		}
		for (int u = 1; u <= n; ++u)
			if (fa[u] == u && minx[u].first != 0x3f3f3f3f) {
				flag = 1;
				int v = find(minx[u].second);
				if (u == v) continue;
				res += minx[u].first;
				fa[u] = v;
				merge(root[v], root[u]);
			}
	}
	printf("%lld\n", res);
	return 0;
}
