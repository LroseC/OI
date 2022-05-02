#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

double f[110];
double g[110][110];

int main(void)
{
	int TYPE, n;
	read >> TYPE >> n;
	if (TYPE == 1) {
		f[1] = 0;
		for (int i = 2; i <= n; ++i) {
			f[i] = f[i - 1] + 2 + (f[i - 1] / (i - 1));
		}
		printf("%lf\n", f[n] / n);
	}
	else {
		for (int i = 1; i <= n; ++i)
			g[i][0] = 1;
		for (int i = 2; i <= n; ++i)
			for (int j = 1; j <= i - 1; ++j)
				for (int k = 1; k < n; ++k) {
					g[i][k] += (g[j][k - 1] + g[i - j][k - 1] - g[j][k - 1] * g[i - j][k - 1]) / (i - 1);
				}
		double res = 0;
		for (int i = n - 1; i >= 1; --i)
			res += g[n][i];
		printf("%.6lf\n", res);
	}
	return 0;
}
