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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i32 = int;
using i64 = long long;
using PII = std::pair<i32, i32>;

int main(void)
{
#ifndef DEBUG
	freopen("splay.in", "r", stdin);
	freopen("splay.out", "w", stdout);
#endif
	//Think twice, code once.
	return 0;
}
