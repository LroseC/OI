#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

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
} io;

const int N = 110;

int n;
int cnt[N];

int main(void)
{
	io >> n;
	int maxn = 0;
	for (int i = 1; i <= n; ++i) {
		int x; io >> x;
		maxn = max(x, maxn);
		++cnt[x];
	}
	for (int i = maxn; i > (maxn - 1) / 2 + 1; --i) {
		cnt[i] -= 2;
		if (cnt[i] < 0) {
			puts("Impossible");
			return 0;
		}
	}
	if (cnt[(maxn - 1) / 2 + 1] != 1 + (maxn & 1)) {
		puts("Impossible");
		return 0;
	}
	for (int i = (maxn - 1) / 2; i >= 1; --i) {
		if (cnt[i]) {
			puts("Impossible");
			return 0;
		}
	}
	puts("Possible");
	return 0;
}