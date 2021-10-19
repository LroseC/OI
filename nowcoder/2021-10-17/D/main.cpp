#include <cctype>
#include <cstdio>
#include <random>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e7 + 10;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int GCD;
int n, m, seed;
int a[N];

inline bool check(int x)
{
	return x % GCD;
}

inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main(void)
{
	n = read(), m = read(), seed = read();
	mt19937 rng(seed);
	auto get = [&]() {
		uniform_int_distribution<int> qwq(2, m);
		return qwq(rng);
	};
	int minx = INT_MAX, miny = INT_MAX;
	for (int i = 1; i <= n; ++i) {
		a[i] = get();
		if (a[i] < minx) {
			miny = minx;
			minx = a[i];
		}
		else if (a[i] < miny) {
			miny = a[i];
		}
	}
	GCD = a[1];
	for (int i = 2; i <= n; ++i) GCD = gcd(GCD, a[i]);
	LL mind = 1ll * minx * miny - minx - miny;
	for (LL s = mind; s >= 1; --s)
		if (!check(s)) {
			write(s);
			return 0;
		}
	return 0;
}