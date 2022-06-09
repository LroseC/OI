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

i64 C[110][110];

int main(void)
{
	int n;
	read >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= i; ++j)
			C[i][j] = j == 0 ? 1 : C[i - 1][j - 1] + C[i - 1][j];
	for (int i = 0; i < n; ++i, puts(""))
		for (int j = 0; j <= i; ++j)
			printf("%lld ", C[i][j]);
	return 0;
}
