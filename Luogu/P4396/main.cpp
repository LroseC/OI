#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10, LEN = 320;

struct Query
{
	int id;
	int l, r, a, b;
	bool operator<(const Query &other) const
	{
		if (l / LEN != other.l / LEN)
			return l / LEN < other.l / LEN;
		return r < other.r;
	}
};

int n, m;
int a[N], V;
Query q[N];
pair<int, int> ans[N];
int sum[N];
int sumB[N], boolsumB[N];

void add(int x)
{
	if (!sum[a[x]])
		++boolsumB[a[x] / LEN];
	++sum[a[x]];
	++sumB[a[x] / LEN];
}
void dec(int x)
{
	--sumB[a[x] / LEN];
	--sum[a[x]];
	if (!sum[a[x]])
		--boolsumB[a[x] / LEN];
}
pair<int, int> query(int L, int R)
{
	R = min(R, V);
	int LB = L / LEN, RB = R / LEN;
	pair<int, int> res = make_pair(0, 0);
	if (LB == RB) {
		for (int i = L; i <= R; ++i) {
			res.first += sum[i];
			res.second += (bool)sum[i];
		}
		return res;
	}
	else {
		for (int i = L; i / LEN == LB; ++i) {
			res.first += sum[i];
			res.second += (bool)sum[i];
		}
		for (int i = R; i / LEN == RB; --i) {
			res.first += sum[i];
			res.second += (bool)sum[i];
		}
		for (int i = LB + 1; i < RB; ++i) {
			res.first += sumB[i];
			res.second += boolsumB[i];
		}
		return res;
	}
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		V = max(V, a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		cin >> q[i].l >> q[i].r >> q[i].a >> q[i].b;
	}
	sort(q + 1, q + 1 + m);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i) {
		while (r < q[i].r) add(++r);
		while (l > q[i].l) add(--l);
		while (r > q[i].r) dec(r--);
		while (l < q[i].l) dec(l++);
		ans[q[i].id] = query(q[i].a, q[i].b);
	}
	for (int i = 1; i <= m; ++i)
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}
