#include <cctype>
#include <cstdio>
#include <unordered_map>

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

using i64 = long long;
const int N = 4641588;

i64 n;
int mod, inv6;
bool vis[N];
int sump[N], prime[N], idx;
std::unordered_map<i64, int> sum;

inline int sq(int x) { return 1ll * x * x % mod; }
inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline int sum2(int x) { return 1ll * x * (x + 1) % mod * (2 * x + 1) % mod * inv6 % mod; }
inline int sum3(int x) { return sq(1ll * x * (x + 1) / 2 % mod); }
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

void initSum(void)
{
	sump[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) {
			prime[++idx] = i;
			sump[i] = (i - 1);
		}
		for (int j = 1; j <= idx && 1ll * i * prime[j] < N; ++j) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0)
				sump[i * prime[j]] = sump[i] * prime[j];
			else
				sump[i * prime[j]] = sump[i] * (prime[j] - 1);
		}
	}
	for (int i = 1; i < N; ++i) {
		sump[i] = 1ll * sump[i] * sq(i) % mod;
		sump[i] = Mod(sump[i - 1] + sump[i]);
	}
}
int getSum(i64 x)
{
	if (x < N)
		return sump[x];
	if (sum.count(x))
		return sum[x];
	int res = sum3(x % mod);
	for (i64 l = 2, r; l <= x; l = r + 1) {
		r = x / (x / l);
		int tmp = Mod(sum2(r % mod) + mod - sum2((l - 1) % mod));
		res = Mod(res + mod - 1ll * tmp * getSum(x / l) % mod);
	}
	return sum[x] = res;
}

int main(void)
{
	read >> mod >> n;
	inv6 = qpow(6, mod - 2);
	initSum();
	int res = 0;
	for (i64 l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		int sum = Mod(getSum(r) + mod - getSum(l - 1));
		res = Mod(res + 1ll * sum3(n / l % mod) * sum % mod);
	}
	printf("%d\n", res);
	return 0;
}
