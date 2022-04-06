#include <cmath>
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

const int N = 5e5 + 10;

int n;
int val[N];
double k;
std::vector<int> nums;
int fa[N], sz[N], ans[N];
int minx[N << 2], tag[N << 2];

void addnode(int u, int v)
{
	tag[u] += v;
	minx[u] += v;
}
void spread(int u)
{
	if (tag[u]) {
		addnode(u << 1, tag[u]);
		addnode(u << 1 | 1, tag[u]);
		tag[u] = 0;
	}
}
void maintain(int u) { minx[u] = std::min(minx[u << 1], minx[u << 1 | 1]); }
void add(int L, int R, int val, int u = 1, int l = 0, int r = nums.size() - 1)
{
	if (L <= l && r <= R) {
		addnode(u, val);
		return;
	}
	spread(u);
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, val, u << 1, l, mid);
	if (R > mid) add(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int sz, int u = 1, int l = 0, int r = nums.size() - 1)
{
	if (l == r) {
		if (minx[u] < sz)
			return -1;
		return l;
	}
	spread(u);
	int mid = l + r >> 1;
	if (minx[u << 1] >= sz)
		return std::max(query(sz, u << 1 | 1, mid + 1, r), mid);
	else
		return query(sz, u << 1, l, mid);
}

int main(void)
{
	read >> n;
	scanf("%lf", &k);
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		fa[i] = floor(i / k);
		nums.emplace_back(val[i]);
	}
	std::sort(nums.begin(), nums.end());
	std::sort(val + 1, val + 1 + n);
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i) {
		val[i] = std::lower_bound(nums.begin(), nums.end(), val[i]) - nums.begin();
		add(0, val[i], 1);
	}
	for (int i = 1; i <= n; ++i) sz[i] = 1;
	for (int i = n; i >= 1; --i) sz[fa[i]] += sz[i];
	for (int i = 1; i <= n; ++i) {
		if (fa[i] && fa[i] != fa[i - 1])
			add(0, ans[fa[i]], sz[fa[i]] - 1);
		ans[i] = query(sz[i]);
		add(0, ans[i], -sz[i]);
	}
	for (int i = 1; i <= n; ++i)
		printf("%d ", nums[ans[i]]);
	puts("");
	return 0;
}
