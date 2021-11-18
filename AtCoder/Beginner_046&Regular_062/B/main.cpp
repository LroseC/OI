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
} io;

int n, k;
int main(void)
{
	io >> n >> k;
	int ans = k;
	for (int i = 2; i <= n; ++i) ans = ans * (k - 1);
	printf("%d\n", ans);
	return 0;
}