#include <cstdio>

using namespace std;

const int N = 1e5 + 10;

namespace splay
{
	int root, idx;
	int ch[N][2], fa[N], cnt[N], size[N], val[N];
	void Print(void);
	void maintain(int x)
	{
		size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
	}
	void clear(int x)
	{
		ch[x][0] = ch[x][1] = fa[x] = cnt[x] = size[x] = 0;
	}
	bool get(int x)
	{
		return ch[fa[x]][1] == x;
	}
	void rotate(int x)
	{
		int y = fa[x], z = fa[y];
		int chx = get(x);
		ch[y][chx] = ch[x][chx ^ 1];
		if (ch[x][chx ^ 1]) fa[ch[x][chx ^ 1]] = y;
		ch[x][chx ^ 1] = y;
		fa[y] = x;
		fa[x] = z;
		if (z) ch[z][y == ch[z][1]] = x;
		maintain(x);
		maintain(y);
	}
	void splay(int x)
	{
		for (int f = fa[x]; f; f = fa[x]) {
			if (fa[f]) rotate(get(x) == get(f) ? f : x);
			rotate(x);
		}
		root = x;
	}
	void insert(int v)
	{
		if (!root) {
			val[++idx] = v;
			root = idx;
			size[idx] = cnt[idx] = 1;
			return;
		}
		int p = root, f = fa[p];
		while (p) {
			if (val[p] == v) {
				++cnt[p];
				maintain(p);
				maintain(f);
				splay(p);
				return;
			}
			f = p;
			p = val[p] > v ? ch[p][0] : ch[p][1];
		}
		p = ++idx;
		fa[p] = f;
		ch[f][val[f] > v ? 0 : 1] = p;
		val[p] = v;
		++cnt[p];
		maintain(p);
		maintain(f);
		splay(p);
	}
	int byval(int k)
	{
		int tmp = 0, p = root;
		while (p) {
//			printf("%d,%d?\n", val[p], tmp);
			if (val[p] == k) {
				tmp += size[ch[p][0]] + 1;
				splay(p);
//				printf("%d:%d;\n", tmp, size[ch[p][0]]);
				return tmp;
			}
			if (k > val[p]) {
				tmp += size[ch[p][0]] + cnt[p];
				p = ch[p][1];
			}
			else p = ch[p][0];
		}
	}
	int byrank(int k)
	{
		int tmp = 0, p = root;
		while (p) {
			if (ch[p][0] && tmp + size[ch[p][0]] >= k)
				p = ch[p][0];
			else if (ch[p][1] && tmp + size[ch[p][0]] + cnt[p] < k) {
				tmp += size[ch[p][0]] + cnt[p];
				p = ch[p][1];
			}
			else {
				splay(p);
				return val[p];
			}
		}
	}
	int pre()
	{
		int p = ch[root][0];
		while (ch[p][1]) p = ch[p][1];
		splay(p);
		return p;
	}
	int nex()
	{
		int p = ch[root][1];
		while (ch[p][0]) p = ch[p][0];
		splay(p);
		return p;
	}
	void remove(int k)
	{
		byval(k);
		int p = root;
		--cnt[p];
		maintain(p);
		if (cnt[p]) {
			splay(p);
			maintain(p);
			return;
		}
		if (!ch[root][0] && !ch[root][1]) {
			clear(root);
			root = 0;
			return;
		}
		if (!ch[root][0]) {
			root = ch[root][1];
			clear(fa[root]);
			fa[root] = 0;
			return;
		}
		if (!ch[root][1]) {
			root = ch[root][0];
			clear(fa[root]);
			fa[root] = 0;
			return;
		}
		int l = ch[root][0], r = ch[root][1];
		clear(root);
		root = l;
		fa[l] = 0;
		p = l;
		while (ch[p][1]) p = ch[p][1];
		splay(p);
		ch[p][1] = r;
		fa[r] = p;
		maintain(p);
	}
	void DFS(int dep, int &tim, int p)
	{
		if (!p) return;
		DFS(dep + 1, tim, ch[p][0]);
		printf("dep=%d,tim=%d,p=%d,cnt=%d,ls=%d,rs=%d\n", dep, tim, val[p], cnt[p], size[ch[p][0]], size[ch[p][1]]);
		++tim;
		DFS(dep + 1, tim, ch[p][1]);
	}
	void Print(void)
	{
		int time = 0;
		DFS(1, time, root);
	}
}

using namespace splay;

int n;

int main()
{
	scanf("%d", &n);
	int opt, x;
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &opt, &x);
//		puts("???");
//		Print();
//		puts("!!!");
		switch(opt) {
			case 1:
				insert(x);
				break;
			case 2:
				remove(x);
				break;
			case 3:
				printf("%d\n", byval(x));
				break;
			case 4:
				printf("%d\n", byrank(x));
				break;
			case 5:
				insert(x);
				printf("%d\n", val[pre()]);
				remove(x);
				break;
			case 6:
				insert(x);
				printf("%d\n", val[nex()]);
				remove(x);
				break;
		}
	}
	return 0;
}
