#include <cctype>
#include <cstdio>

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

/*
   考虑 DP:
   f[i] 表示把前 i 个物品放入若干容器中的最小花费.
   则有 f[i] = min(j = 0; j < i) f[j] + (sum[i] - sum[j] + i - j - L - 1) ^ 2
   总复杂度 O(N^2)
*/

const int N = 5e4 + 10;
using LL = long long;

int n, L;
LL S[N], f[N];
int q[N];

inline LL sq(LL a) { return a * a; }
inline LL X(int i) { return S[i]; }
inline LL Y(int i) { return f[i] + sq(S[i] + L); }
inline long double slope(int a, int b)
{
	return (long double)(Y(a) - Y(b)) / (X(a) - X(b));
}
int main(void)
{
	read >> n >> L; ++L;
	for (int i = 1; i <= n; ++i) {
		read >> S[i];
		S[i] += S[i - 1] + 1;
	}
	int hh = 1, tt = 0;
	q[++tt] = 0;
	for (int i = 1; i <= n; ++i) {
		while (hh < tt && slope(q[hh], q[hh + 1]) <= 2 * S[i])
			++hh;
		int t = q[hh];
		f[i] = f[t] + sq(S[i] - S[t] - L);
		while (hh < tt && slope(q[tt - 1], q[tt]) >= slope(q[tt - 1], i))
			--tt;
		q[++tt] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
