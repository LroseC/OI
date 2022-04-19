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
const int N = 4e5 + 10;

int n, x, y;
char str[N << 1];
int val[N];

int main(void)
{
	freopen("bracket.in", "r", stdin);
	freopen("bracket.out", "w", stdout);
	read >> n >> x >> y;
	if (x == 0 && y == 0) {
		puts("0");
		return 0;
	}
	scanf("%s", str + 1);
	bool flag = 1;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		if (i != 1 && val[i] != val[i - 1])
			flag = 0;
	}
	if (flag) {
		i64 res = 0;
		int cnt = 0;
		for (int i = 1; i <= n << 1; ++i) {
			if (str[i] == ')') ++cnt;
			else res += 1ll * cnt * val[1] * (x + y);
		}
		printf("%lld\n", res);
		return 0;
	}
	return 0;
}
