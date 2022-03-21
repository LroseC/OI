#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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

int main(void)
{
	int T; read >> T;
	while (T--) {
		int n; read >> n;
		std::vector<int> a(n);
		for (int i = 0; i < n; ++i)
			read >> a[i];
		std::sort(a.begin(), a.end());
		printf("%d\n", a[n - 1] + a[n - 2]);
	}
	return 0;
}
