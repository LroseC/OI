#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int n, m;
char str[N];
int x[N], y[N], c[N];
int sa[N], rk[N], height[N];

void get_sa(void);
void get_height(void);

int main(void)
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	m = 122;
	get_sa();
	get_height();
	for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
	puts("");
	for (int j = 1; j <= n; ++j) printf("%d ", height[j]);
	puts("");
}

void get_sa(void)
{
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
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

		swap(x, y);
		x[sa[1]] = 1, num = 1;
		for (int i = 2; i <= n; ++i)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if (num == n) break;
		m = num;
	}
}

void get_height(void)
{
	for (int i = 1; i <= n; ++i) rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if(k) --k;
		int j = sa[rk[i] - 1];
		while (i + k <= n && j + k <= n && str[i + k] == str[j + k]) ++k;
		height[rk[i]] = k;
	}
}