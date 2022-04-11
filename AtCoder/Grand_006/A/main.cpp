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

int n;
char s[110], t[110];

bool check(int x)
{
	for (int i = 1, j = n - x + 1; i <= x; ++i, ++j) {
		if (s[j] != t[i]) return 0;
	}
	return 1;
}

int main(void)
{
	read >> n;
	scanf("%s%s", s + 1, t + 1);
	for (int i = n; i >= 1; --i)
		if (check(i)) {
			printf("%d\n", n * 2 - i);
			return 0;
		}
	printf("%d\n", n * 2);
	return 0;
}
