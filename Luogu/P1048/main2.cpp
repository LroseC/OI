#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

const int N = 1010;

int n, m;
int f[N];

int main(void)
{
	m = read(), n = read();
	for (int i = 0; i < n; ++i) {
		int t = read(), v = read();
		for (int j = m; j >= t; --j)
			f[j] = max(f[j], f[j - t] + v);
	}
	printf("%d\n", f[m]);
}