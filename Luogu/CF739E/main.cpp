#include <iostream>

using i64 = long long;
const int N = 2010;
const double eps = 1e-8;

int n, cnta, cntb;
int g[N][N];
double f[N][N], a[N], b[N];

std::pair<double, int> calc(double deltaA)
{
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= cntb; ++j) {
			f[i][j] = f[i - 1][j];
			g[i][j] = g[i - 1][j];
			double t = f[i - 1][j] + a[i] - deltaA;
			if (t > f[i][j]) {
				f[i][j] = t;
				g[i][j] = g[i - 1][j] + 1;
			}
			if (j) {
				double t = f[i - 1][j - 1] + b[i];
				if (t > f[i][j]) {
					f[i][j] = t;
					g[i][j] = g[i - 1][j - 1];
				}
				t = f[i - 1][j - 1] + a[i] + b[i] - a[i] * b[i] - deltaA;
				if (t > f[i][j]) {
					f[i][j] = t;
					g[i][j] = g[i - 1][j - 1] + 1;
				}
			}
		}
	return std::make_pair(f[n][cntb], g[n][cntb]);
}

int main(void)
{
	std::cin >> n >> cnta >> cntb;
	for (int i = 1; i <= n; ++i)
		std::cin >> a[i];
	for (int i = 1; i <= n; ++i)
		std::cin >> b[i];
	double l = 0, r = 1;
	while (r - l > eps) {
		double mid = (r + l) / 2;
		auto t = calc(mid);
		if (t.second < cnta)
			r = mid;
		else if (t.second == cnta) {
			l = r = mid;
			break;
		}
		else
			l = mid;
	}
	auto t = calc(r);
	printf("%lf\n", t.first + l * cnta);
	return 0;
}
