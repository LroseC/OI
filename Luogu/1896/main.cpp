#include <set>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 20, K = 100, M = 1 << 9;
inline int lowbit(int x) { return x & -x; }
inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, k;
set<int> S;
int cnt[M];
LL f[N][K][M];

/*
状态表示：f[i][j][state] 表示前 i 行放了 j 个国王且第 i 行放置方式为 state 的所有方案集合
性质：个数
状态计算：f[i][j][state] += f[i - 1][j - |state|][state'];
*/

void Print(int x)
{
	for (int j = 0; j < n; ++j)
		if (x >> j & 1) putchar('1');
		else putchar('0');
}

int getcnt(int x)
{
	int res = 0;
	while (x) { x -= lowbit(x); ++res; }
	return res;
}

void dfs(int i, int state)
{
	if (i == n) {
		S.insert(state);
		cnt[state] = getcnt(state);
		return;
	}
	if (!(state >> i - 1 & 1)) dfs(i + 1, state | (1 << i));
	dfs(i + 1, state);
}

int main(void)
{
	n = read(), k = read();
	dfs(0, 0);
	f[0][0][0] = 1;
	for (int i = 1; i <= n + 1; ++i)
		for (int j = 0; j <= k; ++j)
			for (int state : S)
				for (int statep : S) {
					if (state & statep) continue;
					if (S.find(state ^ statep) == S.end()) continue;
					int c = cnt[state];
					if (j - c < 0) continue;
					f[i][j][state] += f[i - 1][j - c][statep];
				}
	#ifdef DEBUG
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= k; ++j)
			for (int state : S) {
				printf("f[%d][%d][", i, j);
				Print(state);
				printf("] = %d\n", f[i][j][state]);
			}
	#endif
	printf("%lld\n", f[n + 1][k][0]);
	return 0;
}