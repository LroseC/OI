#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int n, m;
int sz[(int)1e5 + 10];
int fa[(int)1e5 + 10];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int u, int v) { if (sz[u] > sz[v]) swap(u, v); fa[u] = v; }

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		sz[i] = 1;
	}
	while (m--) {
		int op = read(), u = read(), v = read();
		u = find(u), v = find(v);
		if (op == 1) merge(u, v);
		else puts(u == v ? "Y" : "N");
	}
	return 0;
}