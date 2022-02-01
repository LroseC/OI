#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

#define int long long

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
} IO;

using LL = long long;

struct Operation
{
	int x, l, r, val;

	Operation(void) : x(0), l(0), r(0), val(0) {}
	Operation(int _x, int _l, int _r, int _v) : x(_x), l(_l), r(_r), val(_v) {}
	bool operator<(const Operation &other) const
	{
		if (x != other.x)
			return x < other.x;
		return val < other.val;
	}
};

int n, W, H;
vector<int> nums;
vector<Operation> op;

const int N = 2e4 + 10;

namespace SegmentTree
{
	struct node
	{
		LL tag, max;
	} tr[N << 2];

	void maintain(int u)
	{
		tr[u].max = max(tr[u << 1].max, tr[u << 1 | 1].max) + tr[u].tag;
	}
	void add(int u, int val)
	{
		tr[u].tag += val;
		tr[u].max += val;
	}
	void Add(int L, int R, int val, int l = 0, int r = nums.size(), int u = 1)
	{
		if (L <= l && r <= R) {
			add(u, val);
			return;
		}
		int mid = l + r >> 1;
		if (L <= mid) Add(L, R, val, l, mid, u << 1);
		if (R > mid) Add(L, R, val, mid + 1, r, u << 1 | 1);
		maintain(u);
	}
}

signed main(void)
{
	while (~scanf("%lld%lld%lld", &n, &W, &H)) {
		op.clear();
		nums.clear();
		for (int i = 1; i <= n; ++i) {
			int x, y, val;
			IO >> x >> y >> val;
			op.emplace_back(x, y, y + H, val);
			op.emplace_back(x + W, y, y + H, -val);
			nums.emplace_back(y);
			nums.emplace_back(y + H);
		}
		sort(nums.begin(), nums.end());
		nums.erase(unique(nums.begin(), nums.end()), nums.end());
		for (int i = 0; i < op.size(); ++i) {
			op[i].l = lower_bound(nums.begin(), nums.end(), op[i].l) - nums.begin();
			op[i].r = lower_bound(nums.begin(), nums.end(), op[i].r) - nums.begin();
		}
		LL ans = 0;
		sort(op.begin(), op.end());
		for (int i = 0; i < op.size(); ++i) {
			int l = op[i].l, r = op[i].r, val = op[i].val;
			SegmentTree::Add(l, r - 1, val);
			ans = max(ans, SegmentTree::tr[1].max);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
