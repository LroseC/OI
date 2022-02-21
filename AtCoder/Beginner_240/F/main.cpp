#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} IO;

const int N = 2e5 + 10;

int n, m;
int x[N], y[N];
int cnt[110];

LL calc(int x)
{
	return 1ll * x * (x + 1) / 2;
}

int work(void)
{
	IO >> n >> m;
	memset(cnt, 0, sizeof cnt);
	LL res = LLONG_MIN;
	LL sum = 0, tmp = 0;
	for (int i = 1; i <= n; ++i) {
		IO >> x[i] >> y[i];
		if (sum > 0 && sum + (1ll * x[i] * y[i]) <= 0) {
			//我们需要二分找到最后一个 sum 依然大于等于 0 的点.
			int l = 0, r = y[i];
			while (l < r) {
				int mid = l + r + 1 >> 1;
				if (sum + 1ll * mid * x[i] >= 0) l = mid;
				else r = mid - 1;
			}
			//接着求出 C 对应的值
			LL tmp2 = 0;
			for (int i = -4; i <= 4; ++i)
				tmp2 += 1ll * cnt[i + 10] * i * l;
			res = max(res, tmp + tmp2 + calc(l) * x[i]);
		}
		sum += 1ll * x[i] * y[i];
		for (int j = -4; j <= 4; ++j) {
			tmp += 1ll * cnt[j + 10] * j * y[i];
		}
		tmp += calc(y[i]) * x[i];
		cnt[x[i] + 10] += y[i];
	}
	res = max(res, 1ll * x[1]);
	res = max(res, tmp);
	printf("%lld\n", res);
	return 0;
}

int main(void)
{
	int T; IO >> T;
	while (T--)
		work();
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}
/*
   我们考虑寻找数组 A 的极值点.
   由于 B 是 A 的导数, B 的零点数量就是 A 的极值点数量
   又由于 C 是 B 的导数, B 的零点数量小于 A 正负改变点数量.
   A 正负改变点数量显然是 O(n) 的.
   于是我们枚举出所有的极值点, 由于 x 值域范围极小, 我们可以暴力计算出所有答案取 max.
   顺便一提, 我们要求的是极大点, 所以只要 B 从大于 0 到小于等于 0 的零点.
*/
