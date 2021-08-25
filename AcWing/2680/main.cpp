#include <cmath>
#include <cstdio>
#include <random>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 30, M = 10;

int n, m;
int w[N];
int s[M];
random_device srd;
mt19937 rd(srd());
double ans = 1e12;

inline int rand(int l, int r)
{
	return (1.0 * rd() / UINT_MAX * (r - l) + 0.5) + l;
}

double calc(void)
{
	memset(s, 0, sizeof s);
	for (int i = 0; i < n; ++i) {
		int k = 0;
		for (int j = 1; j < m; ++j)
			if (s[j] < s[k]) k = j;
		s[k] += w[i];
	}
	double sum = 0;
	for (int i = 0; i < m; ++i) sum += s[i];
	double avg = sum / m;
	double res = 0;
	for (int i = 0; i < m; ++i)
		res += (avg - s[i]) * (avg - s[i]);
	res = sqrt(res / m);
	ans = min(ans, res);
	return res;
}
void simulate_anneal(void)
{
	shuffle(w, w + n, rd);
	for (double t = 1e4; t >= 1e-4; t *= 0.99) {
		double x = calc();
		int l = rand(0, n - 1), r = rand(0, n - 1);
		swap(w[l], w[r]);
		double y = calc();
		double delta = y - x;
		if (exp(-delta / t) < 1.0 * rd() / UINT_MAX) swap(w[l], w[r]);
	}
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
	while (1.0 * clock() / CLOCKS_PER_SEC < 0.8) simulate_anneal();
	printf("%.2lf\n", ans);
	return 0;
}