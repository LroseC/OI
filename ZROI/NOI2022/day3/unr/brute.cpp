#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 5e5 + 10;

int n;
double a[N], sum[N];

double calcMax(int pos, int len)
{
	return std::fabs((sum[n] - sum[n - len] + sum[pos] - sum[pos - 1 - len]) / (1 + len * 2) - a[pos]);
}
double calcMin(int pos, int len)
{
	return std::fabs((sum[len] + sum[pos + len] - sum[pos - 1]) / (1 + len * 2) - a[pos]);
}
double calcMax(int l, int r, int len)
{
	double mid = (a[l] + a[r]) / 2;
	return std::fabs((sum[n] - sum[n - len] + sum[r] - sum[l - 1 - len]) / (2 + len * 2) - mid);
}
double calcMin(int l, int r, int len)
{
	double mid = (a[l] + a[r]) / 2;
	return std::fabs((sum[len] + sum[r + len] - sum[l - 1]) / (2 + len * 2) - mid);
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	double res = 0;
	for (int i = 1; i <= n; ++i) {
		vint t, dec;
		for (int len = 0; i - len >= 1 && i + len <= n; ++len) {
//			res = std::max(res, std::fabs((sum[n] - sum[n - len] + sum[i] - sum[i - 1 - len]) / (1 + len * 2) - a[i]));
//			res = std::max(res, std::fabs((sum[len] + sum[i + len] - sum[i - 1]) / (1 + len * 2) - a[i]));
			res = std::max(res, calcMax(i, len));
			res = std::max(res, calcMin(i, len));
		}
	}
	for (int l = 1, r = 2; r <= n; ++l, ++r) {
		double mid = (a[l] + a[r]) / 2;
		for (int len = 0; l - len >= 1 && r + len <= n; ++len) {
//			res = std::max(res, std::fabs((sum[n] - sum[n - len] + sum[r] - sum[l - 1 - len]) / (2 + len * 2) - mid));
//			res = std::max(res, std::fabs((sum[len] + sum[r + len] - sum[l - 1]) / (2 + len * 2) - mid));
			res = std::max(res, calcMax(l, r, len));
			res = std::max(res, calcMin(l, r, len));
		}
	}
	printf("%.8lf\n", res);
	return 0;
}
