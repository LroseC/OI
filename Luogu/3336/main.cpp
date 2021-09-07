#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 2e6;
#define int long long
const int Mod = 19940417;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res;
}
inline int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % Mod;
		base = 1ll * base * base % Mod;
		k >>= 1;
	}
	return res;
}

#define x first
#define y second
typedef pair<int, int> PII;

int n, k;
int ans;
int f[N][2];
vector<PII> a;

signed main(void)
{
	n = read(), k = read();
	for (int i = 0; i < k; ++i) {
		int x = read(), y = read();
		a.emplace_back(PII({x, y}));
	}
	a.emplace_back(PII({0, 0}));
	a.emplace_back(PII({n, 0}));
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	f[0][1] = 1;
	for (int i = 1; i < a.size(); ++i) {
		auto last = a[i - 1], now = a[i];
		int tmp = (now.x - last.x - last.y - now.y) >> 1;
		if (now.y - last.y == now.x - last.x)
			f[i][0] = (1ll * f[i - 1][0] + (last.y ? 0 : f[i - 1][1])) % Mod;
		else if (last.y - now.y == now.x - last.x)
			f[i][1] = (1ll * f[i - 1][0] + f[i - 1][1]) % Mod;
		else if (tmp < 0)
			f[i][1] = (1ll * f[i - 1][0] + (last.y ? 0 : f[i - 1][1])) % Mod;
		else if (tmp == 0) {
			f[i][0] = (1ll * f[i - 1][0] + f[i - 1][1]) % Mod;
			f[i][1] = (1ll * f[i - 1][0] + (last.y ? 0 : f[i - 1][i])) % Mod;
		}
		else {
			int p = qpow(2, tmp - 1);
			if (now.y)
				f[i][0] = (1ll * f[i - 1][1] + 2 * f[i - 1][0]) % Mod * p % Mod;
			f[i][1] = (1ll * f[i - 1][1] + 2ll * f[i - 1][0]) % Mod * p % Mod;
		}
		if (f[i][1] || !now.y)
			ans = max(ans, (now.x - last.x + now.y + last.y) >> 1);
	}
	printf("%lld %lld\n", f[a.size() - 1][1] % Mod, ans);
	return 0;
}