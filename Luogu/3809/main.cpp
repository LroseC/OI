#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int n, m;
char str[N];
int sa[N], rk[N];
int c[N], x[N], y[N];

void get_sa(void)
{
	m = 133;
	for (int i = 1; i <= n; ++i)
		++c[x[i] = str[i]];
	for (int i = 2; i <= m; ++i)
		c[i] += c[i - 1];
	for (int i = n; i >= 1; --i)
		sa[c[x[i]]--] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i)

int main(void)
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	get_sa();
	for (int i = 1; i <= n; ++i)
		printf("%d ", sa[i]);
	puts("");
	return 0;
}
