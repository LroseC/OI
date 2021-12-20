#include <map>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdlib>

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
} IO;

const int N = 1e5 + 10;
using pii = pair<int, int>;

int n, q;
int fa[N << 1], sz[N << 1];
map<pii, int> M;
vector<pii> tr[N << 2];
pii stk[N]; int top;

int find(int x)
{
	while (x != fa[x]) x = fa[x];
	return x;
}
void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] > sz[y]) swap(x, y);
	fa[x] = y;
	sz[y] += sz[x];
	stk[++top] = make_pair(x, y);
}
void undo(void)
{
	auto t = stk[top]; --top;
	fa[t.first] = t.first;
	sz[t.second] -= sz[t.first];
}

void add(int L, int R, int x, int y, int u = 1, int l = 1, int r = q)
{
	if (L <= l && r <= R) {
		tr[u].emplace_back(x, y);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, x, y, u << 1, l, mid);
	if (R > mid) add(L, R, x, y, u << 1 | 1, mid + 1, r);
}
void dfs(int u = 1, int l = 1, int r = q)
{
	bool sec = 1;
	int bk = top;
	for (auto t : tr[u]) {
		int x = t.first, y = t.second;
		if (find(x) == find(y)) {
			sec = 0;
			for (int i = l; i <= r; ++i) puts("NO");
			break;
		}
		merge(x, y + N), merge(x + N, y);
	}
	if (sec) {
		if (l == r) puts("YES");
		else {
			int mid = l + r >> 1;
			dfs(u << 1, l, mid);
			dfs(u << 1 | 1, mid + 1, r);
		}
	}
	while (top != bk) undo();
}

int main(void)
{
	IO >> n >> q;
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		fa[i + N] = i + N;
		sz[i] = sz[i + N] = 1;
	}
	for (int i = 1; i <= q; ++i) {
		int x, y; IO >> x >> y;
		if (M.count(make_pair(x, y))) {
			add(M[make_pair(x, y)], i - 1, x, y);
			M.erase(make_pair(x, y));
		}
		else M[make_pair(x, y)] = i;
	}
	for (auto t : M) {
		add(t.second, q, t.first.first, t.first.second);
	}
	dfs();
	return 0;
}
