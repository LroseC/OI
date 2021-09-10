#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 1e5 + 10;
const int INF = 1e9;

struct Range
{
	int l, r, v;
	bool operator<(const Range b) const
	{
		return r < b.r;
	}
};

int n, Left, Right;
Range rg[N];
int node[N << 2];

void Maintain(int p) { node[p] = min(node[p << 1], node[p << 1 | 1]); }
void Build(int p = 1, int l = 0, int r = Right)
{
	if (l == r) {
		node[p] = l < Left ? 0 : INF;
		return;
	}
	int mid = l + r >> 1;
	Build(p << 1, l, mid);
	Build(p << 1 | 1, mid + 1, r);
	Maintain(p);
}
void Update(int k, int val, int p = 1, int l = 0, int r = Right)
{
	if (l == r) {
		node[p] = min(node[p], val);
		return;
	}
	int mid = l + r >> 1;
	if (k <= mid) Update(k, val, p << 1, l, mid);
	else Update(k, val, p << 1 | 1, mid + 1, r);
	Maintain(p);
}
int Query(int L, int R, int p = 1, int l = 0, int r = Right)
{
	if (L <= l && r <= R) return node[p];
	int mid = l + r >> 1;
	int res = INF;
	if (L <= mid) res = min(res, Query(L, R, p << 1, l, mid));
	if (R > mid) res = min(res, Query(L, R, p << 1 | 1, mid + 1, r));
	return res;
}

int main(void)
{
	n = read(), Left = read() + 1, Right = read() + 1;
	for (int i = 0; i < n; ++i) {
		int l = read(), r = read(), v = read();
		rg[i]  ={l + 1, r + 1, v};
	}
	sort(rg, rg + n);
	Build();
	for (int i = 0; i < n; ++i) {
		int l = rg[i].l, r = rg[i].r, w = rg[i].v;
		int v = Query(l - 1, r - 1) + w;
		Update(r, v);
	}
	int ans = Query(Right, Right);
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}