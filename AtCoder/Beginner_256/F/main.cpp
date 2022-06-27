#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

struct line
{
	int len, f[4];
	int& operator[](int x) { return f[x]; }
};

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	return 0;
}
