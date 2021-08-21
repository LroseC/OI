#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 3e5 + 10;
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

int tot, bit;
int rev[N];
int res[N];
char s1[N], s2[N];

void fft(Complex a[], int inv)
{
	for (int i = 0; i < tot; ++i)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	
	for (int mid = 1; mid < tot; mid <<= 1)
		for (int i = 0; i < tot; i += mid << 1) {
			Complex w1 = {cos(pi / mid), inv * sin(pi / mid)};
			Complex wk = {1, 0};
			for (int j = 0; j < mid; ++j, wk = wk * w1) {
				auto x = a[i + j], y = a[i + j + mid];
				a[i + j] = x + wk * y, a[i + j + mid] = x - wk * y;
			}
		}
}

int main(void)
{
	scanf("%s%s", s1, s2);
	int n = strlen(s1), m = strlen(s2);
	--n, --m;
	while (1 << bit < n + m + 1) ++bit;
	tot = 1 << bit;
	for (int i = 0; i < tot; ++i) rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
	for (int i = 0; i <= n; ++i) a[i].x = s1[i] - '0';
	for (int i = 0; i <= m; ++i) b[i].x = s2[i] - '0';
	reverse(a, a + n + 1);
	reverse(b, b + m + 1);
	fft(a, 1), fft(b, 1);
	for (int i = 0; i < tot; ++i) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 0; i < n + m + 1; ++i) res[i] = (int)(a[i].x / tot + 0.5);
	for (int i = 0; i < n + m + 10; ++i) res[i + 1] += res[i] / 10, res[i] %= 10;
	int all = n + m + 10;
	while (all && !res[all]) -- all;
	for (int i = all; i >= 0; --i) printf("%d", res[i]);
	puts("");
	return 0;
}