#include <cstdio>
#include <algorithm>

using namespace std;

#define reg register
#define ll long long
const int N = 1e5 + 10;

int n;
double a[N], b[N];

inline double min(double a, double b)
{
	return a < b ? a : b;
}
inline double max(double a, double b)
{
	return a > b ? a : b;
}

struct greater
{
	bool operator()(double a, double b)
	{
		return a > b;
	}
};

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lf%lf", &a[i], &b[i]);
	sort(a + 1, a + 1 + n, greater());
	sort(b + 1, b + 1 + n, greater());
	int i = 0, j = 0;
	double ans = 0;
	double suma = 0, sumb = 0;
	while (i != n && j != n) {
		if (suma > sumb || i == n) {
			sumb += b[++j];
		}
		else {
			suma += a[++i];
		}
		ans = max(ans, min(suma, sumb) - i - j);
	}
	printf("%.4lf\n", ans);
	return 0;
}
