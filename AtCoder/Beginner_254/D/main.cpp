#include <cctype>
#include <cstdio>

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
using ui64 = unsigned long long;
const int N = 2e5 + 10;

int hsh[N];
int mp[N];

inline int calcHash(int t)
{
	if (hsh[t]) return hsh[t];
	int x = t;
	int hash = 1;
	for (int j = 2; j * j <= t; ++j)
		if (t % j == 0) {
			int cnt = 0;
			while (t % j == 0) {
				cnt ^= 1;
				t /= j;
			}
			if (cnt)
				hash = hash * j;
		}
	if (t != 1)
		hash = hash * t;
	return hsh[x] = hash;
}

int main(void)
{
	int n; read >> n;
	i64 res = 0;
	for (int i = 1; i <= n; ++i) {
		int t = i;
		++mp[calcHash(i)];
	}
	for (int i = 1; i <= n; ++i) {
		res += mp[calcHash(i)];
	}
	printf("%lld\n", res);
	return 0;
}
