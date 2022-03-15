#include <cmath>
#include <iostream>

using namespace std;

#define x first
#define y second
typedef pair<double, double> PDD;
const int N = 10;
const double PI = 3.141592653589793238462643383;

int n;
double ans;
double u, d, l, r;
PDD p[N];
bool used[N];
double R[N];
double dis[N][N];

inline double sq(double x) { return x * x; }

void dfs(int x, double S)
{
	if (x > n) {
		ans = max(ans, S);
		return;
	}
	for (int i = 1; i <= n; ++i)
		if (!used[i]) {
			used[i] = 1;
			R[i] = abs(u - p[i].y);
			R[i] = min(R[i], abs(d - p[i].y));
			R[i] = min(R[i], abs(l - p[i].x));
			R[i] = min(R[i], abs(r - p[i].x));
			for (int j = 1; j <= n; ++j)
				if (used[j] && i != j)
					R[i] = min(R[i], dis[i][j] - R[j]);
			if (R[i] < 0) R[i] = 0;
			dfs(x + 1, S + PI * sq(R[i]));
			used[i] = 0;
		}
}

int main(void)
{
	cin >> n;
	double x, y;
	cin >> x >> y;
	u = d = y;
	l = r = x;
	cin >> x >> y;
	u = min(u, y), d = max(d, y);
	l = min(l, x), r = max(r, x);
	for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			dis[i][j] = dis[j][i] = sqrt(sq(p[i].x - p[j].x) + sq(p[i].y - p[j].y));
	dfs(1, 0);
	printf("%.0lf\n", (r - l) * (d - u) - ans);
	return 0;
}