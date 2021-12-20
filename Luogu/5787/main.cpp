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

const int N = 2e5 + 10;
using PII = pair<int, int>;
using vecpii = vector<PII>;

int n, m, K;
int fa[N << 1], sz[N << 1];
vecpii tr[N << 2];
PII stk[N]; int top;

int find(int x)
{
	while (x != fa[x]) x = fa[x];
	return x;
}
void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (sz[x] > sz[y]) swap(x, y);
	fa[x] = y;
	sz[y] += sz[x];
	stk[++top] = PII({x, y});
}
void undo(void)
{
	auto t = stk[top];
	int x = t.first, y = t.second;
	fa[x] = x;
	sz[y] -= sz[x];
	--top;
}
void add(int L, int R, int U, int V, int u = 1, int l = 1, int r = K)
{
	if (L <= l && r <= R) {
		tr[u].emplace_back(U, V);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, U, V, u << 1, l, mid);
	if (R > mid) add(L, R, U, V, u << 1 | 1, mid + 1, r);
}
void dfs(int u = 1, int l = 1, int r = K)
{
	int bk = top;
	bool sec = 1;
	for (auto t : tr[u]) {
		int x = t.first, y = t.second;
		if (find(x) == find(y)) {
			sec = 0;
			for (int i = l; i <= r; ++i) puts("No");
			break;
		}
		merge(x + N, y);
		merge(x, y + N);
	}
	if (sec) {
		if (l == r) puts("Yes");
		else {
			int mid = l + r >> 1;
			dfs(u << 1, l, mid);
			dfs(u << 1 | 1, mid + 1, r);
		}
	}
	while (top != bk) undo();
}

signed main(void)
{
	IO >> n >> m >> K;
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		fa[i + N] = i + N;
		sz[i] = sz[i + N] = 1;
	}
	for (int i = 1; i <= m; ++i) {
		int x, y, l, r;
		IO >> x >> y >> l >> r;
		if (l != r) add(l + 1, r, x, y);
	}
	dfs();
	return 0;
}
