#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;

#define reg register
typedef int LL;
const int N = 1e5 + 10;

inline int read(void)
{
	reg int res = 0, f = 1;
	reg char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		res = res * 10 + (ch ^ '0');
		ch = getchar();
	}
	return f * res;
}
inline void write(LL x)
{
	static char buf[64];
	reg int p = -1;
	while (x) buf[++p] = x % 10 ^ '0', x /= 10;
	for (reg int i = p; i >= 0; --i) putchar(buf[i]);
	putchar('\n');
}

struct Node
{
	int a, s;
	bool operator<(const Node &b) const
	{
		return a > b.a;
	}
}node[N];
int n;
LL sum[N];
int front[N], back[N];

int main(void)
{
	n = read();
	for (reg int i = 0; i < n; ++i) node[i].s = read();
	for (reg int i = 0; i < n; ++i) node[i].a = read();
	sort(node, node + n);
	for (reg int i = 0; i < n; ++i) sum[i] = sum[i - 1 + (i == 0)] + node[i].a;
	for (reg int i = 0; i < n; ++i) front[i] = max(front[i - 1], node[i].s * 2);
	for (reg int i = n - 1; i >= 0; --i) back[i] = max(back[i + 1], node[i].s * 2 + node[i].a);
	for (reg int i = 0; i < n; ++i)
		write(max(sum[i] + front[i], sum[i - 1] + back[i]));
	return 0;
}