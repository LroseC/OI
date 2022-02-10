/*
	lcp(i, j): 排名为 i 的后缀和排名为 j 的后缀的最长公共前缀的长度.
	性质:
		1: lcp(i, j) == lcp(j, i);
		2: lcp(i, i) == strlen(i);
		3: lcp(i, j) == min(lcp(i, k), lcp(k, j)), 其中 i <= k <= j
	性质 1, 2 对于任意字符串数组都成立，正确性显然.
	性质 3 对于任意排序后的字符串数组都成立.

	定义 height[i] = lcp(i - 1, i), h[i] = height[sa[i]];
	h[i] >= h[i - 1] - 1;
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int n, m;
char str[N];
int sa[N], rk[N], height[N], x[N], y[N], c[N];

void BuildSa(void)
{
	m = 200;
	for (int i = 1; i <= m; ++i) c[i] = 0;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		//在这里, y[i] 表示第二关键字排名为 i 的后缀是 y[i].
		for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k)
				y[++num] = sa[i] - k;

		for (int i = 1; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		//与一开始不同, 这里一定要按照第二关键字从大到小枚举.

		swap(x, y);

		num = 0;
		for (int i = 1; i <= n; ++i) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if (num == n) break;
		m = num;
	}


	for (int i = 1; i <= n; ++i)
		rk[sa[i]] = i;

	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if (k) --k;
		int j = sa[rk[i] - 1];
		while (i + k <= n && j + k <= n && str[i + k] == str[j + k])
			++k;
		height[rk[i]] = k;
	}
}

int main(void)
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	BuildSa();
	for (int i = 1; i <= n; ++i)
		printf("%d ", sa[i]);
	puts("");
	for (int i = 1; i <= n; ++i)
		printf("%d ", height[i]);
	puts("");
	return 0;
}
