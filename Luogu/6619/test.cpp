#include <utility>
#include <cstdio>

using namespace std;

#define reg register
#define ll long long
#define PII pair<int, int>
const int N = 2e6 + 10;


namespace Splay{
	int root, idx;
	int ch[N][2], fa[N], tem[N], val[N][2], sum[N][2];
	void maintain(int x)
	{
		sum[x][0] = val[x][0] + sum[ch[x][0]][0] + sum[ch[x][1]][0];
		sum[x][1] = val[x][1] + sum[ch[x][0]][1] + sum[ch[x][1]][1];
	}
	bool get(int x)
	{
		return x == ch[fa[x]][1];
	}
	void clear(int x)
	{
		ch[x][0] = ch[x][1] = fa[x] = val[x][0] = val[x][1] = sum[x][0] = sum[x][1] = 0;
	}
	void rotate(int x)
	{
		int y = fa[x], z = fa[y];
		int chk = get(x);
		ch[y][chk] = ch[x][chk ^ 1];
		if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
		ch[x][chk ^ 1] = y;
		if (z) ch[z][get(y)] = x;
		fa[y] = x;
		fa[x] = z;
		maintain(y);
		maintain(x);
	}
	void splay(int x)
	{
		for (reg int f = fa[x]; f = fa[x], f; rotate(x))
			if (fa[f]) rotate(get(x) == get(f) ? f : x);
		root = x;
	}
	void insert(int t, int v, int type)
	{
		if (!root) {
			root = ++idx;
			val[idx][type] = v;
			tem[idx] = t;
			maintain(idx);
			return;
		}
		int now = root, f = 0;
		while (1) {
			if (tem[now] == t) {
				val[now][type] += v;
				maintain(now);
				splay(now);
				break;
			}
			f = now, now = ch[now][t > tem[now]];
			if (!now) {
				now = ++idx;
				val[idx][type] = v;
				tem[idx] = t;
				fa[now] = f;
				ch[f][t > tem[f]] = now;
				maintain(idx);
				splay(now);
				break;
			}
		}
	}
	int find(int t)
	{
		int now = root, f = 0;
		while (now) {
			if (t == tem[now]) {
				splay(now);
				return now;
			}
			f = now, now = ch[now][t > tem[now]];
		}
		return -1;
	}
	int pre()
	{
		int now = ch[root][0];
		while (ch[now][1]) now = ch[now][1];
		if (now) splay(now);
		return now;
	}
	int nxt()
	{
		int now = ch[root][1];
		while (ch[now][0]) now = ch[now][0];
		if (now) splay(now);
		return now;
	}
	void remove(int t, int v, int type)
	{
		find(t);
		val[root][type] -= v;
		maintain(root);
		if (!val[root][0] && !val[root][1]) {
			int now = root;
			if (!ch[now][0] && !ch[now][1]) {
				clear(now); root = 0; return;
			}
			if (!ch[now][0]) {
				root = ch[now][1], fa[root] = 0; clear(now); return;
			}
			if (!ch[now][1]) {
				root = ch[now][0], fa[root] = 0; clear(now); return;
			}
			int x = pre();
			fa[ch[now][1]] = x;
			ch[x][1] = ch[now][1];
			clear(now);
			maintain(root);
		}
	}
	PII icebig(void)//ice -> pre
	{
		int ans = -1;
		int now = root, f = 0;
		int psum = 0, nsum = 0;
		puts("icebig");
		while (now) {
			printf("%d, ", now);
			printf("%d,%d!!!\n", psum + val[now][0] + sum[ch[now][0]][0],nsum + val[now][1] + sum[ch[now][1]][1]);
			if (psum + val[now][0] + sum[ch[now][0]][0] >= nsum + val[now][1] + sum[ch[now][1]][1])
				ans = now;
			f = now, now =  ch[now][(psum + val[now][0] + sum[ch[now][0]][0] < nsum + val[now][1] + sum[ch[now][1]][1])];
			int chk = get(now);
			if (!chk) nsum += sum[ch[f][1]][1] + val[f][1];
			else psum += sum[ch[f][0]][0] + val[f][0];
		}
//		putchar('\n');
		if (ans > 0) splay(ans);
//		printf("%d???\n",ans);
		if (sum[ch[ans][1]][1] + val[ans][1]  == 0) return make_pair(-1, -1);
		return make_pair(ans, val[ans][1] + sum[ch[ans][1]][1]);
	}
	PII firebig(void)//fire -> nxt
	{
		int ans = -1;
		int now = root, f = 0;
		int psum = 0, nsum = 0;
//		puts("firebig");
		while (now) {
//			printf("%d, ", now);
//			printf("%d,%d!!!\n", psum + val[now][0] + sum[ch[now][0]][0],nsum + val[now][1] + sum[ch[now][1]][1]);
			if (psum + val[now][0] + sum[ch[now][0]][0] <= nsum + val[now][1] + sum[ch[now][1]][1])
				ans = now;
			f = now, now =  ch[now][(psum + val[now][0] + sum[ch[now][0]][0] < nsum + val[now][1] + sum[ch[now][1]][1])];
			int chk = get(now);
			if (!chk) nsum += sum[ch[f][1]][1] + val[f][1];
			else psum += sum[ch[f][0]][0] + val[f][0];
		}
//		putchar('\n');
//		printf("ans = %d\n", ans);
		if (ans > 0) splay(ans);
		if (sum[ch[ans][0]][0] + val[ans][0] == 0) return make_pair(-1, -1);
		return make_pair(ans, val[ans][0] + sum[ch[ans][0]][0]);
	}
	void Print(int now, int dep)
	{
		if (!now) return;
		printf("now = %d, tem = %d, val1 = %d, val2 = %d, dep = %d\n", now, tem[now], val[now][0], val[now][1], dep);
		Print(ch[now][0], dep + 1);
		Print(ch[now][1], dep + 1);
	}
};

int Q;
int t[N], x[N], y[N];

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

using namespace Splay;
int main()
{
	scanf("%d", &Q);
	reg int type, k;
	for (reg int i = 1; i <= Q; ++i) {
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d%d%d", &t[i], &x[i], &y[i]);
			Splay::insert(x[i], y[i], t[i]);
		}
		else {
			scanf("%d", &k);
			Splay::remove(x[k], y[k], t[k]);
		}
		PII ans;
		PII fb = Splay::firebig(), ib = Splay::icebig();
		int may = Splay::pre();
		if (fb.second <= ib.second || fb.first == -1) ans = ib;
		if (ib.second <= fb.second || ib.first == -1) ans = fb;
		if (~fb.first || ~ib.first)
			printf("%d:%d,%d,%d\n", tem[ib.first], ib.second, tem[fb.first], fb.second);
		else puts("Peace");
		Print(root, 1);
	}
	return 0;
}
