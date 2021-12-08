#include <set>
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

int n, m, w;
int A[N], nex[N];
set<int> S[N];
int tr[N << 2];

void maintain(int u)
{
	tr[u] = min(tr[u << 1], tr[u << 1 | 1]);
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u] = nex[l];
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void change(int x, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u] = nex[l];
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) change(x, u << 1, l, mid);
	else change(x, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) return tr[u];
	int mid = l + r >> 1;
	int res = n + 1;
	if (L <= mid) res = min(res, query(L, R, u << 1, l, mid));
	if (R > mid) res = min(res, query(L, R, u << 1 | 1, mid + 1, r));
	return res;
}
bool Q(int l, int r)
{
	int res = query(l, r);
	if (res <= r) return 1;
	return 0;
}

int main(void)
{
	io >> n >> m >> w;
	for (int i = 1; i <= n; ++i) {
		io >> A[i];
		int id = min(A[i], w - A[i]);
		S[id].insert(i);
	}
	for (int i = 1; i <= n; ++i) {
		int id = min(A[i], w - A[i]);
		auto it = S[id].upper_bound(i);
		if (it == S[id].end()) nex[i] = n + 1;
		else nex[i] = A[i] == A[*it] ? n + 1 : *it;
	}
	// for (int i = 1; i <= n; ++i) printf("%d ", nex[i]);
	// puts("");
	build();
	int op, x, y;
	int anscnt = 0;
	while (m--) {
		io >> op >> x >> y;
		if (op == 1) {
			int id = min(A[x], w - A[x]);
			auto it = S[id].lower_bound(x);
			if (it != S[id].begin()) {
				auto jt = it; ++jt;
				--it;
				if (jt == S[id].end()) nex[*it] = n + 1;
				else nex[*it] = A[*it] == A[*jt] ? n + 1 : *jt;
				change(*it);
			}
			S[id].erase(x);
			A[x] = y;
			id = min(A[x], w - A[x]);
			S[id].insert(x);
			it = S[id].lower_bound(x);
			if (it != S[id].begin()) {
				--it;
				nex[*it] = A[*it] == A[x] ? n + 1 : x;
				change(*it);
			}
			it = S[id].upper_bound(x);
			if (it == S[id].end()) nex[x] = n + 1;
			else nex[x] = A[x] == A[*it] ? n + 1 : *it;
			change(x);
		}
		else {
			x ^= anscnt; y ^= anscnt;
			bool tmp = Q(x, y);
			anscnt += tmp;
			puts(tmp ? "Yes" : "No");
		}
	}
	return 0;
}