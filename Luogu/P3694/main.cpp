#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = 1 << 20;
const int INF = 0x3f3f3f3f;
inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, m;
int f[M];
int id[N];
int len[30];
int sum[N][30];

void Print(int x)
{
	for (int i = 0; i < m; ++i)
		if (x >> i & 1) putchar('1');
		else putchar('0');
}

void dp(int state)
{
	if (f[state] != INF) return;
	int L = 0;
	for (int i = 0; i < m; ++i)
		if ((state >> i) & 1)
			L += len[i];

	for (int i = 0; i < m; ++i)
		if ((state >> i) & 1) {
			dp(state ^ (1 << i));
			f[state] = min(f[state], f[state ^ (1 << i)] + len[i] - (sum[L][i] - sum[L - len[i]][i]));
		}
}

int main(void)
{
	n = read(), m = read();
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for (int i = 1; i <= n; ++i) {
		id[i] = read() - 1;
		++len[id[i]];
		for (int j = 0; j < m; ++j)
			sum[i][j] = sum[i - 1][j] + (id[i] == j);
	}
	dp((1 << m) - 1);
	printf("%d\n", f[(1 << m) - 1]);
	return 0;
}
/*
f[state] 表示已经将状态中的所有乐队排在前面最少的出列数量
*/