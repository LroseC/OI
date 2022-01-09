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

int n;
vector<int> nums;
int w[N], val[N], tval[N];

bool dfs(int u, int goal)
{
	tval[u] = val[u];
	if ((u << 1) <= n) {
		if (dfs(u << 1, goal)) return 1;
		if (tval[u << 1] > 0)
			tval[u] += tval[u << 1];
	}
	if ((u << 1 | 1) <= n) {
		if (dfs(u << 1 | 1, goal)) return 1;
		if (tval[u << 1 | 1] > 0)
			tval[u] += tval[u << 1 | 1];
	}
	if (tval[u] >= goal) return 1;
	return 0;
}

bool check(int x, int y)
{
	for (int i = 1; i <= n; ++i)
		val[i] = w[i] < x ? -1 : 1;
	bool tmp = dfs(1, 1 + y);
	return tmp;
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
	for (int i = 1; i <= n; ++i)
		w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();

	for (int i = 0; i < n; ++i) {
		int l = 0, r = n - 1, mid;
		while (l < r) {
			mid = l + r + 1 >> 1;
			if (check(mid, i)) l = mid;
			else r = mid - 1;
		}
		printf("%d ", nums[l]);
	}
	puts("");
	return 0;
}

/*
   思路：二分 + 树形DP 
   把所有小于 mid 的值设为 -1, 大于等于当前二分的值设为 1
   然后树形DP, 把树上最大总和求出
   复杂度 n^2logn, 60pts
*/
