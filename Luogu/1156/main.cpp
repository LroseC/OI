#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 3000, M = 130;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

struct Rubbish
{
	int t, f, h;
	bool operator<(const Rubbish &b) const
	{
		return t < b.t;
	}
};

int n, m;
Rubbish q[110];
int f[3010];

int main(void)
{
	m = read(), n = read();
	for (int i = 1; i <= n; ++i) {
		int t = read(), f = read(), h = read();
		q[i] = {t, f, h};
	}
	sort(q + 1,q + 1 + n);
	f[0] = 10;
	for (int i = 1; i <= n; ++i) {
		for (int j = m; j >= 0; --j) {
			if (f[j] >= q[i].t) {
				if (j + q[i].h >= m) {
					printf("%d\n", q[i].t);
					return 0;
				}
				f[j + q[i].h] = max(f[j + q[i].h], f[j]);
				f[j] += q[i].f;
			}
		}
	}
	printf("%d\n", f[0]);
	return 0;
}