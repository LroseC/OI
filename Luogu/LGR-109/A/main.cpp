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

inline i64 getSum(i64 a, i64 b)
{ return (a + b) * (b - a + 1) / 2; }
int main(void)
{
	int T; read >> T;
	while (T--) {
		i64 x, y, z;
		read >> x >> y >> z;
		if (z < x) {
			puts("Merry");
			continue;
		}
		i64 tmp = getSum(z - x, z - 1);
		if (tmp + z - x >= y)
			puts("Renko");
		else
			puts("Merry");
	}
	return 0;
}
