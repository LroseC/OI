#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch))  { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} IO;

using LL = long long;
const int N = 1.2e5 + 10;

struct PII
{
	int id, l, r;
	bool operator<(const PII &other) const
	{
		return r < other.r;
	}
};

int n, m;
int P[N];
PII q[N];
LL ans[N];
int stkmin[N], topmin;
int stkmax[N], topmax;

struct node
{
	int val, tag, cnt, tim;
	node(void) { val = tag = cnt = tim = 0; }
	node operator+(const node &other) const
	{
		node res;
		res.val = min(val, other.val);
		if (res.val == val) res.cnt += cnt;
		if (res.val == other.val) res.cnt += other.cnt;
		return res;
	}
} tr[N << 3];
LL allcnt[N << 3];

void update(int u, int tim)
{
	tr[u].tim += tim;
	allcnt[u] += 1ll * tim * tr[u].cnt;
}
void spread(int u)
{
	if (tr[u].tag) {
		int tag = tr[u].tag;
		tr[u].tag = 0;
		tr[u << 1].val += tag;
		tr[u << 1].tag += tag;
		tr[u << 1 | 1].val += tag;
		tr[u << 1 | 1].tag += tag;
	}
	if (tr[u].tim) {
		if (tr[u << 1].val == tr[u].val)
			update(u << 1, tr[u].tim);
		if (tr[u << 1 | 1].val == tr[u].val)
			update(u << 1 | 1, tr[u].tim);
		tr[u].tim = 0;
	}
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u].val = l;
		tr[u].tag = 0;
		tr[u].cnt = 1;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
	allcnt[u] = allcnt[u << 1] + allcnt[u << 1 | 1];
}
void add(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		tr[u].val += val;
		tr[u].tag += val;
		return;
	}
	spread(u);
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, val, u << 1, l, mid);
	if (R > mid) add(L, R, val, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
	allcnt[u] = allcnt[u << 1] + allcnt[u << 1 | 1];
}
LL query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		return allcnt[u];
	}
	spread(u);
	int mid = l + r >> 1;
	LL res = 0;
	if (L <= mid) res += query(L, R, u << 1, l, mid);
	if (R > mid) res += query(L, R, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
	allcnt[u] = allcnt[u << 1] + allcnt[u << 1 | 1];
	return res;
}

int main(void)
{
	IO >> n;
	for (int i = 1; i <= n; ++i) IO >> P[i];
	IO >> m;
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		IO >> q[i].l >> q[i].r;
	}
	sort(q + 1, q + 1 + m);
	build();
	for (int i = 1, j = 1; i <= n; ++i) {
		while (topmin && P[i] < P[stkmin[topmin]]) {
			--topmin;
			add(stkmin[topmin] + 1, stkmin[topmin + 1], +P[stkmin[topmin + 1]]);
		}
		while (topmax && P[i] > P[stkmax[topmax]]) {
			--topmax;
			add(stkmax[topmax] + 1, stkmax[topmax + 1], -P[stkmax[topmax + 1]]);
		}
		stkmin[++topmin] = i;
		stkmax[++topmax] = i;
		add(stkmin[topmin - 1] + 1, stkmin[topmin], -P[stkmin[topmin]]);
		add(stkmax[topmax - 1] + 1, stkmax[topmax], +P[stkmax[topmax]]);
		update(1, 1);
		while (j <= m && q[j].r == i) ans[q[j].id] = query(q[j].l, q[j].r), ++j;
	}
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
}
