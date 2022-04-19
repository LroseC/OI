#include <vector>
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

const int N = 1e6 + 10, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}

int n, m, maxS;
int cnt[N], s[N], fa[N];

int main(void)
{
	freopen("card.in", "r", stdin);
	freopen("card.out", "w", stdout);
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> s[i];
		++cnt[s[i]];
		maxS = std::max(maxS, s[i]);
	}
	for (int i = 1; i <= maxS; ++i)
		for (int j = i; j <= maxS; j += i)
			fa[i] += cnt[j];
	read >> m;
	for (int TIME = 1, c; TIME <= m; ++TIME) {
		read >> c;
		std::vector<int> p(c);
		for (int i = 0; i < c; ++i)
			read >> p[i];
		std::sort(p.begin(), p.end());
		p.erase(std::unique(p.begin(), p.end()), p.end());
		c = p.size();

		if (c == 0) {
			printf("%d\n", qpow(2, n));
			continue;
		}
		std::vector< std::vector<int> > tmp;
		std::vector<int> t(2);
		t[0] = t[1] = 1;
		tmp.emplace_back(t);
		for (int i = 0; i < c; ++i) {
			int now = tmp.size();
			for (int j = 0; j < now; ++j) {
				auto t = tmp[j];
				t[0] *= p[i];
				t.emplace_back(p[i]);
				tmp.emplace_back(t);
			}
		}
		int res = qpow(2, n) - 1;
		for (auto t : tmp)
			if (t[0] != 1) {
				int rescnt = 0;
				int sz = t.size() - 2;
				for (int state = 1; state < 1 << sz; ++state) {
					int tt = 1;
					for (int j = 0; j < sz; ++j)
						if (state >> j & 1)
							tt *= t[j + 2];
					rescnt += (__builtin_popcount(state) & 1 ? 1 : -1) * fa[tt];
				}
				if (sz & 1)
					res = Mod(res + mod - Mod(qpow(2, n - rescnt) + mod - 1));
				else
					res = Mod(res + Mod(qpow(2, n - rescnt) + mod - 1));
			}
		printf("%d\n", res);
	}
	return 0;
}
