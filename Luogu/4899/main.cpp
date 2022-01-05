#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 2e5 + 10, LOG = 20;

int n, m, q;
int root[N];
vector<int> G[N];

namespace UF
{
	int fa[N << 1];
	void init(int n)
	{
		for (int i = 1; i <= n; ++i) fa[i] = i;
	}
	int find(int x)
	{
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void merge(int a, int b)
	{
		a = find(a), b = find(b);
		fa[a] = b;
	}
};

namespace SGT
{
	struct node
	{
		int l, r;
		int sum;
	} tr[N << 5];
	int idx;

	int add(int pre, int key, int l = 0, int r = n)
	{
		int u = ++idx;
		tr[u] = tr[pre];
		if (l == r) {
			++tr[u].sum;
			return u;
		}
		int mid = l + r >> 1;
		if (key <= mid) tr[u].l = add(tr[u].l, key, l, mid);
		else tr[u].r = add(tr[u].r, key, mid + 1, r);
		tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum;
		return u;
	}
	int query(int u1, int u2, int L, int R, int l = 0, int r = n)
	{
		if (L <= l && r <= R) return tr[u2].sum - tr[u1].sum;
		int mid = l + r >> 1;
		int res = 0;
		if (L <= mid) res += query(tr[u1].l, tr[u2].l, L, R, l, mid);
		if (R > mid) res += query(tr[u1].r, tr[u2].r, L, R, mid + 1, r);
		return res;
	}
}

struct Kruskal
{
	int type;
	int nodecnt;
	int L[N], R[N], idx;
	int fa[N][LOG];
	int nums[N];
	vector<int> K[N];

	void dfs(int u)
	{
		for (int k = 1; k < LOG; ++k)
			fa[u][k] = fa[fa[u][k - 1]][k - 1];

		++idx;
		L[u] = R[u] = idx;
		nums[idx] = u;

		for (int v : K[u]) {
			fa[v][0] = u;
			dfs(v);
			L[u] = min(L[u], L[v]);
			R[u] = max(R[u], R[v]);
		}
	}
	void build(int op)
	{
		type = op;
		UF::init(n);
		memset(L, 0x3f, sizeof L);
		if (type == 1) {
			//root is max;
			for (int u = 1; u <= n; ++u)
				for (int v : G[u])
					if (v < u) {
						int fu = UF::find(u), fv = UF::find(v);
						if (fu == fv) continue;
						UF::merge(fv, fu);
						K[fu].emplace_back(fv);
					}
		}
		else {
			//root is min;
			for (int u = n; u >= 1; --u)
				for (int v : G[u])
					if (v > u) {
						int fu = UF::find(u), fv = UF::find(v);
						if (fu == fv) continue;
						UF::merge(fv, fu);
						K[fu].emplace_back(fv);
					}
		}
		dfs(type == 1 ? n : 1);
	}
	void print(int u)
	{
		printf("u = %d\n", u);
		for (int v : K[u]) print(v);
	}
	pair<int, int> query(int u, int lim)
	{
		if (type == 1) {
			for (int k = LOG - 1; k >= 0; --k)
				if (fa[u][k] && fa[u][k] <= lim) {
					u = fa[u][k];
				}
		}
		else {
			for (int k = LOG - 1; k >= 0; --k)
				if (fa[u][k] && fa[u][k] >= lim) {
					u = fa[u][k];
				}
		}
		puts("begin");
		printf("type = %d, lim = %d\n", type, lim);
		print(u);
		puts("end");
		return make_pair(L[u], R[u]);
	}
} TK_Human, TK_Monster;

void build_SGT(void)
{
	vector<int> pos(n + 1), TREE(n + 1);
	for (int i = 1; i <= n; ++i) pos[TK_Human.nums[i]] = i;
	for (int i = 1; i <= n; ++i) {
		TREE[i] = pos[TK_Monster.nums[i]];
		root[i] = SGT::add(root[i - 1], TREE[i]);
	}
	puts("");
	for (int i = 1; i <= n; ++i) printf("%d ", TK_Human.nums[i]);
	puts("");
	for (int i = 1; i <= n; ++i) printf("%d ", TK_Monster.nums[i]);
	puts("");
	puts("end");
}

bool query(int Human, int Monster, int LimHuman, int LimMoster)
{
	auto SeqHuman = TK_Human.query(Human, LimHuman);
	auto SeqMonster = TK_Monster.query(Monster, LimMoster);
	printf("SeqHuman = (%d, %d)\n", SeqHuman.first, SeqHuman.second);
	printf("SeqMonster = (%d, %d)\n", SeqMonster.first, SeqMonster.second);
	return (bool)SGT::query(root[SeqHuman.first - 1], root[SeqHuman.second], SeqMonster.first, SeqMonster.second);
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m >> q;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		++u, ++v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	TK_Human.build(0);
	TK_Monster.build(1);
	build_SGT();
	for (int i = 1; i <= q; ++i) {
		int S, T, L, R; cin >> S >>T >> L >> R;
		++S, ++T, ++L, ++R;
		printf("%d\n", (int)query(S, T, L, R));
	}
	return 0;
}
