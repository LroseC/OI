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

const int INF = 1e8;
const int N = 2.5e4 + 10, M = 1e6 + 10;

struct Range
{
	int l, r;
	bool operator<(const Range &b) const
	{
		return r < b.r;
	}
};

int node[M * 4];
int n, m;

void Maintain(int p)
{
	node[p] = min(node[p << 1], node[p << 1 | 1]);
}
void Build(int p = 1, int l = 0, int r = m)
{
	node[p] = INF;
	if (l == r) return;
	int mid = l + r >> 1;
	Build(p << 1, l, mid);
	Build(p << 1 | 1, mid + 1, r);
}
void Update(int k, int v, int p = 1, int l = 0, int r = m)
{
	if (l == r) {
		node[p] = min(node[p], v);
		return;
	}
	int mid = l + r >> 1;
	if (k <= mid) Update(k, v, p << 1, l, mid);
	else Update(k, v, p << 1 | 1, mid + 1, r);
	Maintain(p);
}
int Query(int L, int R, int p = 1, int l = 0, int r = m)
{
	if (L <= l && r <= R) return node[p];
	int res = INF;
	int mid = l + r >> 1;
	if (L <= mid) res = min(res, Query(L, R, p << 1, l, mid));
	if (R > mid) res = min(res, Query(L, R, p << 1 | 1, mid + 1, r));
	return res;
}

Range rg[N];

int main(void)
{
	n = read(), m = read();
	for (int i = 0; i < n; ++i) {
		int l = read(), r = read();
		rg[i] = {l, r};
	}
	sort(rg, rg + n);
	Build();
	Update(0, 0);
	for (int i = 0; i < n; ++i) {
		int l = rg[i].l, r = rg[i].r;
		int v = Query(l - 1, r - 1) + 1;
		Update(r, v);
	}
	int ans = Query(m, m);
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}