#include <cctype>
#include <cstdio>
#include <climits>
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

const int N = 5e5 + 10;

int n, m;
struct node
{
	int a, b;
	int alpha, beta;
	int ans;
	node (void)
	{
		b = INT_MAX;
		a = alpha = beta = ans = INT_MIN;
	}
	node operator+(const node &other) const
	{
		node res;
		res.a = max(a, other.a);
		res.b = min(b, other.b);
		res.alpha = max(alpha, other.alpha);
		res.alpha = max(res.alpha, a - other.b);
		res.beta = max(beta, other.beta);
		res.beta = max(res.beta, other.a - b);
		res.ans = max(ans, other.ans);
		res.ans = max(res.ans, alpha + other.a);
		res.ans = max(res.ans, other.beta + a);
		return res;
	}
} tr[N << 2];
int A[N], B[N];

void build(int l = 1, int r = n, int u = 1)
{
	if (l == r) {
		tr[u].a = A[l];
		tr[u].b = B[l];
		return ;
	}
	int mid = l + r >> 1;
	build(l, mid, u << 1);
	build(mid + 1, r, u << 1 | 1);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void changea(int x, int y, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u].a = y;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) changea(x, y, u << 1, l, mid);
	else changea(x, y, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void changeb(int x, int y, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u].b = y;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) changeb(x, y, u << 1, l, mid);
	else changeb(x, y, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
node query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) return tr[u];
	int mid = l + r >> 1;
	if (L <= mid && mid + 1 <= R) return query(L, R, u << 1, l, mid) + query(L, R, u << 1 | 1, mid + 1, r);
	else if (L <= mid) return query(L, R, u << 1, l, mid);
	else return query(L, R, u << 1 | 1, mid + 1, r);
}

int main(void)
{ 
	io >> n >> m;
	for (int i = 1; i <= n; ++i) io >> A[i];
	for (int i = 1; i <= n; ++i) io >> B[i];
	build();
	while (m--) {
		int op, x, y; io >> op >> x >> y;
		if (op == 1)
			changea(x, y);
		if (op == 2)
			changeb(x, y);
		if (op == 3)
			printf("%d\n", query(x, y).ans);
	}
	return 0;
}