#include <cctype>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i32 = int32_t;
using i64 = int64_t;
using PII = std::pair<i32, i32>;
const int N = 2e6 + 10;

i64 gcd(i64 a, i64 b)
{ return b ? gcd(b, a % b) : a; }
i64 lcm(i64 a, i64 b)
{ return a / gcd(a, b) * b; }
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y)
{
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	i64 d = exgcd(b, a % b, y, x);
	y -= (a / b) * x;
	return d;
}

struct fangcheng
{
	i64 p, a;
	fangcheng(void) {}
	fangcheng(i64 _p, i64 _a) { p = _p, a = _a; }
	friend fangcheng operator+(const fangcheng &f1, const fangcheng &f2)
	{
		fangcheng res;
		res.p = lcm(f1.p, f2.p);
		i64 x, y;
		i64 del = std::abs(f1.a - f2.a);
		i64 d = exgcd(f1.p, f2.p, x, y);
		if (del % d) {
			puts("-1");
			exit(0);
		}
		x = x * (del / d);
		y = y * (del / d);
		res.a = ((f1.a + x * f1.p) % res.p + res.p) % res.p;
		return res;
	}
};

i32 n, top;
i32 vis[N], to[N];
char s[N], T[N];
char str1[N << 1], str2[N];
i32 nex[N << 1];
fangcheng res(1, 0);

void insert(i64 p, i64 a)
{
	res = res + fangcheng(p, a);
}
void solve(void)
{
	i64 loop = top;
	for (int i = 1, j = 0; i < top; ++i) {
		while (j && str2[i] != str2[j]) j = nex[j - 1];
		if (i < top && j < top && str2[i] == str2[j]) ++j;
		nex[i] = j;
	}
	for (int i = 0; i < top; ++i) {
		str1[i + top] = str1[i];
	}
	i32 pos = -1, p2;
	for (int i = 0, j = 0; i < (top << 1); ++i) {
		while (j && (j == top || str1[i] != str2[j])) j = nex[j - 1];
		if (i < (top << 1) && j < top && str1[i] == str2[j]) ++j;
		if (j == top) {
			if (pos != -1) {
				p2 = i - top + 1;
				loop = p2 - pos;
				break;
			}
			pos = i - top + 1;
		}
	}
//	for (int i = 0; i < (top << 1); ++i)
//		putchar(str1[i]);
//	putchar('\n');
//	for (int i = 0; i < top; ++i)
//		putchar(str2[i]);
//	putchar('\n');
	if (pos == -1) {
		puts("-1");
		exit(0);
	}
	insert(loop, pos);
}
void dfs(i32 u)
{
	vis[u] = 1;
	str1[top] = s[u];
	str2[top] = T[u];
	top += 1;
	if (vis[to[u]]) {
		solve();
	}
	else {
		dfs(to[u]);
	}
}

int main(void)
{
#ifndef DEBUG
	freopen("manipulation.in", "r", stdin);
	freopen("manipulation.out", "w", stdout);
#endif
	//Think twice, code once.
	scanf("%s", s);
	scanf("%s", T);
	n = strlen(s);
	for (int i = 1; i <= n; ++i) {
		if (i & 1) to[(i + 1) / 2 - 1] = i - 1;
		else to[i / 2 + n / 2 - 1] = i - 1;
	}
	for (int i = 0; i < n; ++i)
		if (!vis[i]) {
			top = 0;
			dfs(i);
		}
	printf("%lld\n", (res.a % res.p + res.p) % res.p);
	return 0;
}
/*
   一眼置换环, 两眼 kmp, 三眼是数学.
   就没了, 比 T1 简单多了.
   堪称近几场最水的题之一.
   会不会时间不够写不出来啊 /ll.
   那我血亏.
   算了不写正解了, 暴力打满吧.
   不行! 我要爆切 T2!
   反正 T1 过拍了, 肉眼也没看出锅.
   过不了 T2 不丢人, 时间不够而已.
   但是分数可能比较难看 /xk
*/
