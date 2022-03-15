#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;

template<typename INT> INT min(INT a, INT b, INT c)
{
	return min(a, min(b, c));
}
inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n;
int f[N][3];
vector<int> a;

int main(void)
{
	n = read();
	a.resize(n);
	for (int i = 0; i < n; ++i) a[i] = read();
	// for (int i = 0; i < n; ++i) printf("%d ", a[i]);
	// puts("");
	memset(f, INF, 4 * 3 * n);
	f[0][a[0] + 1] = 0;
	for (int i = 1; i < n; ++i) {
		for (int j = -1; j <= a[i]; ++j)
			f[i][a[i] + 1] = min(f[i][a[i] + 1], f[i - 1][j + 1]);
		if (f[i - 1][0] != INF)
			for (int j = a[i] - 1, v = 1; j >= -1; --j, ++v)
				f[i][j + 1] = min(f[i][j + 1], f[i - 1][0] + v);
		if (f[i - 1][2] != INF)
			f[i][2] = min(f[i][2], f[i - 1][2] + 1 - a[i]);
	}
	// for (int i = 0; i < n; ++i)
		// for (int j = 0; j < 3; ++j)
			// printf("f[%d][%d] = %d\n", i, j - 1, f[i][j]);
	int ans = min(f[n - 1][1], f[n - 1][0], f[n - 1][2]);
	if (ans >= INF) puts("BRAK");
	else printf("%d\n", ans);
	return 0;
}