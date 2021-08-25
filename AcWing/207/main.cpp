#include <cmath>
#include <cstdio>
#include <random>
#include <cstring>

using namespace std;

const int N = 20;

int n;
double ans[N];
double d[N][N];
double delta[N];
double dist[N];

void calc(void)
{
	double avg = 0;
	for (int i = 0; i <= n; ++i) {
		delta[i] = 0;
		dist[i] = 0;
		for (int j = 0; j < n; ++j)
			dist[i] += (d[i][j] - ans[j]) * (d[i][j] - ans[j]);
		dist[i] = sqrt(dist[i]);
		avg += dist[i] / (n + 1);
	}
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j < n; ++j)
			delta[j] += (dist[i] - avg) * (d[i][j] - ans[j]) / avg;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j < n; ++j) {
			scanf("%lf", &d[i][j]);
			ans[j] += d[i][j] / (n + 1);
		}
	for (double t = 1e4; t >= 1e-6; t *= 0.99995) {
		calc();
		for (int i = 0; i < n; ++i) ans[i] += t * delta[i];
	}
	for (int i = 0; i < n; ++i) printf("%.3lf ", ans[i]);
	return 0;
}