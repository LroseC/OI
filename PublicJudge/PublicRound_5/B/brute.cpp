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

i64 work(int n)
{
	i64 res = 0;
	int t[100], p[100], tmp[100];
	for (int i = 1; i <= n; ++i)
		t[i] = i;
	do {
#ifdef A
		for (int i = 1; i <= n; ++i)
			p[i] = t[i];
		for (int i = 2; i <= n; ++i)
			if (p[i] < p[1]) {
				for (int j = 1; j <= n; ++j)
					tmp[j] = p[j];
				for (int j = 1, k = i; j <= n; ++j, ++k)
					p[j] = tmp[k > n ? k - n : k];
			}
		if (p[1] != 1) ++res;
#else
		int *p = tmp;
		for (int i = 1; i <= n; ++i) {
			tmp[i] = tmp[i + n] = t[i];
		}
		int last = 0;
		auto Mod = [&](int x) { return x > n ? x - n : x; };
		for (int i = 2; i <= n; ++i)
			if (p[Mod(last + i)] < p[Mod(last + 1)]) {
				last = Mod(last + i - 1);
			}
		if (p[Mod(last + 1)] != 1) ++res;
#endif
	} while (std::next_permutation(t + 1, t + 1 + n));
	return res;
}

int main(void)
{
	for (int n = 3; n <= 13; ++n) {
		printf("ans[%d] = %lld\n", n, work(n));
	}
	return 0;
}
