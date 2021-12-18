#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

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
} io;

const int N = 3e5 + 10;

struct PII
{
	int x, y;
	PII(void) { x = y = 0; }
	PII(int _x, int _y) : x(_x), y(_y) {}
	bool operator<(const PII &other) const
	{
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};

int n;
PII chess[N];
long long ans;
int stkmax[N], topmax;
int stkmin[N], topmin;

struct node
{
	int l, r;
	int val, tag, cnt;
} tr[N << 3];

void spread(int u)
{
	if (tr[u].tag) {
		tr[u << 1].tag += tr[u].tag;
		tr[u << 1 | 1].tag += tr[u].tag;
		tr[u << 1].val += tr[u].tag;
		tr[u << 1 | 1].val += tr[u].tag;
		tr[u].tag = 0;
	}
}
void maintain(int u)
{
	tr[u].val = min(tr[u << 1].val, tr[u << 1 | 1].val);
	tr[u].cnt = 0;
	if (tr[u].val == tr[u << 1].val) tr[u].cnt += tr[u << 1].cnt;
	if (tr[u].val == tr[u << 1 | 1].val) tr[u].cnt += tr[u << 1 | 1].cnt;
}
void build(int u = 1, int l = 1, int r = n)
{
	tr[u].l = l;
	tr[u].r = r;
	if (l == r) {
		tr[u].val = l;
		tr[u].tag = 0;
		tr[u].cnt = 1;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void add(int L, int R, int val, int u = 1)
{
	int l = tr[u].l, r = tr[u].r;
	if (L <= l && r <= R) {
		tr[u].val += val;
		tr[u].tag += val;
		return;
	}
	int mid = l + r >> 1;
	spread(u);
	if (L <= mid) add(L, R, val, u << 1);
	if (R > mid) add(L, R, val, u << 1 | 1);
	maintain(u);
}
int query(int val)
{
	return tr[1].val == val ? tr[1].cnt : 0;
}

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) {
		io >> chess[i].x >> chess[i].y;
	}
	sort(chess + 1, chess + 1 + n);
	build();
	for (int i = 1; i <= n; ++i) {
		while (topmax && chess[i].y > chess[stkmax[topmax]].y) {
			--topmax;
			add(stkmax[topmax] + 1, stkmax[topmax + 1], -chess[stkmax[topmax + 1]].y);
		}
		while (topmin && chess[i].y < chess[stkmin[topmin]].y) {
			--topmin;
			add(stkmin[topmin] + 1, stkmin[topmin + 1], +chess[stkmin[topmin + 1]].y);
		}
		stkmax[++topmax] = i;
		stkmin[++topmin] = i;
		add(stkmax[topmax - 1] + 1, stkmax[topmax], +chess[stkmax[topmax]].y);
		add(stkmin[topmin - 1] + 1, stkmin[topmin], -chess[stkmin[topmin]].y);
		ans += query(i);
	}
	printf("%lld\n", ans);
	return 0;
}
