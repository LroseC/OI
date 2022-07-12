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
	std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	double res = 0;
	for (int i = 1; i <= n; ++i) {
		int rightBound = std::min(i - 1, n - i);
		int L = 0, R = rightBound;
		while (L < R) {
			int mid = L + R + 1 >> 1;
			if (calcMax(i, mid - 1) < calcMax(i, mid)) L = mid;
			else R = mid - 1;
		}
		res = std::max(res, calcMax(i, L));
		L = 0, R = rightBound;
		while (L < R) {
			int mid = L + R + 1 >> 1;
			if (calcMin(i, mid - 1) < calcMin(i, mid)) L = mid;
			else R = mid - 1;
		}
		res = std::max(res, calcMin(i, L));
	}
	for (int l = 1, r = 2; r <= n; ++l, ++r) {
		int rightBound = std::min(l - 1, r - n);
		int L = 0, R = rightBound;
		while (L < R) {
			int mid = L + R + 1 >> 1;
			if (calcMax(l, r, mid - 1) < calcMax(l, r, mid)) L = mid;
			else R = mid - 1;
		}
		res = std::max(res, calcMax(l, r, L));
		L = 0, R = rightBound;
		while (L < R) {
			int mid = L + R + 1 >> 1;
			if (calcMin(l, r, mid - 1) < calcMin(l, r, mid)) L = mid;
			else R = mid - 1;
		}
		res = std::max(res, calcMin(l, r, L));
	}
	printf("%.8lf\n", res);
	return 0;
}
