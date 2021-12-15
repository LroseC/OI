#include <vector>
#include <cctype>
#include <cstdio>

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

using LL = long long;
const int N = 1e5 + 10;

struct Query
{
	int x, l, r, v;
	Query(void) { x = l = r = v = 0; }
	Query(int _x, int _l, int _r, int _v) : x(_x), l(_l), r(_r), v(_v) {}
};
struct node
{
	int l, r;
	int res;
	int cnt;
}

int n;
node tr[N << 2];
Query q[N << 1];
vector<int> nums;

void maintain(int u)
{
	if (tr[u].cnt)
		tr[u].res = nums[r + 1] - nums[l];
	else
		tr[u].res = tr[u << 1].res + tr[u << 1 | 1].res;
}
void build(int u, int l, int r)
{
	if (l == r) {
		tr[u].l = l; tr[u].r = r;
		tr[u].res = tr[u].cnt = 0;
		return 0;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) {
		int x1, x2, y1, y2;
		io >> x1 >> y1 >> x2 >> y2;
		nums.emplace_back(y1);
		nums.emplace_back(y2);
		q[++idx] = Query(x1, y1, y2, 1);
		q[++idx] = Query(x2, y1, y2, -1);
	}
	sort(q + 1, q + 1 + idx);
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= idx; ++i) {
		q[i].l = lower_bound(nums.begin(), nums.end(), q[i].l) - nums.begin();
		q[i].r = lower_bound(nums.begin(), nums.end(), q[i].r) - nums.begin() - 1;
	}
	LL res = 0;
	build(1, 0, nums.size());
	for (int i = 1; i <= idx; ++i) {
		if (i != 1)
			res += 1ll * (q[i].x - q[i - 1].x) * query();
		add(q[i].l, q[i].r, q[i].v);
	}
	printf("%lld\n", res);
	return 0;
}
