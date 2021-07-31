# <center>AtCoder Beginner_212 题解</center>

### A. Alloy

​	[题目链接](https://atcoder.jp/contests/abc212/tasks/abc212_a)

##### 题面简述

​	Takahashi 熔化并混合了 $A$ 克黄金， $B$ 克白银。

​	请你判断这是合金还是纯金还是纯银。



##### 题目思路

​	水题，没什么好说的。



##### 代码实现

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int a, b;

int main(void)
{
	cin >> a >> b;
	if (a && b) puts("Alloy");
	else if (a) puts("Gold");
	else if (b) puts("Silver");
	return 0;
}
```

<div style="page-break-after:always"></div>

### B. Weak Password

[题目链接](https://atcoder.jp/contests/abc212/tasks/abc212_b)

##### 题面简述

​	给你一个四位的密码，判断这个密码强度强弱。

​	一个密码强度弱，当且仅当满足以下两个条件之一：

* 四位都一样。

* 对于前三位密码均满足这一位密码的后一位是该位密码的后继。（ 一个一位数 $i$ 的后继是 $i + 1$ ，$9$ 的后继是 $0$ ）



##### 题目思路

​	同水题。



##### 代码实现

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

char str[20];

bool check(void)
{
	for (int i = 1; i <= 4; ++i) str[i] -= '0';
	for (int i = 1; i < 4; ++i)
		if ((str[i] + 1) % 10 != str[i + 1]) return 0;
	return 1;
}

int main(void)
{
	scanf("%s", str + 1);
	if (str[1] == str[2] && str[2] == str[3] && str[3] == str[4])
		puts("Weak");
	else if(check())
		puts("Weak");
	else puts("Strong");

	return 0;
}
```

<div style="page-break-after:always"></div>

### C. Min Difference

[题目链接](https://atcoder.jp/contests/abc212/tasks/abc212_c)

##### 题面简述

​	给你长度为 $n$ 的数组 $A$ ，长度为 $m$ 的数组 $B$ 。

​	求 $\min |A_i - B_j|,i\in[1,n],j\in[1,m]$​ 。​



##### 题目思路

​	这还不够水？



##### 代码实现

```cpp
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n, m;
int a[N], b[N];

int main(void)
{
	scanf("%d%d", &n, &m);
	int ans = INT_MAX;
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int j = 1; j <= m; ++j) scanf("%d", &b[j]);
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	for (int i = 1; i <= n; ++i) {
		int k = lower_bound(b + 1, b + 1 + m, a[i]) - b;
		if (k - 1) ans = min(ans, abs(b[k - 1] - a[i]));
		if (k <= m) ans = min(ans, abs(b[k] - a[i]));
	}
	printf("%d\n", ans);
	return 0;
}
```



<div style="page-break-after:always"></div>

### D. Querying Multiset

[题目链接](https://atcoder.jp/contests/abc212/tasks/abc212_d)

##### 题面简述

​	Takahashi 有很多球，上面都是空白的。他还有一个袋子，一开始是空的。

​	Takahashi 将会做 $Q$​ 次操作，有以下三种 ：

* Type $1$ ：在一个空白的球上写上正整数 $X_i$ 并把它放入袋子中。
* Type $2$ ：把袋子中每一个球上的正整数加上 $Xi$ 。
* Type $3$​ ：选出袋子中写的数最小的球，记录上面的数然后把这个球扔掉。



##### 题目思路

​	还是水题，一眼秒了。

​	不过比前面几题好多了，这题好歹转了几个弯，用了个数据结构。



​	看着像个数据结构，维护最小值，整体加减。

​	直接小根堆，再打个整体懒标记。放入新的正整数前减去当前标记。



##### 代码实现

```cpp
#include <queue>
#include <cstdio>
#include <algorithm>

using namespace std;

#define int long long

int q;
int tag;
priority_queue< int, vector<int>, greater<int> > heap;

signed main(void)
{
	scanf("%lld", &q);
	while (q--) {
		int op, x;
		scanf("%lld", &op);
		if (op == 1) {
			scanf("%lld", &x);
			heap.push(x - tag);
		}
		if (op == 2) {
			scanf("%lld", &x);
			tag += x;
		}
		if (op == 3) {
			printf("%lld\n", heap.top() + tag);
			heap.pop();
		}
	}
	return 0;
}
```



<div style="page-break-after:always"></div>

### E. Safety Journey

[题目链接](https://atcoder.jp/contests/abc212/tasks/abc212_e)

##### 题面简述

​	AcCoder 共和国有 $n$​ 个城市。一开始城市两两间有无向边。

​	后来有 $m$​ 条边无法通行了。

​	问题从 $1$​ 号节点走 $K$ 条边后回到 $1$ 号节点的方案数，对 $998244353$​ 取模。



##### 题目思路

​	和刚刚那几题不是一个难度的。不过还是一眼秒了（我真的不是在吹啊）。

​	看到 $m$ 比较小，而且本身就是删边，那我们考虑减法求贡献。

​	具体地说，设 $f(i,j)$​​ 表示走 $j$​​ 步到 $i$​​ 号节点的方案数，那么
$$
f(i,j)=\sum_{k=1}^n f(k,j-1) - \sum_uf(u,j-1)[u\nrightarrow i]
$$
​	本来 $1$​​ ～ $n$​​ 号节点对 $i$​​​ 号节点都有贡献，现在删去一些边，导致两个点无法相互贡献，故减去。

​	顺便一提，一个点是无法到达自己的，即不能原地停留。

​	最终答案就是 $f(1,k)$​ 。



##### 代码实现

```cpp
#include <vector>
#include <cstdio>

using namespace std;

#define int long long
const int N = 5010;
const int mod = 998244353;

int n, m, day;
vector<int> edge[N];
int f[2][N], tot[2], tmp;

void Work(void)
{
	tmp ^= 1;
	for (int i = 1; i <= n; ++i)
		f[tmp][i] = tot[tmp ^ 1];
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < edge[i].size(); ++j) {
			int v = edge[i][j];
			f[tmp][i] = (f[tmp][i] - f[tmp ^ 1][v]) % mod;
		}
	tot[tmp] = 0;
	for (int i = 1; i <= n; ++i)
		tot[tmp] = (tot[tmp] + f[tmp][i]) % mod;
	return;
}

signed main(void)
{
	scanf("%lld%lld%lld", &n, &m, &day);
	for (int i = 1; i <= n; ++i) edge[i].push_back(i);
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%lld%lld", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	tot[tmp] = 1;
	f[tmp][1] = 1;
	while (day--) Work();

	printf("%lld\n", (f[tmp][1] + mod) % mod);
	
	return 0;
}
```

<div style="page-break-after:always"></div>

### F. Greedy Takahashi

[题目链接](https://atcoder.jp/contests/abc212/tasks/abc212_f)

##### 题面简述

​	不简述了。



##### 题目思路

​	（前面 $5$ 题我写了 $40$ $min$ ，这题我 $40$ $min$ 都没写出来，写到一半发现看错题。。。）

​	显然，当你坐上任何一趟公交车时，你的路线就完全是确定的了。

​	因此，对于任何一班公交车，坐上它之后最终能到达的终点一定就是坐完这趟公交后你会坐上的下一趟公交车的终点。

​	于是就有了做法：先把每个公交车按到达时间从大到小排序，然后依次处理每班公交（保证无后效性），用一个数组记录坐上这班公交后最终会到达的节点编号。



​	然后我没发现这题的提问不是问最终会到达哪里，而是在 $Z_i$ 分钟在哪个节点。

​	原地心态爆炸不打了，不过有一个倍增的想法。

​	参考倍增求 $LCA$ ，这题可以在依次处理坐完每班公交后再坐 $1,2,4,8,\cdots$ ​班公交车后到达的节点。

​	每次倍增处理询问，这样复杂度就很合理（从预处理到询问均为 $O(n\log n)$​​​​）。



##### 代码实现

​	丢一个考场上写一半的代码。

```
```

<div style="page-break-after:always"></div>

## <center>考后感想</center>

​	我太菜了。

​	其实 $F$ 题好多人跳过了，甚至我刚开始做这题的时候当时的$rank$ $2$ , $rank$ $3$ 全都是只有这题没 $A$ 。

​	下次一定看榜打比赛。