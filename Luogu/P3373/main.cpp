#include <cctype>
#include <cstdio>

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
const int N = 1e5 + 10;

struct segNode
{
	int sum;
	int tagAdd, tagMul;
};

int n, m, mod;
int a[N];
segNode tr[N << 2];

inline int Mod(int x) { return x >= mod ? x - mod : x; }
void nodeAdd(int u, int val, int l, int r)
{
	tr[u].tagAdd = Mod(tr[u].tagAdd + val);
	tr[u].sum = Mod(tr[u].sum + 1ll * val * (r - l + 1) % mod);
}
void nodeMul(int u, int val, int l, int r)
{
	tr[u].sum = 1ll * tr[u].sum * val % mod;
	tr[u].tagAdd = 1ll * tr[u].tagAdd * val % mod;
	tr[u].tagMul = 1ll * tr[u].tagMul * val % mod;
}
void spread(int u, int l, int r)
{
	if (tr[u].tagMul != 1) {
		int mid = l + r >> 1;
		int val = tr[u].tagMul;
		nodeMul(u << 1, val, l, mid);
		nodeMul(u << 1 | 1, val, mid + 1, r);
		tr[u].tagMul = 1;
	}
	if (tr[u].tagAdd) {
		int mid = l + r >> 1;
		int val = tr[u].tagAdd;
		tr[u].tagAdd = 0;
		nodeAdd(u << 1, val, l, mid);
		nodeAdd(u << 1 | 1, val, mid + 1, r);
	}
}
void maintain(int u)
{
	tr[u].sum = Mod(tr[u << 1].sum + tr[u << 1 | 1].sum);
}
void build(int u = 1, int l = 1, int r = n)
{
	tr[u].tagAdd = 0;
	tr[u].tagMul = 1;
	if (l == r) {
		tr[u].tagAdd = 0;
		tr[u].tagMul = 1;
		tr[u].sum = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void segMul(int L, int R, int x, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		nodeMul(u, x, l, r);
		return;
	}
	int mid = l + r >> 1;
	spread(u, l, r);
	if (L <= mid)
		segMul(L, R, x, u << 1, l, mid);
	if (R > mid)
		segMul(L, R, x, u << 1 | 1, mid + 1, r);
	maintain(u);
}
void segAdd(int L, int R, int x, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		nodeAdd(u, x, l, r);
		return;
	}
	int mid = l + r >> 1;
	spread(u, l, r);
	if (L <= mid)
		segAdd(L, R, x, u << 1, l, mid);
	if (R > mid)
		segAdd(L, R, x, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return tr[u].sum;
	int mid = l + r >> 1;
	spread(u, l, r);
	int res = 0;
	if (L <= mid)
		res = Mod(res + query(L, R, u << 1, l, mid));
	if (R > mid)
		res = Mod(res + query(L, R, u << 1 | 1, mid + 1, r));
	return res;
}

int main(void)
{
	read >> n >> m >> mod;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	build();
	while (m--) {
		int op, x, y, k;
		read >> op;
		if (op == 1) {
			read >> x >> y >> k;
			segMul(x, y, k);
		}
		else if (op == 2) {
			read >> x >> y >> k;
			segAdd(x, y, k);
		}
		else {
			read >> x >> y;
			printf("%d\n", query(x, y));
		}
	}
	return 0;
}
