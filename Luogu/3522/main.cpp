#include <cctype>
#include <cstdio>
#include <climits>
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
} io;

const int N = 1e6 + 10, M = 20;

int n;
int lg2[N];
int maxlow[N][M], up[N];

inline int getmax(int l, int r)
{
	int t = lg2[r - l + 1];
	return max(maxlow[l][t], maxlow[r - (1 << t) + 1][t]);
}

int main(void)
{
	io >> n;

	lg2[1] = 0;
	for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;

	for (int i = 1; i <= n; ++i) {
		io >> maxlow[i][0] >> up[i];
	}
	for (int j = 1; j < M; ++j)
		for (int i = 1; i <= n; ++i) {
			int tmp = i + (1 << j - 1);
			maxlow[i][j] = max(maxlow[i][j - 1], tmp <= n ? maxlow[tmp][j - 1] : INT_MIN);
		}
	int ans = 0;
	for (int l = 1, r = 1; l <= n; ++l) {
		while (r < n && up[r + 1] >= getmax(l, r + 1)) ++r;
		ans = max(ans, r - l + 1);
	}
	printf("%d\n", ans);
	return 0;
}