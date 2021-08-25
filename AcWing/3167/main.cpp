#include <ctime>
#include <cstdio>
#include <random>
#include <climits>

using namespace std;

typedef pair<double, double> PDD;

const int N = 110;

int n;
double ans = 1e8;
PDD p[N];
random_device srd;
mt19937 rd(srd());

double rand(double l, double r)
{
	return 1.0 * rd() / UINT_MAX * (r - l) + l;
}
double get_dist(PDD a, PDD b)
{
	double dx = a.first - b.first, dy = a.second - b.second;
	return sqrt(dx * dx + dy * dy);
}
double calc(PDD x)
{
	double res = 0;
	for (int i = 1; i <= n; ++i)
		res += get_dist(x, p[i]);
	ans = min(ans, res);
	return res;
}
void simulate_anneal(void)
{
	PDD cur(rand(0, 10000), rand(0, 10000));
	for (int t = 1e4; t >= 1e-4; t *= 0.99) {
		PDD p(rand(cur.first - t, cur.first + t), rand(cur.second - t, cur.second + t));
		double dt = calc(cur) - calc(p);
		if (exp(-dt / t) > rand(0, 1)) cur = p;
	}
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lf%lf", &p[i].first, &p[i].second);
	while (1.0 * clock() / CLOCKS_PER_SEC < 0.8) simulate_anneal();
	printf("%.0lf\n", (int)ans);
	return 0;
}