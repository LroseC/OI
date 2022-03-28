#include <vector>
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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 3e5 + 10, B = 550;

struct Query
{
	int id, l, r;
	bool operator<(const Query &other) const
	{
		if (l / B != other.l / B) return l < other.l;
		return (l / B & 1) ? r < other.r : r > other.r;
	}
};

int n, m;
int cnt[N];
i64 val[N], ans[N];
std::vector<i64> nums;

void Add(int pos, i64 &res)
{
	++cnt[val[pos]];
	if (cnt[val[pos]] > 1)
		res ^= nums[val[pos]];
}
void Dec(int pos, i64 &res)
{
	if (cnt[val[pos]] > 1)
		res ^= nums[val[pos]];
	--cnt[val[pos]];
}

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		nums.emplace_back(val[i]);
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		val[i] = std::lower_bound(nums.begin(), nums.end(), val[i]) - nums.begin();
	read >> m;
	std::vector<Query> q(m);
	for (int i = 0; i < m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(q.begin(), q.end());
	i64 res = 0;
	int L = 1, R = 0;
	for (int i = 0; i < m; ++i) {
		while (L > q[i].l) Add(--L, res);
		while (R < q[i].r) Add(++R, res);
		while (L < q[i].l) Dec(L++, res);
		while (R > q[i].r) Dec(R--, res);

		ans[q[i].id] = res;
	}
	for (int i = 0; i < m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
