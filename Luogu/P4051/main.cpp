#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n, m;
char str[N];

int sa[N], x[N], y[N], c[N];

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
}

int main(void)
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int i = 1; i <= n; ++i)
		str[i + n] = str[i];
	n <<= 1;
	BuildSa();
	for (int i = 1; i <= n; ++i)
		if (sa[i] <= n / 2)
			putchar(str[sa[i] + n / 2 - 1]);
	puts("");
	return 0;
}
