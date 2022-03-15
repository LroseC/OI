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

int n, M, T;
int f[210][210];

int main(void)
{
	n = read(), M =read(), T = read();
	for (int i = 0; i < n; ++i) {
		int m = read(), t = read();
		for (int j = M; j >= m; --j)
			for (int k = T; k >= t; --k)
				f[j][k] = max(f[j][k], f[j - m][k - t] + 1);
	}
	printf("%d\n", f[M][T]);
	return 0;
}