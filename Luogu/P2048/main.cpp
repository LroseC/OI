#include <queue>
#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 1e6 + 10, LG = 20;

struct node
{
	int pos, l, r;
	i64 val;

	node(void) {}
	node(int _p, int _l, int _r, i64 _v) { pos = _p, l = _l, r = _r, val = _v; }
	bool operator<(const node &other) const { return val < other.val; }
};

int n, K, L, R;
i64 sum[N];
int lg2[N];
int st[N][LG];

void build(void)
{
	lg2[1] = 0;
	for (int i = 2; i <= n; ++i)
		lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; i <= n; ++i)
		st[i][0] = i;
	for (int k = 1; k < LG; ++k)
		for (int i = 1; i + (1 << k - 1) <= n; ++i) {
			int l = st[i][k - 1], r = st[i + (1 << k - 1)][k - 1];
			st[i][k] = sum[l] > sum[r] ? l : r;
		}
}
int query(int l, int r)
{
	int t = lg2[r - l + 1];
	int le = st[l][t], ri = st[r - (1 << t) + 1][t];
	return sum[le] > sum[ri] ? le : ri;
}

int main(void)
{
	read >> n >> K >> L >> R;
	for (int i = 1; i <= n; ++i) {
		read >> sum[i];
		sum[i] += sum[i - 1];
	}
	build();
	std::priority_queue<node> heap;
	for (int i = 1; i <= n; ++i) {
		int left = L + i - 1, right = std::min(n, R + i - 1);
		if (left <= right)
			heap.emplace(i, left, right, sum[query(left, right)] - sum[i - 1]);
	}
	i64 res = 0;
	for (int i = 1; i <= K; ++i) {
		auto t = heap.top(); heap.pop();
		int pos = t.pos, l = t.l, r = t.r;
		int posR = query(l, r);
		res += sum[posR] - sum[pos - 1];
		if (l <= posR - 1)
			heap.emplace(pos, l, posR - 1, sum[query(l, posR - 1)] - sum[pos - 1]);
		if (posR + 1 <= r)
			heap.emplace(pos, posR + 1, r, sum[query(posR + 1, r)] - sum[pos - 1]);
	}
	printf("%lld\n", res);
	return 0;
}
