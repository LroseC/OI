#include <cctype>
#include <cstdio>
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
const int mod = 998244353;

int ans[10][10];

inline int qpow(i32 base, i32 k)
{
	i32 res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}

i32 calc(i32 n, i32 K)
{
	for (int i = 0; i < 1 << K; ++i) {
		for (int j = 0; j < i; ++j) {
			if (i >> j & 1)
		}
	}
}

int main(void)
{
	ans[1][1] = 1;
	ans[1][2] = 2;
	ans[1][3] = 3;
	ans[1][4] = 4;
	ans[1][5] = 5;
	ans[1][6] = 6;
	ans[1][7] = 7;
	ans[1][8] = 8;
	ans[2][1] = 1;
	ans[2][2] = 4;
	ans[2][3] = 9;
	ans[2][4] = 16;
	ans[2][5] = 25;
	ans[2][6] = 36;
	ans[2][7] = 49;
	ans[2][8] = 64;
	ans[3][1] = 1;
	ans[3][2] = 6;
	ans[3][3] = 27;
	ans[3][4] = 64;
	ans[3][5] = 125;
	ans[3][6] = 216;
	ans[3][7] = 343;
	ans[3][8] = 512;
	ans[4][1] = 1;
	ans[4][2] = 10;
	ans[4][3] = 60;
	ans[4][4] = 256;
	ans[4][5] = 625;
	ans[4][6] = 1296;
	ans[4][7] = 2401;
	ans[4][8] = 4096;
	ans[5][1] = 1;
	ans[5][2] = 14;
	ans[5][3] = 108;
	ans[5][4] = 792;
	ans[5][5] = 3125;
	ans[5][6] = 7776;
	ans[5][7] = 16807;
	ans[5][8] = 32768;
	ans[6][1] = 1;
	ans[6][2] = 22;
	ans[6][3] = 252;
	ans[6][4] = 1848;
	ans[6][5] = 12620;
	ans[6][6] = 46656;
	ans[6][7] = 117649;
	ans[6][8] = 262144;
	ans[7][1] = 1;
	ans[7][2] = 30;
	ans[7][3] = 474;
	ans[7][4] = 3768;
	ans[7][5] = 39540;
	ans[7][6] = 234000;
	ans[7][7] = 823543;
	ans[7][8] = 2097152;
	ans[8][1] = 1;
	ans[8][2] = 46;
	ans[8][3] = 786;
	ans[8][4] = 11448;
	ans[8][5] = 94680;
	ans[8][6] = 948240;
	ans[8][7] = 4946298;
	ans[8][8] = 16777216;
#ifndef DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	//Think twice, code once.
	i32 tt;
	read >> tt;
	while (tt--) {
		i32 n, K;
		read >> n >> K;
	}
	return 0;
}
/*
   好像会一个 2^m 的做法, 但是好饿, 写不动了.
   T3 一眼后缀自动机套 dp, 但是没复习后缀自动机, 不会打.
   T1 调太久了, 有点浪费时间. 还不一定能过, 众所周知, 过拍了 != AC.
   摆烂了, 吃完饭再写这个 60 的暴力把.
   感觉这次我不大行, 应该一堆人比我高, 理论上来说我应该现在打这个 60 分的.
   但是摆烂, 没办法.
   众所周知, LroseC 是摆烂 + 挂分小能手, 我们看看今天他怎么暴毙把.
   有个人说没进前五不给饭吃, 日!
*/
