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

const int N = 5e5 + 10;

struct Query
{
	int id, l, r;
	bool operator<(const Query &other) const
	{
		return r < other.r;
	}
	Query(void) { id = l = r = 0; }
};

int n, m;
int A[N];
int ans[N];
Query q[N];
int pos[21];
int base[21];

void insert(int id, int x)
{
	for (int k = 20; k >= 0; --k)
		if (x >> k & 1) {
			if (!base[k]) {
				pos[k] = id;
				base[k] = x;
				return;
			}
			if (id > pos[k])
				swap(pos[k], id), swap(base[k], x);
			x ^= base[k];
		}
}
int query(int leftlim)
{
	int res = 0;
	for (int k = 20; k >= 0; --k)
		if (!(res >> k & 1) && base[k] && pos[k] >= leftlim) {
			res ^= base[k];
		}
	return res;
}

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) io >> A[i];
	io >> m;
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		io >> q[i].l >> q[i].r;
	}
	sort(q + 1, q + 1 + m);
	int right = 0;
	for (int i = 1; i <= m; ++i) {
		while (right < q[i].r) ++right, insert(right, A[right]);
		ans[q[i].id] = query(q[i].l);
	}
	for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}
