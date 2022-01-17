#include <cctype>
#include <cstdio>
#include <cstring>

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

const int N = 310;

int len, m;
char str[N];
int digit[N];
int lenson, son[N];

int f[N][N];
int g[N][10];

void init(void)
{
}
int dp(int l, int r)
{
}

int main(void)
{
	IO >> m;
	scanf("%s", str + 1);
	len = strlen(str + 1);
	for (int i = 1; i <= len; ++i)
		digit[i] = str[i] - '0';
	scanf("%s", str + 1);
	lenson = strlen(str + 1);
	for (int i = 1; i <= lenson; ++i)
		son[i] = str[i] - '0';

	init();

	f[0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = 0; k < i; ++k) {
				f[i][j] = (f[i][j] + 1ll * f[k][j - 1] * dp(k + 1, i) % mod) % mod;
			}
	return 0;
}
/*
	思路: DP 套 DP? 然而我没有写过.
	主 DP: f[i][j] 表示前 i 位数 S 作为子串出现了 j 次的方案数.
	辅助 DP: dp(l, r) 表示 l 到 r 的区间内 S 作为子串出现 1 次的方案数.
	f[i][j] = sum(k = 0; k < i) f[k][j - 1] * dp(k + 1, i);
	边界: f[0][0] = 1;
	辅助 DP 用数位 DP 实现，寄搜可好写了，昨晚就写了一个 (差点寄了)
	貌似复杂度有点问题, 这记搜的复杂度应该不是乘上外层 DP 的复杂度吧，如果是就寄了.
	貌似没寄, 换成递推的貌似比较稳.
	不会递推, 寄了.
*/