// copy from Acwing 300
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5010;
typedef long long LL;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, s;
LL f[N];
int t[N], c[N];
LL sumt[N], sumc[N];

/*
状态表示：f[i] 表示给前 i 个任务分组的所有方案集合
性质：费用最小
状态计算：f[i] = min { (int j = 0; j < i; ++j) f[j] + (s + sumt[j + 1 ~ i]) * sumc[j + 1 ~ i]
*/

int main(void)
{
	n = read();
	s = read();
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for (int i = 1; i <= n; ++i) {
		t[i] = read();
		c[i] = read();
		sumt[i] = sumt[i - 1] + t[i];
		sumc[i] = sumc[i - 1] + c[i];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < i; ++j)
			f[i] = min(f[i], f[j] + (sumc[i] - sumc[j]) * sumt[i] + (sumc[n] - sumc[j]) * s);
	printf("%lld\n", f[n]);
	return 0;
}
