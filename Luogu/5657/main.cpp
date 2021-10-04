#include <cctype>
#include <cstdio>

using namespace std;

typedef unsigned long long ULL;

inline ULL read(void)
{
	ULL res = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res;
}

int n;
ULL k;

void dfs(int n, ULL k)
{
	if (n == 0) {
		putchar(k + '0');
		return;
	}
	if (k >> n & 1) {
		putchar('1');
		dfs(n - 1, (1 << n + 1) - k);
	}
	else {
		dfs(n - 1, k);
		putchar('0');
	}
}

int main(void)
{
	n = read(), k = read();
	dfs(n - 1, k);
}