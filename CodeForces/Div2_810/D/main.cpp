#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 2e5 + 10;

struct node
{
	int cnt;
	i64 tag;
	i64 pre, suf;
	friend node operator+(const node &a, const node &b)
	{
		node res;
		res.cnt = 0;
		res.tag = 0;
		res.pre = std::max(a.pre, b.pre);
		res.suf = std::max(a.suf, b.suf);
		return res;
	}
};
struct Query
{
	int a, b, c;
	bool operator<(const Query &other) const
	{ return a < other.a; }
};

i32 n, m;
i32 pos[N], rain[N], id[N];
node tr[N << 2];
char res[N];
vi32 nums;

inline int getIndex(int x)
{ return std::lower_bound(nums.begin(), nums.end(), x) - nums.begin(); }
void build(int u = 1, int l = 0, int r = nums.size() - 1)
{
	tr[u].tag = 0;
	if (l == r) {
		tr[u].pre = -nums[l];
		tr[u].suf = +nums[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void addNode(int u, int val)
{
	tr[u].tag += val;
	tr[u].pre += val;
	tr[u].suf += val;
}
void spread(int u)
{
	if (tr[u].tag) {
		addNode(u << 1, tr[u].tag);
		addNode(u << 1 | 1, tr[u].tag);
		tr[u].tag = 0;
	}
}
void add(int L, int R, int val, int u = 1, int l = 0, int r = nums.size() - 1)
{
	if (L <= l && r <= R) {
		addNode(u, val);
		return;
	}
	spread(u);
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, val, u << 1, l, mid);
	if (R > mid) add(L, R, val, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void add2(int L, int R, int val, int u = 1, int l = 0, int r = nums.size() - 1)
{
	if (L <= l && r <= R) {
		tr[u].cnt += 1;
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) add2(L, R, val, u << 1, l, mid);
	if (R > mid) add2(L, R, val, u << 1 | 1, mid + 1, r);
}
void change(int cnt = 0, int u = 1, int l = 0, int r = nums.size() - 1)
{
	cnt += tr[u].cnt;
	if (l == r) {
		printf("l = %d, pre = %lld, suf = %lld\n", l, tr[u].pre, tr[u].suf);
		printf("cnt = %d\n", tr[u].cnt);
		tr[u].pre += 1ll * cnt * nums[l];
		tr[u].suf += 1ll * cnt * nums[l];
		return;
	}
	int mid = l + r >> 1;
	spread(u);
	change(cnt, u << 1, l, mid);
	change(cnt, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
node query(int L, int R, int u = 1, int l = 0, int r = nums.size() - 1)
{
	if (L > R) return tr[0];
	if (L <= l && r <= R)
		return tr[u];
	spread(u);
	int mid = l + r >> 1;
	if (L <= mid && R > mid)
		return query(L, R, u << 1, l, mid) + query(L, R, u << 1 | 1, mid + 1, r);
	else if (L <= mid)
		return query(L, R, u << 1, l, mid);
	else
		return query(L, R, u << 1 | 1, mid + 1, r);
}

void work(void)
{
	read >> n >> m;
	std::vector<Query> rn(n);
	nums.resize(n);
	for (int i = 1; i <= n; ++i) {
		rn[i - 1].c = i;
		read >> rn[i - 1].a >> rn[i - 1].b;
	}
	std::sort(rn.begin(), rn.end());
	for (int i = 1; i <= n; ++i) {
		id[i] = rn[i - 1].c;
		pos[i] = rn[i - 1].a;
		rain[i] = rn[i - 1].b;
		nums[i - 1] = pos[i];
	}
	for (int i = 1; i <= n; ++i) {
		printf("i = %d, pos = %d, rain = %d\n", i, pos[i], rain[i]);
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	build();
	for (int i = 1; i <= n; ++i) {
		int j = getIndex(pos[i]);
		if (j != 0) {
			add(0, j - 1, rain[i] - pos[i]);
			add2(0, j - 1, 1);
		}
		add(j, nums.size() - 1, rain[i] + pos[i]);
		add2(j, nums.size() - 1, -1);
	}
	change();
	for (int i = 1; i <= n; ++i) {
		bool sec = 1;
		int ps = getIndex(pos[i]);
		printf("ps = %d, pre = %lld, suf = %lld\n", ps, query(0, ps - 1).pre, query(ps, nums.size() - 1).suf);
		if (ps != 0) {
			if (query(1, ps - 1).pre - (rain[i] - pos[i]) > m) {
				sec = 0;
			}
		}
		if (query(ps, nums.size() - 1).suf - (rain[i] + pos[i]) > m) {
			sec = 0;
		}
		res[id[i]] = sec ? '1' : '0';
	}
	for (int i = 1; i <= n; ++i)
		putchar(res[i]);
	putchar('\n');
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
/*
   p[i] - abs(x[i] - pos);
   <=>
   sum(pos >= x[i]) p[i] + x[i] - pos
   +
   sum(pos < x[i]) p[i] - x[i] + pos;
   lsum[i] = sum(x[j] <= i) p[j] + x[j];
   rsum[i] = sum(x[j] > i) p[j] - x[j];
   for all pos, val[i] = lsum[pos] + rsum[pos] + del[pos] * pos;
*/
