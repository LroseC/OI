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

struct seg
{
	i64 val;
	int left, right;
};
seg operator+(const seg &a, const seg &b)
{
	seg res;
	res.left = a.left;
	res.right = b.right;
	res.val = a.val + b.val;
	return res;
}
struct segNode
{
	seg res[4];
};

int n, m;
segNode tr[N << 2];

seg merge(seg x1, seg x2, seg y1, seg y2)
{
	if (x1.val == 0)
		return y1;
	if (y1.val == 0)
		return x1;
	if (x1.right && y1.left) {
		if (x1.right >= y1.left)
			return x1 + y2;
		else
			return x2 + y1;
	}
	return x1 + y1;
}
void maintain(int u)
{
	tr[u].res[0] = merge(
		tr[u << 1].res[2], tr[u << 1].res[0],
		tr[u << 1 | 1].res[1], tr[u << 1 | 1].res[0]
	);
	tr[u].res[1] = merge(
		tr[u << 1].res[3], tr[u << 1].res[1],
		tr[u << 1 | 1].res[1], tr[u << 1 | 1].res[0]
	);
	tr[u].res[2] = merge(
		tr[u << 1].res[2], tr[u << 1].res[0],
		tr[u << 1 | 1].res[3], tr[u << 1 | 1].res[2]
	);
	tr[u].res[3] = merge(
		tr[u << 1].res[3], tr[u << 1].res[1],
		tr[u << 1 | 1].res[3], tr[u << 1 | 1].res[2]
	);
}
void change(int pos, int val, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u].res[3].val = val;
		tr[u].res[3].left = tr[u].res[3].right = val;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
		change(pos, val, u << 1, l, mid);
	else
		change(pos, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		int x; read >> x;
		change(i, x);
	}
	read >> m;
	while (m--) {
		int x, y; read >> x >> y;
		change(x, y);
		printf("%lld\n", tr[1].res[3].val);
	}
	return 0;
}
