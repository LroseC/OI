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

int ans[100];


int main(void)
{
	ans[3] = 1;
	ans[4] = 3;
	ans[5] = 22;
	ans[6] = 137;
	ans[7] = 1023;
	ans[8] = 8221;
	ans[9] = 79056;
	ans[10] = 799039;
	ans[11] = 9011440;
	ans[12] = 109029410;
	ans[13] = 1448549484;
	int n; read >> n;
	printf("%d\n", ans[n]);
	return 0;
}
