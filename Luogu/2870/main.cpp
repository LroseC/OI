#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int n, m;
char str[N];
char ans[N];
int sa[N], rk[N], x[N], y[N], c[N];

void BuildSa(void)
{
	m = 200;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k)
				y[++num] = sa[i] - k;

		for (int i = 1; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

		swap(x, y);
		num = 0;
		for (int i = 1; i <= n; ++i)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;

		if (n == num) break;
		m = num;
	}
	for (int i = 1; i <= n; ++i)
		rk[sa[i]] = i;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		do str[i] = getchar();
		while (isspace(str[i]));
	}
	str[n + 1] = 1;
	for (int i = n, j = 2; i >= 1; --i, ++j)
		str[n + j] = str[i];
	n = n * 2 + 1;
	BuildSa();
	n = (n - 1) / 2;
	int i = 1, j = n;
	int idx = 0;
	while (i < j) {
		if (str[i] < str[j])
			ans[++idx] = str[i++];
		else if (str[i] > str[j])
			ans[++idx] = str[j--];
		else {
			if (rk[i] < rk[2 * n - j + 2])
				ans[++idx] = str[i++];
			else
				ans[++idx] = str[j--];
		}
	}
	ans[++idx] = str[i];
	for (int i = 1; i <= idx; ++i) {
		putchar(ans[i]);
		if (i % 80 == 0) putchar('\n');
	}
	puts("");
	return 0;
}
