#include <cctype>
#include <cstdio>

strcut FSI
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

int n, m;

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		read >> w[i];
		scanf("%s%s", str1 + 1, str2 + 1);
	}
	return 0;
}