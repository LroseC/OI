#include <cctype>
#include <cstdio>
#include <algorithm>

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

using i64 = long long;
const int N = 5e5 + 10;

struct Query
{
	int id, x, y;
	bool operator<(const Query &other) const
	{
		return y < other.y;
	}
};

int n, m;
i64 a[N];
i64 sum[N];
Query q[N];
i64 X[N], Y[N], ans[N];
int stk[N], top;

double slope(int a, int b) { return double(Y[a] - Y[b]) / double(X[a] - X[b]); }

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> a[i], sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n; ++i)
		X[i] = a[i], Y[i] = 1ll * a[i] * i - sum[i];
	read >> m;
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		read >> q[i].x >> q[i].y;
	}
	std::sort(q + 1, q + 1 + m);

	int y = 0;
	for (int i = 1; i <= m; ++i) {
		while (y + 1 <= q[i].y) {
			++y;
			while (top > 0 && X[stk[top]] >= X[y])
				--top;
			while (top > 1 && slope(y, stk[top - 1]) < slope(stk[top], stk[top - 1]))
				--top;
			stk[++top] = y;
		}
		int l = 1, r = top;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (slope(stk[mid - 1], stk[mid]) < (q[i].y - q[i].x))
				l = mid;
			else r = mid - 1;
		}
		ans[q[i].id] = X[stk[l]] * (q[i].x - q[i].y) + Y[stk[l]] + sum[q[i].y];
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
