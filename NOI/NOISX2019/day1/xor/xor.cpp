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
using uint = unsigned int;
const int N = 5e5 + 10;

int n, K;
uint sum[N];
int root[N];
int idx, tim[N * 33];
int ch[N * 33][2];

struct node
{
	int pos, l, r, Rpos;
	uint val;

	node(void) {}
	node(int _p, int _l, int _r, int _R)
	{
		pos = _p, l = _l, r = _r, Rpos = _R;
		val = sum[Rpos] ^ sum[pos - 1];
	}
	bool operator<(const node &other) const { return val < other.val; }
};

int insert(int rt, uint x, int dep, int id)
{
	if (dep == -1) {
		int u = ++idx;
		tim[u] = id;
		return u;
	}
	int u = ++idx;
	tim[u] = id;
	ch[u][0] = ch[rt][0];
	ch[u][1] = ch[rt][1];
	int t = x >> dep & 1;
	ch[u][t] = insert(ch[u][t], x, dep - 1, id);
	return u;
}
int query(uint x, int l, int r)
{
	int u = root[r];
	for (int i = 31; i >= 0; --i) {
		int t = x >> i & 1;
		if (ch[u][t ^ 1] && tim[ch[u][t ^ 1]] >= l)
			u = ch[u][t ^ 1];
		else
			u = ch[u][t];
	}
	return tim[u];
}

int main(void)
{
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	read >> n >> K;
	for (int i = 1; i <= n; ++i) {
		read >> sum[i];
		sum[i] ^= sum[i - 1];
		root[i] = insert(root[i - 1], sum[i], 31, i);
	}
	std::priority_queue<node> heap;
	for (int i = 1; i <= n; ++i) {
		int left = i, right = n;
		heap.emplace(i, left, right, query(sum[i - 1], left, right));
	}
	i64 res = 0;
	for (int i = 1; i <= K; ++i) {
		auto t = heap.top(); heap.pop();
		int l = t.l, r = t.r, pos = t.pos, Rpos = t.Rpos;
		res += sum[Rpos] ^ sum[pos - 1];
		if (l <= Rpos - 1)
			heap.emplace(pos, l, Rpos - 1, query(sum[pos - 1], l, Rpos - 1));
		if (Rpos + 1 <= r)
			heap.emplace(pos, Rpos + 1, r, query(sum[pos - 1], Rpos + 1, r));
	}
	printf("%lld\n", res);
	return 0;
}
