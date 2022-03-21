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

const int N = 1e5 + 10, LG = 20;

int n, m, root, idx;
int L[N], R[N], revL[N], val[N];
int dep[N], fa[N][LG];
std::vector<int> G[N];
int tr[N << 2];

void getFa(int u)
{
	L[u] = ++idx;
	revL[idx] = u;
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : G[u])
		if (v != fa[u][0]) {
			fa[v][0] = u;
			getFa(v);
		}
	R[u] = idx;
}
void maintain(int u) { tr[u] = std::min(tr[u << 1], tr[u << 1 | 1]); }
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u] = val[revL[l]];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void change(int pos, int val, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u] = val;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
		change(pos, val, u << 1, l, mid);
	else
		change(pos, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L > R)
		return 0x3f3f3f3f;
	if (L <= l && r <= R)
		return tr[u];
	int res = 0x3f3f3f3f;
	int mid = l + r >> 1;
	if (L <= mid)
		res = std::min(res, query(L, R, u << 1, l, mid));
	if (R > mid)
		res = std::min(res, query(L, R, u << 1 | 1, mid + 1, r));
	return res;
}
int LCA(int u, int v)
{
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = LG - 1; i >= 0; --i)
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
int getSon(int u)
{
	int v = root;
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[v][i]] > dep[u]) v = fa[v][i];
	return v;
}
int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		read >> fa[i][0] >> val[i];
		G[fa[i][0]].emplace_back(i);
	}
	getFa(root = 1);
	build();
	for (int i = 1; i <= m; ++i) {
		char op[5];
		scanf("%s", op);
		if (op[0] == 'V') {
			int pos, v;
			read >> pos >> v;
			change(L[pos], v);
		}
		else if (op[0] == 'E') {
			read >> root;
		}
		else {
			int u; read >> u;
			if (u == root) {
				printf("%d\n", query(1, n));
			}
			else if (LCA(root, u) == u) {
				int t = getSon(u);
				printf("%d\n", std::min(query(1, L[t] - 1), query(R[t] + 1, n)));
			}
			else {
				printf("%d\n", query(L[u], R[u]));
			}
		}
	}
	return 0;
}
