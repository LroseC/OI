#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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
} IO;

const int N = 2e5 + 10;

int maxval, ans[N];
int n, w[N], pos[N];
int val[N], tval[N];
vector<int> nums;

void maintain(int u)
{
	tval[u] = val[u];
	if ((u << 1) <= n && tval[u << 1] > 0)
		tval[u] += tval[u << 1];
	if ((u << 1 | 1) <= n && tval[u << 1 | 1] > 0)
		tval[u] += tval[u << 1 | 1];
	maxval = max(maxval, tval[u]);
}
void update(int x)
{
	int u = pos[x];
	val[u] = 1;
	maintain(u);
	while (u >> 1) {
		maintain(u >> 1);
		u = u >> 1;
	}
}
void dfs(int u)
{
	tval[u] = val[u];
	if ((u << 1) <= n)
		dfs(u << 1);
	if ((u << 1 | 1) <= n)
		dfs(u << 1 | 1);
	maintain(u);
}

int main(void)
{
	IO >> n;
	for (int i = 1; i <= n; ++i) {
		IO >> w[i];
		nums.emplace_back(w[i]);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i) {
		w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();
		pos[w[i]] = i;
	}

	for (int i = 1; i <= n; ++i)
		val[i] = w[i] < n - 1 ? -1 : 1;
	dfs(1);
	int lastans = -1;
	for (int i = n - 1; i >= 0; --i) {
		int y = maxval - 1;
		for (int j = y; j >= lastans; --j) ans[j] = max(ans[j], nums[i]);
		lastans = y;
		update(i - 1);
	}
	for (int i = 0; i < n; ++i)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}

/*
   思路：暴力的思路是对于每一个询问的 a 二分答案求解, 复杂度 n^2logn.
   从中我们可以想到另一个思路: 我们直接枚举答案，然后用线段树区间修改. 最后单点查询输出每一个 a 的答案.
   你也许会问: 枚举答案不也是 n^2logn 的吗? 然而并不是这样，枚举答案时每次只会修改一个点的值, 我们向上递归修改答案即可.
   最终复杂度 nlogn.
   似乎常数略大? 最后一个样例跑了 6s.
*/
