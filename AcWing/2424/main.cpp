#include <ctime>
#include <random>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;
const int N = 55;

int n, m;
PII a[N];
int ans = 0;
random_device srd;
mt19937 rd(srd());

int rand(int l, int r)
{
	return (int)(1.0 * rd() / UINT_MAX * (r - l) + 0.5) + l;
}
inline int calc(void)
{
	int res = 0;
	for (int i = 0; i < m; ++i) {
		res += a[i].first + a[i].second;
		if (i < n) {
			if (a[i].first == 10)
				res += a[i + 1].first + a[i + 1].second;
			else if (a[i].first + a[i].second == 10)
				res += a[i + 1].first;
		}
	}
	ans = max(ans, res);
	return res;
}
inline void simulate_anneal(void)
{
	for (double t = 1e4; t >= 1e-4; t *= 0.99) {
		int x = calc();
		int l = rand(0, m - 1), r = rand(0, m - 1);
		swap(a[l], a[r]);
		if (n + (a[n - 1].first == 10) == m) {
			int y = calc();
			int delta = y - x;
			if (exp(1.0 * delta / t) < 1.0 * rd() / UINT_MAX) swap(a[l], a[r]);
		}
		else swap(a[l], a[r]);
	}
}

int main(void)
{
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
	if (a[n - 1].first == 10) m = n + 1, cin >> a[n].first >> a[n].second;
	else m = n;
	while (1.0 * clock() / CLOCKS_PER_SEC < 0.8) simulate_anneal();
	printf("%d\n", ans);
	return 0;
}