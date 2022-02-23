#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 310;
using LL = long long;

int n, W;
int w[N], t[N];
LL x[N], f[1010];

bool check(int res)
{
	for (int i = 1; i <= n; ++i) {
		x[i] = 1000 * t[i] - 1ll * res * w[i];
	}
	memset(f, 0xcf, sizeof f);
	f[0] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = W; j >= 0; --j) {
			int to = min(W, j + w[i]);
			f[to] = max(f[to], f[j] + x[i]);
		}
	return f[W] >= 0;
}

int main(void)
{
	read >> n >> W;
	for (int i = 1; i <= n; ++i)
		read >> w[i] >> t[i];
	int l = 0, r = 1e9;
	check(1000);
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
