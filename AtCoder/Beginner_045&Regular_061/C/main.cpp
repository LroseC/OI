#include <cctype>
#include <cstdio>
#include <cstring>

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

using LL = long long;

LL ans;
int n, dep = 1;
char str[110];
long long num[110];

void dfs(int i, int lim)
{
	if (i > lim) {
		for (int i = 1; i <= dep; ++i)
			ans += num[i];
		return;
	}
	num[dep] = num[dep] * 10 + str[i] - '0';
	dfs(i + 1, lim);
	num[dep] /= 10;
	num[++dep] = str[i] - '0';
	dfs(i + 1, lim);
	--dep;
}

int main(void)
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	num[1] = str[1] - '0';
	dfs(2, n);
	printf("%lld\n", ans);
	return 0;
}