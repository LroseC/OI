#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} io;

const int N = 1e5 + 10, M = 5e5 + 10;

int m;
char op[100];
double b[N], k[N]; int tot;
int tag[M << 2];

double calc(int i, int x) { return k[i] * (x - 1) + b[i]; }
void change(int id, int u = 1, int l = 1, int r = 5e5 + 5)
{
	if (l == r) {
		if (calc(tag[u], l) < calc(id, l)) tag[u] = id;
		return;
	}
	if (!tag[u]) tag[u] = id;
	else {
		int mid = l + r >> 1;
		double y1 = calc(tag[u], mid), y2 = calc(id, mid);
		if (k[tag[u]] < k[id]) {
			if (y1 < y2) {
				change(tag[u], u << 1, l, mid);
				tag[u] = id;
			}
			else change(id, u << 1 | 1, mid + 1, r);
		}
		else if (k[tag[u]] > k[id]) {
			if (y1 < y2) {
				change(tag[u], u << 1 | 1, mid + 1, r);
				tag[u] = id;
			}
			else change(id, u << 1, l, mid);
		}
		else if (b[id] > b[tag[u]]) tag[u] = id;
	}
}
double query(int x, int u = 1, int l = 0, int r = M - 1)
{
	if (l == r) return calc(tag[u], x);
	int mid = l + r >> 1;
	double res = calc(tag[u], x);
	if (x <= mid) res = max(res, query(x, u << 1, l, mid));
	else res = max(res, query(x, u << 1 | 1, mid + 1, r));
	return res;
}

int main(void)
{
	io >> m;
	while (m--) {
		scanf("%s", op + 1);
		if (op[1] == 'Q') {
			int x; io >> x;
			if (tot == 0) printf("0\n");
			else printf("%d\n", (int)query(x) / 100);
		}
		else {
			++tot;
			scanf("%lf%lf", &b[tot], &k[tot]);
			change(tot);
		}
	}
	return 0;
}