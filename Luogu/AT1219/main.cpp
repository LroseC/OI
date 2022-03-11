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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 1e5 + 10, B = 316;

struct Query
{
	int id, l, r;
	bool operator<(const Query &other) const
	{
		if (l / B != other.l / B) return l < other.l;
		return r < other.r;
	}
};

int n, m;
int type[N];
i64 cnt[N], ans[N];
Query q[N];
std::vector<int> nums;

void Add(int pos, i64 &res)
{
	++cnt[type[pos]];
	res = std::max(res, 1ll * cnt[type[pos]] * nums[type[pos]]);
}
void Dec(int pos)
{
	--cnt[type[pos]];
}

int main(void)
{
	read >> n >> m;
	nums.resize(n);
	for (int i = 1; i <= n; ++i) {
		read >> type[i];
		nums[i - 1] = type[i];
	}
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		type[i] = std::lower_bound(nums.begin(), nums.end(), type[i]) - nums.begin();

	std::sort(q + 1, q + 1 + m);

	int L, R; i64 res;
	for (int i = 1; i <= m; ++i) {
		if (i == 1 || q[i].l / B != q[i - 1].l / B) {
			res = 0;
			L = q[i].l / B * B + B;
			R = L - 1;
			memset(cnt, 0, sizeof cnt);
		}
		if (q[i].l / B == q[i].r / B) {
			i64 res = 0;
			for (int j = q[i].l; j <= q[i].r; ++j)
				Add(j, res);
			ans[q[i].id] = res;
			for (int j = q[i].l; j <= q[i].r; ++j)
				Dec(j);
		}
		else {
			while (R < q[i].r) Add(++R, res);
			i64 tmp = res;
			for (int j = L - 1; j >= q[i].l; --j) Add(j, res);
			ans[q[i].id] = res;
			for (int j = L - 1; j >= q[i].l; --j) Dec(j);
			res = tmp;
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
