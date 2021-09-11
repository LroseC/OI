//这题是一个 CDQ 分治，然而我似乎忘记怎么写了
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
inline int lowbit(int x) { return x & -x; }

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

struct Query
{
	int op, x, y, z, v, id, f;
};

bool cmpx(const Query &a, const Query &b)
{
	if (a.x == b.x) return a.op < b.op;
	return a.x < b.x;
}
bool cmpy(const Query &a, const Query &b)
{
	return a.y < b.y;
}

const int N = 2e5 + 10;
const int M = 5e5 + 10;

int sz, n;
int idx, anscnt;
Query q[N * 4];
Query tmp[N * 4];
LL ans[N];
LL tr[M];
int stk[N * 4];

void Print(Query x)
{
	printf("x=%d,y=%d,z=%d,v=%d,id=%d,op=%d,f=%d\n", x.x, x.y, x.z, x.v,x.id, x.op, x.f);
}

void Add(int k, int val)
{
	for (int i = k; i < M; i += lowbit(i)) tr[i] += val;
}
LL Ask(int k)
{
	LL res = 0;
	for (int i = k; i; i -= lowbit(i)) res += tr[i];
	return res;
}

void Solve(int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;
	Solve(l, mid);
	Solve(mid + 1, r);
	int i = l, j = mid + 1, t = l;
	int top = 0;
	while (i <= mid && j <= r) {
		while (i <= mid && q[i].y <= q[j].y) {
			if (q[i].op == 1) {
				stk[++top] = i;
				Add(q[i].z, q[i].v);
			}
			tmp[t++] = q[i++];
		}
		while (j <= r && q[i].y > q[j].y) {
			if (q[j].op == 2) {
				ans[q[j].id] += 1ll * q[j].f * Ask(q[j].z);
			}
			tmp[t++] = q[j++];
		}
	}
	while (i <= mid) tmp[t++] = q[i++];
	while (j <= r) {
		if (q[j].op == 2) {
			ans[q[j].id] += 1ll * q[j].f * Ask(q[j].z);
		}
		tmp[t++] = q[j++];
	}
	while (top) Add(q[stk[top]].z, -q[stk[top]].v), --top;
	for (int i = l; i <= r; ++i) q[i] = tmp[i];
}


int main(void)
{
	sz = read(), n = read();
	for (int i = 1; i <= n; ++i) {
		int op = read();
		if (op == 1) {
			++idx;
			q[idx].x = read();
			q[idx].y = read();
			q[idx].z = i;
			q[idx].v = read();
			q[idx].op = op;
		}
		else {
			++anscnt;
			int x1 = read(), y1 = read(), x2 = read(), y2 = read();
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);

			++idx;
			q[idx].f = 1;
			q[idx].x = x2;
			q[idx].y = y2;
			q[idx].z = i;
			q[idx].id = anscnt;
			q[idx].op = op;
			
			++idx;
			q[idx].f = 1;
			q[idx].x = x1 - 1;
			q[idx].y = y1 - 1;
			q[idx].z = i;
			q[idx].id = anscnt;
			q[idx].op = op;
			
			++idx;
			q[idx].f = -1;
			q[idx].x = x1 - 1;
			q[idx].y = y2;
			q[idx].z = i;
			q[idx].id = anscnt;
			q[idx].op = op;

			++idx;
			q[idx].f = -1;
			q[idx].x = x2;
			q[idx].y = y1 - 1;
			q[idx].z = i;
			q[idx].id = anscnt;
			q[idx].op = op;
		}
	}
	sort(q + 1, q + 1 + idx, cmpx);
	Solve(1, idx);
	for (int i = 1; i <= anscnt; ++i) printf("%lld\n", ans[i]);
	return 0;
}