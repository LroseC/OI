#include <cmath>
#include <queue>
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
const int N = 5e5 + 10;

int n;
double K;
int sz[N], val[N], ans[N];
std::vector<int> G[N], nums;
int tr[N << 2];

void maintain(int u) { tr[u] = tr[u << 1] + tr[u << 1 | 1]; }
void add(int pos, int val, int u = 1, int l = 0, int r = nums.size() - 1)
{
	if (l == r) {
		tr[u] += val;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
		add(pos, val, u << 1, l, mid);
	else
		add(pos, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int queryGreater(int x, int u = 1, int l = 0, int r = nums.size() - 1)
{
	if (l == r)
		return l;
	int mid = l + r >> 1;
	if (tr[u << 1 | 1] >= x)
		return queryGreater(x, u << 1 | 1, mid + 1, r);
	else
		return queryGreater(x - tr[u << 1 | 1], u << 1, l, mid);
}

void getSz(int u)
{
	sz[u] = 1;
	for (int v : G[u]) {
		getSz(v);
		sz[u] += sz[v];
	}
}
void bfsCalc(void)
{
	std::queue<int> q;
	q.emplace(1);
	while (q.size()) {
		int u = q.front(); q.pop();
		ans[u] = queryGreater(sz[u]);
		add(ans[u], -1);
		for (int v : G[u])
			q.emplace(v);
	}
}

int main(void)
{
//	freopen("iiidx.in", "r", stdin);
//	freopen("iiidx.out", "w", stdout);
	read >> n;
	scanf("%lf", &K);
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		nums.emplace_back(val[i]);
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		add(std::lower_bound(nums.begin(), nums.end(), val[i]) - nums.begin(), 1);
	for (int i = 1; i <= n; ++i)
		G[(int)std::floor(i / K)].emplace_back(i);
	getSz(0);
	bfsCalc();
	for (int i = 1; i <= n; ++i)
		printf("%d ", nums[ans[i]]);
	puts("");
	return 0;
}
