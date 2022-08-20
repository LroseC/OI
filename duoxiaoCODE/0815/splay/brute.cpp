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
const int N = 1e6 + 10;

struct node
{
	i32 ch[2], fa;
};

i32 n;
i64 res[N];
node tr[N], back[N];

i32 getch(i32 x)
{ return x == tr[tr[x].fa].ch[1]; }
void rotate(i32 x)
{
	i32 y = tr[x].fa;
	i32 z = tr[y].fa;
	i32 op = getch(x);
	i32 opy = getch(y);
	tr[y].ch[op] = tr[x].ch[op ^ 1];
	tr[tr[x].ch[op ^ 1]].fa = y;
	tr[x].ch[op ^ 1] = y;
	tr[y].fa = x;
	tr[x].fa = z;
	if (z) tr[z].ch[opy] = x;
}
void splay(i32 x)
{
	while (tr[x].fa) {
		if (tr[tr[x].fa].fa == 0) {
			rotate(x);
		}
		else if (getch(x) == getch(tr[x].fa)) {
			rotate(tr[x].fa);
			rotate(x);
		}
		else {
			rotate(x);
			rotate(x);
		}
	}
}
void getRes(i32 u, i32 dep)
{
	if (tr[u].ch[0])
		getRes(tr[u].ch[0], dep + 1);
	if (tr[u].ch[1])
		getRes(tr[u].ch[1], dep + 1);
	res[u] += dep;
}

int main(void)
{
#ifndef DEBUG
	freopen("splay.in", "r", stdin);
	freopen("splay.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> tr[i].ch[0] >> tr[i].ch[1];
		if (tr[i].ch[0]) tr[tr[i].ch[0]].fa = i;
		if (tr[i].ch[1]) tr[tr[i].ch[1]].fa = i;
	}
	for (int i = 1; i <= n; ++i) {
		back[i] = tr[i];
	}
	for (int i = 1; i <= n; ++i) {
		splay(i);
		getRes(i, 0);
		for (int j = 1; j <= n; ++j) {
			tr[j] = back[j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%lld\n", res[i]);
	}
	return 0;
}
