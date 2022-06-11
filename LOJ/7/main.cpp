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

int main(void)
{
	i64 res = 0;
	for (int i = 1; i <= 3e6; ++i) {
		static i64 x; read >> x;;
		res ^= x;
	}
	printf("%lld\n", res);
	return 0;
}
