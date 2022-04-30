#include <cctype>
#include <cstdio>
#include <algorithm>

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
const int N = 6e5 + 10;

struct node
{
	int tag, cnt, ccnt, res;
};
node operator+(const node &a, const node &b)
{
	node res; res.tag = 0;
	res.cnt = std::min(a.cnt, b.cnt);
	res.ccnt = 0;
	res.ccnt += (a.cnt == res.cnt) * a.ccnt;
	res.ccnt += (b.cnt == res.cnt) * b.ccnt;
	res.res = a.res + b.res;
	return res;
}

int n, m;
int origin;
int a[N], cnt[N];
node tr[N << 3];

void addNode(int u, int val)
{
	tr[u].tag += val;
	tr[u].cnt += val;
	tr[u].res = (tr[u].cnt == 0) * tr[u].ccnt;
}
void spread(int u, int l, int r)
{
	if (tr[u].tag) {
		addNode(u << 1, tr[u].tag);
		addNode(u << 1 | 1, tr[u].tag);
		tr[u].tag = 0;
	}
}
void build(int u = 1, int l = -N, int r = N)
{
	if (l == r) {
		tr[u].cnt = 0;
		tr[u].ccnt = 1;
		tr[u].res = 1;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void add(int L, int R, int x, int u = 1, int l = -N, int r = N)
{
	if (L <= l && r <= R) {
		addNode(u, x);
		return;
	}
	spread(u, l, r);
	int mid = l + r >> 1;
	if (L <= mid)
		add(L, R, x, u << 1, l, mid);
	if (R > mid)
		add(L, R, x, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
int query(int L, int R, int u = 1, int l = -N, int r = N)
{
	if (L <= l && r <= R)
		return tr[u].res;
	spread(u, l, r);
	int mid = l + r >> 1;
	int res = 0;
	if (L <= mid)
		res += query(L, R, u << 1, l, mid);
	if (R > mid)
		res += query(L, R, u << 1 | 1, mid + 1, r);
	return res;
}

int main(void)
{
	read >> n >> m;
	build();
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		++cnt[a[i]];
		int pos = a[i] - cnt[a[i]] + 1;
		add(pos, pos, 1);
	}
	for (int Id = 1; Id <= m; ++Id) {
		int pos, x;
		read >> pos >> x;
		if (pos == 0) {
			if (x == 1 && cnt[origin + n])
				add(origin + n - cnt[origin + n] + 1, origin + n, -x);
			origin -= x;
			if (x == -1 && cnt[origin + n])
				add(origin + n - cnt[origin + n] + 1, origin + n, -x);
		}
		else {
			int ps = a[pos] - cnt[a[pos]] + 1;
			if (a[pos] <= origin + n)
				add(ps, ps, -1);
			--cnt[a[pos]];
			a[pos] = x + origin;
			++cnt[a[pos]];
			ps = a[pos] - cnt[a[pos]] + 1;
			if (a[pos] <= origin + n)
				add(ps, ps, 1);
		}
		printf("%d\n", query(origin + 1, origin + n));
	}
	return 0;
}
