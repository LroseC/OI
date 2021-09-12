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

const int N = 4010;
const int Mod = 1e9 + 7;

inline int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % Mod;
		base = 1ll * base * base % Mod;
		k >>= 1;
	}
	return res;
}
inline int getinv(int x)
{
	return qpow(x, Mod - 2);
}

int a, b, c, d;
int fac[N], inv[N];
/*
先考虑 T 有多少种情况：
显然，T 可以看作 0，1 形成的排列，且 0，1 本身无先后顺序
故 T 一共有 (c + d)! / c! / d! 种

然后考虑通过插入的方式构造串 S
显然，对于一串连续的 0 字符，无论把一个字符 0 插入在其中的任何一个地方，都会被视作同一种方案
那么就让字符 0 只能插到字符 1 之前或整个字符串末尾
对于字符 1 同理
我们枚举插在 T 后的字符 1，字符 2 的数量
然后即可用组合数学求出方案
*/

int C(int x, int y)
{
	if (x > y) return 0;
	return 1ll * fac[y] * inv[x] % Mod * inv[y - x] % Mod;
}

int main(void)
{
	a = read(), b = read(), c = read(), d = read();
	fac[0] = 1;
	inv[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % Mod;
	for (int i = 1; i < N; ++i) inv[i] = getinv(fac[i]);
	if (!c || !d) {
		printf("%d\n", C(a, a + b));
		return 0;
	}
	int ans = 0;
	for (int i = 0; i <= a - c; ++i)
		for (int j = 0; j <= b - d; ++j)
			ans = (ans + 1ll * C(i, i + j) * C(d - 1, a + d - c - i - 1) % Mod * C(c - 1, b + c  - d  - j - 1) % Mod) % Mod;
	ans = 1ll * ans * C(c, c + d) % Mod;
	printf("%d\n", ans);
	return 0;
}