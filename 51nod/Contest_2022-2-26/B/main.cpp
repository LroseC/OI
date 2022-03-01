#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 310;

int n;
int c[N];
int f[N][N];

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> c[i];
	memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= n; ++i)
		f[i][i] = 1;
	for (int len = 2; len <= n; ++len)
		for (int l = 1, r = l + len - 1; r <= n; ++l, ++r)
			for (int mid = l; mid < r; ++mid)
				f[l][r] = min(f[l][r], f[l][mid] + f[mid + 1][r] - (c[l] == c[r]));
	printf("%d\n", f[1][n]);
	return 0;
}
