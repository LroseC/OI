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

int n;
int a[100];

void work(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	int res = 0;
	for (int i = n - 1; i >= 1; --i) {
		if (a[i + 1] == 0) {
			puts("-1");
			return;
		}
		while (a[i] >= a[i + 1])
			a[i] /= 2, ++res;
	}
	printf("%d\n", res);
}

int main(void)
{
	int T; read >> T;
	while (T--) work();
	return 0;
}
