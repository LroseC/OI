#include <cstdio>

using namespace std;

#define reg register
#define ll long long
const int N = 1e5 + 10;

namespace Splay
{
	int rt, idx;
	int fa[N], ch[N][2], val[N], size[N], cnt[N];
	void maintain(int x)
	{
		size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
	}
	bool get(int x)
	{
		return x == ch[fa[x]][1];
	}
	void clear(int x)
	{
		fa[x] = ch[x][0] = ch[x][1] = val[x] = size[x] = cnt[x] = 0;
	}
	void rotate(int x)
	{
		int y = fa[x], z = fa[y], chk = get(x);
		if (z) ch[z][get(y)] = x;
		ch[y][chk] = ch[x][chk ^ 1];
		if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
		ch[x][chk ^ 1] = y;
		fa[y] = x, fa[x] = z;
		maintain(y), maintain(x);
	}
	void splay(int x)
	{
		for (int f = fa[x]; f = fa[x], f; rotate(x)) {
			printf("x::%d,f::%d,get(x)::%d,get(f)::%d\n", x, f, get(x), get(f));
			if (fa[f]) rotate(get(x) == get(f) ? f : x);
		}
		rt = x;
	}
	void insert(int v)
	{
		if (!rt) {
			val[++idx] = v;
			++cnt[idx];
			rt = idx;
			maintain(rt);
			return;
		}
		int now = rt, f = 0;
		while (1) {
			if (val[now] == v) {
				++cnt[now];
				maintain(now);
				maintain(f);
				splay(now);
				break;
			}
			f = now;
			now = ch[now][val[now] < v];
			if (!now) {
				val[++idx] = v;
				++cnt[idx];
				fa[idx] = f;
				ch[f][val[f] < v] = idx;
				maintain(idx);
				maintain(f);
				splay(idx);
				break;
			}
		}
	}
	void Print(int now, int dep)
	{
		if (!now) return;
		printf("now = %d,dep = %d\n", now, dep);
		Print(ch[now][0], dep + 1);
		Print(ch[now][1], dep + 1);
	}
};

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		if (x == 1) {
			int v;
			scanf("%d", &v);
			Splay::insert(v);
		}
		if (x == 2) {
			int v;
			scanf("%d", &v);
			Splay::splay(v);
		}
		Splay::Print(Splay::rt, 1);
		putchar('\n');
	}
	return 0;
}
