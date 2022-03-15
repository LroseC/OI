#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

// #define DEBUG
typedef long long LL;
typedef pair<int, int> PII;
const int S = 1 << 8;

inline LL read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, mod;
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19};
PII nums[1010];
LL f[S][S], g[2][S][S];

/*
f[s1][s2] 表示小 A 选择的数所有质因子为 s1，小 B 选择的数所有质因子为 s2 的所有方案集合
*/

int main(void)
{
	n = read(), mod = read();

	for (int i = 2; i <= n; ++i) {
		int tmp = i;
		for (int j = 0; j < 8; ++j)
			if (!(tmp % prime[j])) {
				nums[i].second |= (1 << j);
				do tmp /= prime[j];
				while (!(tmp % prime[j]));
			}
		nums[i].first = tmp;
	}

	sort(nums + 2, nums + n + 1);

	f[0][0] = 1;
	for (int i = 2; i <= n; ++i) {
		#ifdef DEBUG
		printf("i = %d\n", i);
		#endif

		if (nums[i].first != nums[i - 1].first || nums[i].first == 1) {
			memcpy(g[0], f, sizeof f);
			memcpy(g[1], f, sizeof f);
		}

		#ifdef DEBUG
		puts("mid");
		#endif

		for (int s1 = S - 1; s1 >= 0; --s1)
			for (int s2 = S - 1; s2 >= 0; --s2) {
				if (!(s1 & nums[i].second)) {
					g[0][s1][s2 | nums[i].second] += g[0][s1][s2];
					g[0][s1][s2 | nums[i].second] %= mod;
				}
				if (!(s2 & nums[i].second)) {
					g[1][s1 | nums[i].second][s2] += g[1][s1][s2];
					g[1][s1 | nums[i].second][s2] %= mod;
				}
			}
		
		#ifdef DEBUG
		puts("after DP");
		#endif
		if (nums[i + 1].first != nums[i].first || nums[i + 1].first == 1)
			for (int s1 = 0; s1 < S; ++s1)
				for (int s2 = 0; s2 < S; ++s2)
					f[s1][s2] = (g[0][s1][s2] + g[1][s1][s2] - f[s1][s2]) % mod;

		#ifdef DEBUG
		puts("end");
		#endif
	}
	LL ans = 0;
	for (int s1 = 0; s1 < S; ++s1)
		for (int s2 = 0; s2 < S; ++s2) {
			ans += f[s1][s2];
			ans %= mod;
		}
	printf("%lld\n", (ans + mod) % mod);
	return 0;
}