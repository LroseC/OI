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

int n, a, d;

long long calc(void)
{
	long long res = n;
	while ((d & 1) == 0) {
		d >>= 1;
		res += res - 1;
	}
	return res - n;
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		read >> n >> a >> d;
		printf("%lld\n", calc());
	}
	return 0;
}
