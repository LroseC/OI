#include <vector>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using PII = std::pair<i32, i32>;
const int N = 5e5 + 10;
template<typename T>
void maxx(T &a, T b) { a = std::max(a, b); }

struct node
{
	i64 max[3];
	friend node operator+(const node &a, const node &b)
	{
		node res;
		for (int i = 0; i < 3; ++i)
			res.max[i] = std::max(a.max[i], b.max[i]);
		return res;
	}
};
int n;
vi64 nums;
int a[N];
i64 sum[N], f[N];
node tr[N << 3];

void build(int u = 1, int l = 0, int r = nums.size())
{
	for (int i = 0; i < 3; ++i)
		tr[u].max[i] = 0xcfcfcfcfcfcfcfcf;
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
}
void add(int pos, int u = 1, int l = 0, int r = nums.size())
{
	if (l == r) {
		maxx(tr[u].max[0], f[pos] - pos);
		maxx(tr[u].max[1], f[pos]);
		maxx(tr[u].max[2], f[pos] + pos);
		return;
	}
	int mid = l + r >> 1;
	if (sum[pos] <= mid)
		add(pos, u << 1, l, mid);
	else
		add(pos, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
node query(int L, int R, int u = 1, int l = 0, int r = nums.size())
{
	if (L <= l && r <= R)
		return tr[u];
	int mid = l + r >> 1;
	if (L <= mid && R > mid)
		return query(L, R, u << 1, l, mid) + query(L, R, u << 1 | 1, mid + 1, r);
	if (L <= mid)
		return query(L, R, u << 1, l, mid);
	if (R > mid)
		return query(L, R, u << 1 | 1, mid + 1, r);
}

void work(void)
{
	read >> n;
	nums.resize(n + 1);
	nums[0] = sum[0] = 0;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		nums[i] = sum[i] = sum[i - 1] + a[i];
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 0; i <= n; ++i) {
		sum[i] = std::lower_bound(nums.begin(), nums.end(), sum[i]) - nums.begin();
	}
	build();
	add(0);
	for (int r = 1; r <= n; ++r) {
		f[r] = 0xcfcfcfcfcfcfcfcf;
		if (0 <= sum[r] - 1) {
			maxx(f[r], r + query(0, sum[r] - 1).max[0]);
		}
		maxx(f[r], query(sum[r], sum[r]).max[1]);
		if (sum[r] + 1 <= nums.size()) {
			maxx(f[r], query(sum[r] + 1, nums.size()).max[2] - r);
		}
		add(r);
	}
	printf("%lld\n", f[n]);
}

int main(void)
{
	//Think twice, code once.
//	std::ios::sync_with_stdio(false);
	int tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
