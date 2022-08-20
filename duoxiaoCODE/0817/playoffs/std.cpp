#include <cctype>
#include <cstdio>
#include <cstdint>
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

int main(void)
{
#ifndef DEBUG
	freopen("playoffs.in", "r", stdin);
	freopen("playoffs.out", "w", stdout);
#endif
	//Think twice, code once.
	return 0;
}
/*
   考虑钦定左边集合晋级的最菜的和右边集合晋级的最菜的.
   显然可以贪心, 一个男的如果不是比两边最菜的都强的话, 显然就不让他晋级算了.
   剩下的男的一定是无论丢左边还是丢右边都一样的, 所以只要左右集合加起来留出这么多空位就行了.
   所以只要考虑女的怎么放.(我怀疑我在物化女性！(
   这个大概也可以贪心, 把所有女的拆成两半, 从大到小排序, 选出最大的.
   啊, 好像做完了, 而且好像挺对的!
   复杂度大概是 n^3, 先写个 n^3logn 的.
   甚至比 T1 好写多了? 不过没有 T1 那么一眼.
   过不了第四个大样例????
   我觉得我是对的啊??????
   我的答案更大?????
   怎么回事呢???????
   调完锅之后是错的, 因为第二个不能贪心, 我 nt 了.
   但是好像还是一道经典题, 我回想一下.
   不回想拉!! 直接 n^2 DP !!!!
   拿分要紧!!!!!!
   我趣, DP 是 n^3 的!!!!!
   回归原点/xk
   那就拿假做法骗分!!!!
   正解: n^2 * n^3 DP 优化.
   考虑按 a 先将每个人排序.
   这样就不用钦定左边集合晋级的最菜的了，准确来说是一边枚举一边直接确定.
   啊, 然后就 n^4 了.
   还能考虑去掉一维. 延续那个贪心, 人分为 3 种:
   废物男, 卷王男, 强者女.
   DP 的时候 fw 是不管的, 考虑 f[i][a][b] 表示考虑前 i 个, A, B 分别选了 a, b 个.
   注意到任何一个 DP 方案都可以进行一些调整.
*/
