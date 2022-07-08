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
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 1e7 + 10, mod = 20101009;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int val;
	ModInt(void) { val = 0; }
	ModInt(int x) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
};

int n, m;
int prime[N], v[N], mu[N], idx;
ModInt sum[N];

void init(void)
{
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!v[i]) {
			v[i] = i;
			mu[i] = -1;
			prime[++idx] = i;
		}
		for (int j = 1; j <= idx && i * prime[j] < N; ++j) {
			v[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) mu[i * prime[j]] = 0;
			else mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i < N; ++i) {
		sum[i] = sum[i - 1] + ModInt(i) * i * Mod(mu[i] + mod);
	}
}
ModInt S(int x) { return (1ll * x * (x + 1) / 2) % mod; }
ModInt calc(int t)
{
	ModInt res = 0;
	int x = n / t, y = m / t;
	for (int l = 1, r; l <= x; l = r + 1) {
		r = std::min(x / (x / l), y / (y / l));
		res = res + S(x / l) * S(y / l) * (S(r) - S(l - 1));
	}
	return res;
}
int main(void)
{
	//Think twice, code once.
	init();
	read >> n >> m;
	if (n > m) std::swap(n, m);
	ModInt res = 0;
	for (int l = 1, r; l <= std::min(n, m); l = r + 1) {
		r = std::min(n / (n / l), m / (m / l));
		res = res + calc(l) * (sum[r] - sum[l - 1]);
	}
	printf("%d\n", res.val);
	return 0;
}
