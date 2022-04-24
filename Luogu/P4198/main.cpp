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

struct node
{
	int max, cnt;
};

int n, m;
int h[N];
node tr[N << 2];

bool myGreater(int x, int y)
{
	if (!y) return x;
	return 1ll * h[x] * y > 1ll * h[y] * x;
}
void build(int u = 1, int l = 1, int r = n)
{
	tr[u].max = l;
	if (l == r)
		return;
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
}
int calc(int u, int l, int r, int lim)
{
	if (l == r)
		return h[l] > 0 && myGreater(l, lim);
	int mid = l + r >> 1;
	if (myGreater(tr[u << 1].max, lim))
		return calc(u << 1, l, mid, lim) + tr[u].cnt;
	else
		return 0 + calc(u << 1 | 1, mid + 1, r, lim);
}
void change(int pos, int u = 1, int l = 1, int r = n)
{
	if (l == r)
		return;
	int mid = l + r >> 1;
	if (pos <= mid)
		change(pos, u << 1, l, mid);
	else
		change(pos, u << 1 | 1, mid + 1, r);
	tr[u].max = myGreater(tr[u << 1].max, tr[u << 1 | 1].max) ? tr[u << 1].max : tr[u << 1 | 1].max;
	tr[u].cnt = calc(u << 1 | 1, mid + 1, r, tr[u << 1].max);
}

int main(void)
{
	read >> n >> m;
	build();
	for (int i = 1, x, y; i <= m; ++i) {
		read >> x >> y;
		h[x] = y;
		change(x);
		printf("%d\n", calc(1, 1, n, 0));
	}
	return 0;
}
