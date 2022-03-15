#include <cstdio>
#include <iostream>

using namespace std;

const int N = 5010;

int n;
int h[N];
int f[N][N];

bool CanSee(int r, int l, int p)
{
	return (1ll * (h[r] - h[l]) * (r - p) < 1ll * (h[r] - h[p]) * (r - l));
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> h[i];
	
	int ans = 0;
	for (int r = 1; r <= n; ++r) {
		int sum, p = 0;
		ans ^= (f[r][r] = sum = 1);
		for (int l = r - 1; l >= 1; --l) {
			if (!p || CanSee(r, l, p)) {
				sum += min(f[l + 1][p - 1], f[l + 1][p]);
				p = l;
			}
			ans ^= (f[l][r] = (sum + min(f[l][p], f[l][p - 1])));
		}
	}
	printf("%d\n", ans);
	return 0;
}