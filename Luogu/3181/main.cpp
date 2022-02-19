#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 4e5 + 10;
using LL = long long;

int n, m;
int x[N], y[N], c[N], sa[N], rk[N], height[N];
char s1[N], s2[N];
char str[N];
int stk[N];

void buildSA(void)
{
	m = 200;
	for (int i = 0; i <= m; ++i) c[i] = 0;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++num] = sa[i] - k;

		for (int i = 0; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i];

		swap(x, y);
		num = 1, x[sa[1]] = 1;
		for (int i = 2; i <= n; ++i) {
			int a = sa[i] + k <= n ? y[sa[i] + k] : 0;
			int b = sa[i - 1] + k <= n ? y[sa[i - 1] + k] : 0;
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && a == b) ? num : ++num;
		}
		if (num == n) break;
		m = num;
	}

	for (int i = 1; i <= n; ++i) rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if (k) --k;
		int j = sa[rk[i] - 1];
		while (i + k <= n && j + k <= n && str[i + k] == str[j + k])
			++k;
		height[rk[i]] = k;
	}
}

LL calc(void)
{
	LL res = 0, tmp = 0;
	buildSA();
	int top = 0;
	for (int i = 1; i <= n; ++i) {
		while (top && height[i] <= height[stk[top]]) {
			tmp -= (stk[top] - stk[top - 1]) * height[stk[top]];
			--top;
		}
		stk[++top] = i;
		tmp += (stk[top] - stk[top - 1]) * height[stk[top]];
		res += tmp;
	}
	return res;
}

int main(void)
{
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	n = 0;
	for (int i = 1; s1[i]; ++i)
		str[++n] = s1[i];
	str[++n];
	for (int i = 1; s2[i]; ++i)
		str[++n] = s2[i];
	LL res = calc();

	n = 0;
	for (int i = 1; s1[i]; ++i)
		str[++n] = s1[i];
	res -= calc();

	n = 0;
	for (int i = 1; s2[i]; ++i)
		str[++n] = s2[i];
	res -= calc();
	printf("%lld\n", res);
	return 0;
}
