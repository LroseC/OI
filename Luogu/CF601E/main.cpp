#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdlib>
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
} IO;

const int p = 1e7 + 19, mod = 1e9 + 7;
const int N = 5000 + 30000 + 10;
using pii = pair<int, int>;

int n, m, K;
pii a[N], b[N]; int idx;
bool q[N];
vector<pii> tr[N << 2];
int f[1010];

void add(int L, int R, int v, int w, int u = 1, int l = 1, int r = m)
{
	if (L <= l && r <= R) {
		tr[u].emplace_back(make_pair(v, w));
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, v, w, u << 1, l, mid);
	if (R > mid) add(L, R, v, w, u << 1 | 1, mid + 1, r);
}
void calc(int u = 1, int l = 1, int r = m)
{
	int g[1010];
	memcpy(g, f, sizeof g);
	for (auto t : tr[u])
		for (int j = K; j >= t.second; --j)
			f[j] = max(f[j], f[j - t.second] + t.first);
	if (l == r) {
		if (q[l]) {
			int res = 0;
			for (int m = 1, tmp = 1; m <= K; ++m, tmp = 1ll * tmp * p % mod)
				res = (res + 1ll * f[m] * tmp % mod) % mod;
			printf("%d\n", res);
		}
	}
	else {
		int mid = l + r >> 1;
		calc(u << 1, l, mid);
		calc(u << 1 | 1, mid + 1, r);
	}
	memcpy(f, g, sizeof f);
}

int main(void)
{
	IO >> n >> K;
	for (int i = 1; i <= n; ++i) {
		IO >> a[i].first >> a[i].second;
		b[i].first = 1;
	}
	IO >> m;
	idx = n;
	for (int i = 1; i <= m; ++i) {
		int op; IO >> op;
		if (op == 1) {
			int v, w; IO >> v >> w;
			++idx;
			a[idx] = make_pair(v, w);
			b[idx].first = i;
		}
		if (op == 2) {
			int x; IO >> x;
			b[x].second = i;
		}
		if (op == 3) {
			q[i] = 1;
		}
	}
	for (int i = 1; i <= idx; ++i) {
		add(b[i].first, b[i].second == 0 ? m : b[i].second, a[i].first, a[i].second);
	}
	calc();
	return 0;
}
