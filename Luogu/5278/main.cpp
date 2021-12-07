#include <map>
#include <set>
#include <cctype>
#include <cstdio>
#include <climits>
#include <assert.h>
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
}io;

const int N = 3e5 + 10;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int n, m;
int A[N];
map< int, set<int> > M;

struct node
{
	int l, r;
	int _gcd, _min, _max;
	int _left, _right;
	node operator+(const node &other) const
	{
		node res;
		res.l = l; res.r = other.r;
		res._min = min(_min, other._min);
		res._max = max(_max, other._max);
		res._left = max(_left, other._left);
		res._right = min(_right, other._right);
		res._gcd = gcd(_gcd, other._gcd);
		res._gcd = gcd(res._gcd, abs(A[other.l] - A[r]));
		return res;
	}
}tr[N << 2];

void build(int u = 1, int l = 1, int r = n)
{
	tr[u].l = l, tr[u].r = r;
	if (l == r) {
		tr[u]._gcd = 0;
		tr[u]._min = tr[u]._max = A[l];
		auto &_S = M[A[l]];
		auto it = _S.lower_bound(l);
		if (it == _S.begin())
			tr[u]._left = INT_MIN;
		else {
			--it;
			tr[u]._left = *it;
		}
		it = _S.upper_bound(l);
		if (it == _S.end())
			tr[u]._right = INT_MAX;
		else
			tr[u]._right = *it;
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void change(int x, int y, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u]._gcd = 0;
		tr[u]._min = tr[u]._max = A[l];
		auto &_S = M[A[l]];
		auto it = _S.lower_bound(l);
		if (it == _S.begin())
			tr[u]._left = INT_MIN;
		else {
			--it;
			tr[u]._left = *it;
		}
		it = _S.upper_bound(l);
		if (it == _S.end())
			tr[u]._right = INT_MAX;
		else
			tr[u]._right = *it;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) change(x, y, u << 1, l, mid);
	else change(x, y, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
node query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		return tr[u];
	}
	int mid = l + r >> 1;
	if (L <= mid && R > mid) return query(L, R, u << 1, l, mid) + query(L, R, u << 1 | 1, mid + 1, r);
	else if (L <= mid) return query(L, R, u << 1, l, mid);
	else return query(L, R, u << 1, mid + 1, r);
}
bool Q(int l, int r, int k)
{
	if (l == r) return 1;
	node res = query(l, r);
	if (res._max != 1ll * k * (r - l) + res._min) return 0;
	if (res._gcd != k) return 0;
	if (l <= res._left || res._right <= r) return 0;
	return 1;
}

int main(void)
{
	io >> n >> m;
	for (int i = 1; i <= n; ++i) {
		io >> A[i];
		M[A[i]].insert(i);
	}
	build();
	int anscnt = 0;
	while (m--) {
		int op;
		io >> op;
		if (op == 1) {
			int x, y; io >> x >> y;
			x ^= anscnt;
			y ^= anscnt;
			M[A[x]].erase(x);
			A[x] = y;
			M[A[x]].insert(x);
			change(x, y);
		}
		else {
			int l, r, k; io >> l >> r >> k;
			l ^= anscnt;
			r ^= anscnt;
			k ^= anscnt;
			bool tmp = Q(l, r, k);
			puts(tmp ? "Yes" : "No");
			anscnt += tmp;
		}
	}
	return 0;
}