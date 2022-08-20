#include <vector>
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
const int N = 510;

struct node
{
	i32 a, b, c;
	node(void) {}
	node(i32 _a, i32 _b, i32 _c)
	{ a = _a, b = _b, c = _c; }
	bool operator<(const node &other) const
	{ return a > other.a; }
};

i32 n, K;
bool del[N];
i32 a[N], b[N], c[N];
std::vector<i32> nums;

int main(void)
{
#ifndef DEBUG
	freopen("playoffs.in", "r", stdin);
	freopen("playoffs.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> K;
	for (int i = 1; i <= n; ++i) {
		read >> a[i] >> b[i] >> c[i];
	}
	i64 ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (j != i) {
				i32 cnt = 0;
				for (int k = 1; k <= n; ++k) {
					if (k == i || k == j) continue;
					if (c[k] == 0 && a[k] > a[i] && b[k] > b[j])
						cnt += 1;
				}
				std::fill(del + 1, del + 1 + n, 0);
				std::vector<node> female;
				for (int k = 1; k <= n; ++k) {
					if (c[k] == 0) continue;
					if (k == i || k == j) continue;
					if (a[k] > a[i]) {
						female.emplace_back(a[k], k, 0);
					}
					if (b[k] > b[j]) {
						female.emplace_back(b[k], k, 1);
					}
				}
				i64 res = 0;
				if (c[i]) res += a[i];
				if (c[j]) res += b[j];
				i32 rest[2];
				rest[0] = rest[1] = K - 1;
				i32 restTot = 2 * (K - 1) - cnt;
				if (restTot < 0) continue;
				std::sort(female.begin(), female.end());
				for (auto pr : female) {
					if (del[pr.b]) continue;
					if (!rest[pr.c]) continue;
					if (!restTot) break;
					res += pr.a;
					del[pr.b] = 1;
					rest[pr.c] -= 1;
					restTot -= 1;
				}
				ans = std::max(ans, res);
			}
	printf("%lld\n", ans);
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
*/
