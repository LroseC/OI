#include <cctype>
#include <cstdio>

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

const int mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int n, a, c;

int main(void)
{
	read >> n >> a >> c;
	int res = 0;
	for (int i = 0; i <= n; ++i)
		res = Mod(res + (1ll * i * a / c) % mod);
	printf("%d\n", res);
	return 0;
}
