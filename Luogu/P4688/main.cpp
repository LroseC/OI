#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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
const int S = 33410, N = 1e5 + 10, B = 316;

struct bitset
{
	i64 v[1563];
	void fill(void)
	{ std::memset(v, 0xff, sizeof v); }
	void clear(void)
	{ std::memset(v, 0, sizeof v); }
	int popcount(void)
	{
		int res = 0;
		for (int i = 0; i < 1563; ++i)
			res += __builtin_popcountl(v[i]);
		return res;
	}
};

struct Query
{
	int id, l, r;

	Query(void) {}
	Query(int _id, int _l, int _r) { id = _id, l = _l, r = _r; }
	bool operator<(const Query &other) const
	{
		if (l / B != other.l / B)
			return l < other.l;
		return (l / B & 1) ? r < other.r : r > other.r;
	}
};

int n, idx;
int pre[N], a[N], cnt[N], ans[N];
bitset bs[S];
Query q[S * 3];

void Add(int pos, bitset &res)
{
	++cnt[a[pos]];
	int tpos = pre[a[pos] - 1] + cnt[a[pos]];
	res.v[tpos / 64] ^= 1ll << (tpos % 64);
}
void Dec(int pos, bitset &res)
{
	int tpos = pre[a[pos] - 1] + cnt[a[pos]];
	res.v[tpos / 64] ^= 1ll << (tpos % 64);
	--cnt[a[pos]];
}
void merge(bitset &a, bitset &b)
{
	for (int i = 0; i < 1563; ++i)
		a.v[i] &= b.v[i];
}

void calc(int m)
{
	idx = 0;
	for (int i = 1; i <= m; ++i) {
		bs[i].fill();
		ans[i] = 0;
		for (int j = 1, l, r; j <= 3; ++j) {
			read >> l >> r;
			q[++idx] = Query(i, l, r);
			ans[i] += r - l + 1;
		}
	}
	std::sort(q + 1, q + 1 + idx);
	bitset res;
	res.clear();
	std::memset(cnt, 0, sizeof cnt);
	int L = 1, R = 0;
	for (int i = 1; i <= idx; ++i) {
		while (L > q[i].l) Add(--L, res);
		while (R < q[i].r) Add(++R, res);
		while (L < q[i].l) Dec(L++, res);
		while (R > q[i].r) Dec(R--, res);

		merge(bs[q[i].id], res);
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i] - 3 * bs[i].popcount());
}

int main(void)
{
//	freopen("xp.in", "r", stdin);
//	freopen("xp.out", "w", stdout);
	int m;
	read >> n >> m;
	std::vector<int> nums;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		nums.emplace_back(a[i]);
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;
		++pre[a[i]];
	}
	for (int i = 1; i <= n; ++i)
		pre[i] += pre[i - 1];
	while (m) {
		calc(std::min(m, 33400));
		m -= std::min(m, 33400);
	}
	return 0;
}
