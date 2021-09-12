#include <set>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
inline int lowbit(int x) { return x & -x; }
inline LL read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n;
LL m;
int q[N];
int a[N];
LL f[N];
multiset<LL> S;

/*
状态表示：f[i] 表示所有对前 i 个数进行划分的方案的集合
性质：最小值
状态计算：f[i] = min { for(int j = g[i]; j < i; ++j) f[j] + max(a[j + 1 ~ i]) }
考虑对这个式子进行优化
注意到一个性质：只有当 f[j] = max(a[j ~ i]) 时，才能取到最优
所以我们进行单调队列优化 维护一个单调递减的符合该性质的序列
并用 STL set 来求出当前最优解
*/

void remove(LL x)
{
	auto it = S.find(x);
	S.erase(it);
}

int main(void)
{
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (a[i] > m) {
			puts("-1");
			return 0;
		}
	}

	int hh = 0, tt = 0;
	LL sum = 0;
	for (int i = 1, j = 0; i <= n; ++i) {
		sum += a[i];
		while (sum > m) sum -= a[++j];
		while (hh <= tt && q[hh] <= j) {
			if (hh < tt) remove(f[q[hh]] + a[q[hh + 1]]);
			++hh;
		}
		int tail = tt;
		while (hh <= tt && a[q[tt]] <= a[i]) {
			if (tt != tail) remove(f[q[tt]] + a[q[tt + 1]]);
			--tt;
		}
		if (hh <= tt && tt != tail) remove(f[q[tt]] + a[q[tt + 1]]);
		q[++tt] = i;
		if (hh < tt) S.insert(f[q[tt - 1]] + a[q[tt]]);

		f[i] = f[j] + a[q[hh]];
		if (S.size()) f[i] = min(f[i], *S.begin());
	}
	printf("%lld\n", f[n]);
	return 0;
}