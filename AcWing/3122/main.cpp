#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 5e5 + 10;
const double pi = 3.141592653589793238462643383;

struct Complex
{
	double x, y;
	Complex operator+(const Complex &b) const
	{
		return {x + b.x, y + b.y};
	}
	Complex operator-(const Complex &b) const
	{
		return {x - b.x, y - b.y};
	}
	Complex operator*(const Complex &b) const
	{
		return {x * b.x - y * b.y, x * b.y + y * b.x};
	}
}a[N], b[N];

int n, m;
int tot, bit;
int rev[N];

void fft(Complex a[], int inv)
{
	for (int i = 0; i < tot; ++i)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	for (int mid = 1; mid < tot; mid <<= 1)
		for (int i = 0; i < tot; i += mid * 2) {
			Complex w1 = {cos(pi / mid), inv * sin(pi / mid)};
			Complex wnow = {1, 0};
			for (int j = 0; j < mid; ++j, wnow = wnow * w1) {
				auto x = a[i + j], y = a[i + j + mid];
				a[i + j] = x + wnow * y, a[i + j + mid] = x - wnow * y;
			}
		}
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; ++i) scanf("%lf", &a[i].x);
	for (int i = 0; i <= m; ++i) scanf("%lf", &b[i].x);
	while (1 << bit < n + m + 1) ++bit;
	tot = 1 << bit;
	for (int i = 0; i < tot; ++i)
		rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
	fft(a, 1), fft(b, 1);
	for (int i = 0; i < n + m + 1; ++i) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 0; i < n + m + 1; ++i) {
		printf("%d ", (int)(a[i].x / tot + 0.5));
	}
	return 0;
}