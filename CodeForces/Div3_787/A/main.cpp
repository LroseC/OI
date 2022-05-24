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

using i64 = long long;

int main(void)
{
	int T; read >> T;
	while (T--) {
		int a, b, c, x, y;
		read >> a >> b >> c >> x >> y;
		x -= std::min(x, a);
		y -= std::min(y, b);
		puts(c >= x + y ? "YES" : "NO");
	}
	return 0;
}
