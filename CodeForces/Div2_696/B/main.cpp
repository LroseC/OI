#include <cctype>
#include <cstdio>

using namespace std;

typedef long long LL;
const int N = 3e4 + 10;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int d;
int idx, prime[N], v[N];

void shai(void)
{
	for (int i = 2; i < N; ++i) {
		if (!v[i]) {
			v[i] = i;
			prime[++idx] = i;
		}
		for (int j = 1; j <= idx; ++j) {
			if (prime[j] * i > N) break;
			v[prime[j] * i] = prime[j];
			if (prime[j] == v[i]) break;
		}
	}
}

int main(void)
{
	shai();
	int T = read();
	while (T--) {
		d = read();
		LL ans = 1;
		int p = 1;
		for (int i = 1, cnt = 0; i <= idx && cnt < 2; ++i)
			if (prime[i] - p >= d) {
				ans *= prime[i];
				p = prime[i];
				++cnt;
			}
		printf("%lld\n", ans);
	}
	return 0;
}