#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} IO;

const int N = 1e5 + 10;
const double eps = 1e-6;

int n;
int minx = INT_MAX, maxx = INT_MIN;
int a[N], b[N], f[N][2];
double barr[N], g[N][2];

bool dparr(void)
{
	for (int i = 1; i <= n; ++i) {
		g[i][0] = g[i - 1][1];
		g[i][1] = max(g[i - 1][0], g[i - 1][1]) + barr[i];
	}
	return max(g[n][0], g[n][1]) >= eps;
}
bool dpmid(void)
{
	for (int i = 1; i <= n; ++i) {
		f[i][0] = f[i - 1][1];
		f[i][1] = max(f[i - 1][0], f[i - 1][1]) + b[i];
	}
	return max(f[n][0], f[n][1]) >= 1;
}

bool checkarr(double x)
{
	for (int i = 1; i <= n; ++i)
		barr[i] = a[i] - x;
	return dparr();	double l = minx, r = maxx;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (checkarr(mid)) l = mid;
		else r = mid;
	}
	return l;
}

double calcarr(void)
{
	double l = minx, r = maxx;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (checkarr(mid)) l = mid;
		else r = mid;
	}
	return l;
}
bool checkmid(int x)
{
	for (int i = 1; i <= n; ++i)
		b[i] = a[i] >= x ? 1 : -1;
	return dpmid();
}
int calcmid(void)
{
	int l = minx, r = maxx;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (checkmid(mid)) l = mid;
		else r = mid - 1;
	}
	return l;
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n;
	for (int i = 1; i <= n; ++i) {
		IO >> a[i];
		minx = min(minx, a[i]);
		maxx = max(maxx, a[i]);
	}
	printf("%lf\n%d\n", calcarr(), calcmid());
	return 0;
}
