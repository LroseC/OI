#include <vector>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>

using namespace std;

template<typename Int>inline void read(Int &res)
{
	res = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) { res = res * 10 + (ch ^ '0'); ch = getchar(); }
}
template<typename Int>inline void write(Int x)
{
	static char buf[20];
	int p = -1;
	while (x) { buf[++p] = x % 10 ^ '0'; x /= 10; }
	while (p >= 0) { putchar(buf[p]); --p; }
}

int n;
vector<int> stick;

bool dfs(int len, int x)
{
}

int main(void)
{
	read(n);
	for (int i = 1; i <= n; ++i) {
		int x; read(x);
		if (x <= 50) stick.emplace_back(x);
	}
	sort(stick.begin(), stick.end(), greater<int>());
	int len = stick[0];
	while (!dfs(len, 0)) ++len;
	write(len); putchar('\n');
	return 0;
}