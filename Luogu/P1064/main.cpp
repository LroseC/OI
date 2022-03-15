#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 110, M = 3.2e4 + 10;
#define x first
#define y second
typedef long long LL;
typedef pair<int, int> PII;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

struct Query
{
	int w, v, op;
	bool operator<(const Query &b) const
	{
		return op < b.op;
	}
};

int n, m;
LL f[M];
vector<PII> a[N];
Query q[100010];

int main(void)
{
	scanf("%d%d", &m, &n);
	// for (int i = 1; i <= n; ++i) {
		// int w = read(), v = read(), op = read();
		// q[i] = {w, v, op};
	// }
	// sort(q + 1, q + 1 + n);
	for (int i = 1; i <= n; ++i) {
		// int w = q[i].w, v = q[i].v, op = q[i].op;
		int w = read(), v = read(), op = read();
		if (!op) a[i].emplace_back(PII({w, w * v}));
		else {
			int k = a[op].size();
			for (int j = 0; j < k; ++j) {
				auto tmp = a[op][j];
				a[op].emplace_back(PII({tmp.x + w, tmp.y + w * v}));
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		if (a[i].size())
			for (int j = m; j >= 0; --j)
				for (auto t : a[i]) {
					if (j < t.x) continue;
					f[j] = max(f[j], f[j - t.x] + t.y);
				}
	printf("%lld\n", f[m]);
	return 0;
}