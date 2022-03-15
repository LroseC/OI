#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int mod = 1e9 + 7;
const int N = 110, S = 1 << 6;
inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, m;
int f[2][S][S];

void Print(int x)
{
	for (int i = 0; i < m; ++i)
		if (x >> i & 1) putchar('1');
		else putchar('0');
}
int Attack1(int state)
{
	int res = 0;
	for (int i = 0; i < m; ++i)
		if (state >> i & 1) {
			if (i - 2 > -1 && !(state >> i - 1 & 1))
				res |= (1 << i - 2);
			if (i + 2 < m && !(state >> i + 1 & 1))
				res |= (1 << i + 2);
		}
	return res;
}
int Attack2(int state, int stateg)
{
	int res = 0;
	for (int i = 0; i < m; ++i)
		if (state >> i & 1 && !(stateg >> i & 1)) {
			if (i - 1 > -1)
				res |= (1 << i - 1);
			if (i + 1 < m)
				res |= (1 << i + 1);
		}
	return res;
}

int main(void)
{
	n = read(), m = read();
	if (n < m) swap(n, m);
	for (int state = 0; state < 1 << m; ++state)
		for (int statep = 0; statep < 1 << m; ++statep) {
			if ((Attack1(state) & statep) || (Attack1(statep) & state)) continue;
			f[1][state][statep] = 1;
		}

	for (int i = 2; i <= n + 1; ++i) {
		memset(f[i & 1], 0, sizeof f[i & 1]);
		for (int state = 0; state < 1 << m; ++state)
			for (int stateg = 0; stateg < 1 << m; ++stateg)
				for (int statef = 0; statef < 1 << m; ++statef) {
					if ((Attack1(stateg) & state) || (Attack2(statef, stateg) & state)) continue;
					if ((Attack1(state) & stateg) || (Attack2(state, stateg) & statef)) continue;
					f[i & 1][stateg][state] += f[i - 1 & 1][statef][stateg];
					f[i & 1][stateg][state] %= mod;
				}
		#ifdef DEBUG
		for (int states = 0; states < 1 << m; ++states)
			for (int statet = 0; statet < 1 << m; ++statet) {
				printf("f[%d][", i + 1); Print(states); printf("]["); Print(statet); printf("] = %d\n", f[i & 1][states][statet]);
			}
		#endif
	}

	int ans = 0;
	for (int states = 0; states < 1 << m; ++states)
		for (int statet = 0; statet < 1 << m; ++statet) {
			ans += f[n - 1 & 1][states][statet];
			ans %= mod;
		}

	printf("%d\n", f[n + 1 & 1][0][0]);
	return 0;
}