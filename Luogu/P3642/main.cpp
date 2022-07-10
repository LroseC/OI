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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
	return 0;
}
/*
f[u][x] means the minimum price to make
distance bitween u and all leafy node in the subtree of u equal to x
f[u][x] =
sum(v is son of u)
	min(all i)
		(f[v][i] + |x - i|)
let g[v][x] = min(all i) (f[v][i] + |x - i|)
*/
