#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int r, c, n;
vector<int> xn, yn;
int x[N], y[N];

int main(void)
{
	scanf("%d%d%d", &r, &c, &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &x[i], &y[i]);
		xn.push_back(x[i]);
		yn.push_back(y[i]);
	}
	sort(xn.begin(), xn.end());
	sort(yn.begin(), yn.end());
	xn.erase(unique(xn.begin(), xn.end()), xn.end());
	yn.erase(unique(yn.begin(), yn.end()), yn.end());
	for (int i = 1; i <= n; ++i)
		printf("%ld %ld\n", lower_bound(xn.begin(), xn.end(), x[i]) - xn.begin() + 1, lower_bound(yn.begin(), yn.end(), y[i]) - yn.begin() + 1);

	return 0;
}
