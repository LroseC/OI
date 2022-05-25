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
const int N = 1e4 + 10;

int n, m;
int w[N];

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> w[i], w[i] *= 2;
	for (int i = 1, u, v, c; i <= m; ++i) {
		read >> u >> v >> c;
		w[u] += c, w[v] += c;
	}
	std::sort(w + 1, w + 1 + n);
	int res = 0;
	for (int i = n; i >= 1; i -= 2)
		res += w[i] - w[i - 1];
	printf("%d\n", res / 2);
	return 0;
}
