#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 2e5 + 10;
const long long MOD = 998244353;
int n;
long long k;
struct bian
{
	int from, to, w;
}eg[N << 1];
int front[N], num;
void add(int x, int y, int w)
{
	eg[++ num].to = y;
	eg[num].from = front[x];
	front[x] = num;
	eg[num].w = w;
}
long long ksm(long long x, long long y)
{
	long long m = 1;
	for (; y; y >>= 1)
	{
		if(y & 1)
		m = m * x % MOD;
		x = x * x % MOD;
	}
	return m;
}
int siz[N], dep[N], son[N], fa[N], top[N], ids[N], val[N], val_k[N], dy[N];
int fa_val[N];
void dfs1(int o, int from)
{
	siz[o] = 1;
	dep[o] = dep[from] + 1;
	fa[o] = from;
	for (int i = front[o]; i; i = eg[i].from)
	{
		int to = eg[i].to;
		if(to == from)continue;
		dfs1(to, o);
		siz[o] += siz[to];
		val[o] += val[to] + eg[i].w;
		if(siz[to] > siz[son[o]])son[o] = to;
	}
	val_k[o] = ksm(val[o] - val[son[o]] - fa_val[son[o]], k);
}
void dfs2(int o, int tp)
{
	ids[o] = ++ num;
	dy[num] = o;
	top[o] = tp;
	if(son[o])dfs2(son[o], tp);
	for (int i = front[o]; i; i = eg[i].from)
	{
		int to = eg[i].to;
		if(to == fa[o] || to == son[o])continue;
		dfs2(to, to);
	}
}
long long tree[N << 2], sum_val[N << 2], add_tag[N << 2], tag[N << 2];
void build(int o, int l, int r)
{
	if(l == r)
	{
		tree[o] = val_k[dy[l]];
		sum_val[o] = fa_val[dy[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	tree[o] = (tree[o << 1] + tree[o << 1 | 1]) % MOD;
	sum_val[o] = sum_val[o << 1] + sum_val[o << 1 | 1];
}
void pushdown(int o, int l, int r, int mid)
{
	if(tag[o])
	{
		add_tag[o << 1] = add_tag[o << 1 | 1] = 0;
		tag[o << 1] = tag[o << 1 | 1] = tag[o];
		sum_val[o << 1] = tag[o] * (mid - l + 1);
		sum_val[o << 1 | 1] = tag[o] * (r - mid);
		tag[o] = 0;
	}
	if(add_tag[o])
	{
		add_tag[o << 1] += add_tag[o];
		add_tag[o << 1 | 1] += add_tag[o];
		sum_val[o << 1] += add_tag[o] * (mid - l + 1);
		sum_val[o << 1 | 1] += add_tag[o] * (r - mid);
		add_tag[o] = 0;
	}
}
long long opt1(int o, int l, int r, int L, int R)
{
	if(L > R)return 0;
	if(l >= L && r <= R)
	{
		return tree[o];
	}
	int mid = (l + r) >> 1;
	long long ans = 0;
	if(mid >= L) ans += opt1(o << 1, l, mid, L, R);
	if(mid < R) ans += opt1(o << 1 | 1, mid + 1, r, L, R);
	return ans % MOD;
}
long long opt2(int o, int l, int r, int L, int R)
{
	if(L > R)return 0;
	if(l >= L && r <= R)
	{
		return sum_val[o];
	}
	int mid = (l + r) >> 1;
	pushdown(o, l, r, mid);
	long long ans = 0;
	if(mid >= L) ans += opt2(o << 1, l, mid, L, R);
	if(mid < R) ans += opt2(o << 1 | 1, mid + 1, r, L, R);
	return ans;
}
void opt3(int o, int l, int r, int L, int R, int w)
{
	if(L > R)return;
	if(l >= L && r <= R)
	{
		sum_val[o] += w * (r - l + 1);
		add_tag[o] += w;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(o, l, r, mid);
	if(mid >= L) opt3(o << 1, l, mid, L, R, w);
	if(mid < R) opt3(o << 1 | 1, mid + 1, r, L, R, w);
	sum_val[o] = sum_val[o << 1] + sum_val[o << 1 | 1];
}
void opt4(int o, int l, int r, int L, int R, int w)
{
	if(L > R)return;
	if(l >= L && r <= R)
	{
		sum_val[o] = w * (r - l + 1);
		add_tag[o] = 0;
		tag[o] = w;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(o, l, r, mid);
	if(mid >= L) opt4(o << 1, l, mid, L, R, w);
	if(mid < R) opt4(o << 1 | 1, mid + 1, r, L, R, w);
	sum_val[o] = sum_val[o << 1] + sum_val[o << 1 | 1];
}
void opt5(int o, int l, int r, int i, int w)
{
	if(i == 0)return;
	if(l == r)
	{
		tree[o] = w;
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= i) opt5(o << 1, l, mid, i, w);
	else opt5(o << 1 | 1, mid + 1, r, i, w);
	tree[o] = (tree[o << 1] + tree[o << 1 | 1]) % MOD;
}
int LCA(int x, int y)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]])swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] < dep[y])
	swap(x, y);
	return y;
}
long long tree_val(int o)
{
	if(o == 0)return 0;
	return opt2(1, 1, n, ids[o] + 1, ids[o] + siz[o] - 1);
}
long long o_val(int o)
{
	if(o == 0)return 0;
	return opt2(1, 1, n, ids[o], ids[o]);
}
long long que_list(int x, int y)
{
	long long ans = 0, xx = x, yy = y;
	int lca = LCA(x, y);
	long long zong = tree_val(1) - tree_val(son[lca]) - o_val(son[lca]);
	if(x != lca)
	ans += ksm(tree_val(x), k);
	if(y != lca)
	ans += ksm(tree_val(y), k);
	ans %= MOD;
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]])swap(x, y);
		(ans += opt1(1, 1, n, ids[top[x]], ids[x] - 1)) %= MOD;
		x = top[x];
		if(fa[x] != lca)
		(ans += ksm(tree_val(fa[x]) - o_val(x) - tree_val(x), k))  %= MOD;
		else
		{
			zong -= tree_val(x) + o_val(x);
		}
		x = fa[x];
	}
	if(dep[x] < dep[y])
	swap(x, y);
	if(x != y)
	(ans += opt1(1, 1, n, ids[y] + 1, ids[x] - 1)) %= MOD;
	else
	zong += tree_val(son[lca]) + o_val(son[lca]);
	(ans += ksm(zong, k)) %= MOD;
	return (ans + MOD) % MOD;
}
void add_list(int x, int y, int w)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]])swap(x, y);
		opt3(1, 1, n, ids[top[x]], ids[x], w);
		x = top[x];
		opt5(1, 1, n, ids[fa[x]], ksm(tree_val(fa[x]) - tree_val(son[fa[x]]) - o_val(son[fa[x]]), k));
		x = fa[x];
	}
	if(dep[x] < dep[y])swap(x, y);
	opt3(1, 1, n, ids[y] + 1, ids[x], w);
	x = y;
	while(x)
	{
		x = top[x];
		opt5(1, 1, n, ids[fa[x]], ksm(tree_val(fa[x]) - tree_val(son[fa[x]]) - o_val(son[fa[x]]), k));
		x = fa[x];
	}
}
void re_list(int x, int y, int w)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]])swap(x, y);
		opt4(1, 1, n, ids[top[x]], ids[x], w);
		x = top[x];
		opt5(1, 1, n, ids[fa[x]], ksm(tree_val(fa[x]) - tree_val(son[fa[x]]) - o_val(son[fa[x]]), k));
		x = fa[x];
	}
	if(dep[x] < dep[y])swap(x, y);
	opt4(1, 1, n, ids[y] + 1, ids[x], w);
	x = y;
	while(x)
	{
		x = top[x];
		opt5(1, 1, n, ids[fa[x]], ksm(tree_val(fa[x]) - tree_val(son[fa[x]]) - o_val(son[fa[x]]), k));
		x = fa[x];
	}
}
int main()
{
	int q;
	scanf("%d%d%lld", &n, &q, &k);
	for (int i = 2; i <= n; ++ i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		fa_val[i] = y;
		add(x, i, y);
	}
	num = 0;
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	long long a = 0;
	int x = 0, y = 0;
	for (int i = 1; i <= q; ++ i)
	{
		int op, x, y, w;
		scanf("%d%d%d", &op, &x, &y);
		if(op <= 2)
		scanf("%d", &w);
		if(op == 1)
		add_list(x, y, w);
		if(op == 2)
		re_list(x, y, w);
		if(op == 3)
		printf("%lld\n", que_list(x, y));
	}
}
