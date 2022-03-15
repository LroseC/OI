#include <cctype>
#include <cstdio>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int f[2];

int main(void)
{
	n = read(), p = read(), q = read();
	for (int i = 1; i <= n; ++i) {
		f[0] = min(f[0] + q, f[1])
	}
}