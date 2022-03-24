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

int n;
i64 X[N], Y[N], a[N], b[N];
i64 f[N];
int stk[N], top;

long double slope(int a, int b) { return (long double)(Y[a] - Y[b]) / (long double)(X[a] - X[b]); }

int main(void)
{
//	freopen("traffic.in", "r", stdin);
//	freopen("traffic.out", "w", stdout);
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> X[i];
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	for (int i = 1; i <= n; ++i)
		read >> b[i];
	Y[1] = a[1];
	stk[++top] = 1;
	for (int i = 2; i <= n; ++i) {
		int l = 1, r = top;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (slope(stk[mid - 1], stk[mid]) <= b[i])
				l = mid;
			else
				r = mid - 1;
		}
		f[i] = Y[stk[l]] - 1ll * b[i] * X[stk[l]] + b[i] * X[i];
		Y[i] = f[i] + a[i];
		while (top > 1 && slope(stk[top], i) < slope(stk[top - 1], stk[top]))
			--top;
		stk[++top] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
