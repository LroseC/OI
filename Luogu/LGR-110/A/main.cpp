#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 1e6 + 10;

int fib[N];
int sum[N];

int main(void)
{
	fib[1] = fib[2] = 1;
	for (int i = 3; i < N; ++i)
		fib[i] = (fib[i - 1] + fib[i - 2]) % 9;
	for (int i = 1; i < N; ++i)
		sum[i] = (sum[i - 1] + fib[i]) % 9;
	int T; read >> T;
	while (T--) {
		int n; read >> n;
		printf("%d\n", sum[n]);
	}
	return 0;
}
