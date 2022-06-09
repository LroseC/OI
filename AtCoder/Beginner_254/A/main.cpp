#include <cctype>
#include <cstdio>
#include <cstring>

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
	char str[100];
	scanf("%s", str + 1);
	int len = std::strlen(str + 1);
	for (int i = len - 1; i <= len; ++i)
		putchar(str[i]);
	putchar('\n');
	return 0;
}
