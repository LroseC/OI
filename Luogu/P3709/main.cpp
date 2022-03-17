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

const int N = 2e5 + 10, B = 447;

struct Query
{
	int id, l, r;
	friend bool operator<(const Query &a, const Query &b)
	{
		if (a.l / B != b.l / B) return a.l < b.l;
		return a.r < b.r;
	}
};

int n, m;
int type[N], ans[N], cnt[N];

void Add(int pos, int &res)
{
	++cnt[type[pos]];
	res = std::max(cnt[type[pos]], res);
}
void Dec(int pos)
{
	--cnt[type[pos]];
}

int main(void)
{
	read >> n >> m;
	std::vector<int> nums(n);
	for (int i = 1; i <= n; ++i) {
		read >> type[i];
		nums[i - 1] = type[i];
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		type[i] = std::lower_bound(nums.begin(), nums.end(), type[i]) - nums.begin() + 1;

	std::vector<Query> q(m);
	for (int i = 0; i < m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(q.begin(), q.end());
	int L, R, res;
	for (int i = 0; i < m; ++i) {
		if (i == 0 || q[i].l / B != q[i - 1].l / B) {
			res = 0;
			std::memset(cnt, 0, sizeof cnt);
			L = q[i].l / B * B + B, R = L - 1;
		}
		if (q[i].l / B == q[i].r / B) {
			int res = 0;
			for (int j = q[i].l; j <= q[i].r; ++j)
				Add(j, res);
			for (int j = q[i].l; j <= q[i].r; ++j)
				Dec(j);
			ans[q[i].id] = res;
		}
		else {
			while (R < q[i].r)
				Add(++R, res);
			int tmp = res;
			for (int j = L - 1; j >= q[i].l; --j)
				Add(j, res);
			ans[q[i].id] = res;
			for (int j = q[i].l; j <= L - 1; ++j)
				Dec(j);
			res = tmp;
		}
	}
	for (int i = 0; i < m; ++i)
		printf("%d\n", -ans[i]);
	return 0;
}
