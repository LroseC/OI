#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

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
} read;

const int N = 3e5 + 10;
using ull = unsigned long long;
struct Rain
{
	int l, r, v;
	Rain(void) { l = r = v = 0; }
	Rain(int _l, int _r, int _v) : l(_l), r(_r), v(_v) {}
};

int n, m, K;
int ans[N];
int q[N], qt[N];
int needed[N], belong[N];
vector<int> country[N];
vector<Rain> rain;

ull tr[N];
inline int lowbit(int x) { return x & -x; }
void _add(int x, int v)
{
	for (int i = x; i < N; i += lowbit(i))
		tr[i] += v;
}
ull query(int x)
{
	ull res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
void add(int L, int R, int val)
{
	if (L <= R) {
		_add(L, val);
		_add(R + 1, -val);
	}
	else {
		_add(L, val);
		_add(1, val);
		_add(R + 1, -val);
	}
}
void calc(int L, int R, int l, int r)
{
	if (R < L) return;
	if (l == r) {
		for (int i = L; i <= R; ++i)
			ans[q[i]] = l;
		return;
	}
	int mid = l + r >> 1;
	for (int i = l; i <= mid; ++i)
		add(rain[i].l, rain[i].r, rain[i].v);
	int left = L, right = R;
	for (int i = L; i <= R; ++i) {
		int id = q[i];
		ull tmp = 0;
		for (int v : country[id])
			tmp += query(v);
		if (needed[id] <= tmp)
			qt[left++] = id;
		else
			qt[right--] = id, needed[id] -= tmp;
	}
	for (int i = L; i <= R; ++i)
		q[i] = qt[i];
	for (int i = l; i <= mid; ++i)
		add(rain[i].l, rain[i].r, -rain[i].v);
	calc(L, right, l, mid);
	calc(left, R, mid + 1, r);
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		read >> belong[i];
		country[belong[i]].emplace_back(i);
	}
	for (int i = 1; i <= n; ++i)
		read >> needed[i];
	read >> K;
	rain.emplace_back(0, 0, 0);
	for (int i = 1; i <= K; ++i) {
		int l, r, v; read >> l >> r >> v;
		rain.emplace_back(l, r, v);
	}
	for (int i = 1; i <= n; ++i)
		q[i] = i;
	calc(1, n, 1, K + 1);
	for (int i = 1; i <= n; ++i) {
		if (ans[i] == K + 1) puts("NIE");
		else printf("%d\n", ans[i]);
	}
	return 0;
}
