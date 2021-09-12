#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 1010;
const int mod = 1e9 + 7;
inline int lowbit(int x) { return x & -x; }

int T;
int a[N];
int tr[N];
int f[N][N];
vector<int> nums;

/*
状态表示: f[i][j] 表示以第 i 个数为结尾,长度为 j 的上升子序列的个数
状态计算: f[i][j] = for (last = 1; last < i; ++last) f[last][j - 1] * (a[last] < a[i]);
*/

void add(int k, int x)
{
	for (int i = k; i < N; i += lowbit(i)) tr[i] = (tr[i] + x) % mod;
}
int query(int k)
{
	int res = 0;
	for (int i = k; i; i -= lowbit(i)) res = (res + tr[i]) % mod;
	return res;
}

int main(void)
{
	T = read();
	for (int C = 1; C <= T; ++C) {
		int n = read(), m = read();
		nums.clear();
		for (int i = 1; i <= n; ++i) {
			a[i] = read();
			nums.emplace_back(a[i]);
		}
		sort(nums.begin(), nums.end());
		nums.erase(unique(nums.begin(), nums.end()), nums.end());
		for (int i = 1; i <= n; ++i) a[i] = upper_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
		for (int i = 1; i <= n; ++i) f[i][1] = 1;
		for (int j = 2; j <= m; ++j) {
			memset(tr, 0, sizeof tr);
			for (int i = 1; i <= n; ++i) {
				f[i][j] = query(a[i] - 1);
				add(a[i], f[i][j - 1]);
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i) ans = (ans + f[i][m]) % mod;
		printf("Case #%d: %d\n", C, ans);
	}
}