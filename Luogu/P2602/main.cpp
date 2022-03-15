#include <cctype>
#include <cstdio>

using namespace std;

typedef unsigned long long ULL;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

ULL pw10[20];
ULL f[20][10][10];

/*
 * f[i][j][k] 表示第 i 位，最高位是 j 时，数字 k 出现了多少次
 * f[i][j][k] = for (int t = 0; t < 10; ++t) f[i][j][k] += f[i - 1][t][k];
 * f[i][j][k] += (j == k ? pw10[i - 1] : 0);
 */

inline void init(void)
{
	pw10[0] = 1;
	for (int i = 1; i <= 18; ++i) pw10[i] = pw10[i - 1] * 10;

	for (int i = 0; i < 10; ++i) f[1][i][i] = 1;
	for (int i = 2; i < 18; ++i)
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k)
				for (int t = 0; t < 10; ++t) f[i][j][k] += f[i - 1][t][k];
			f[i][j][j] += pw10[i - 1];
		}
}
inline ULL calc(ULL number, int digit)
{
	static char num[30]; int p = 0;
	while (number) { num[++p] = number % 10; number /= 10; }

	ULL res = 0;
	for (int len = 1; len < p; ++len)
		for (int j = 1; j < 10; ++j) res += f[len][j][digit];

	for (int i = 1; i < num[p]; ++i) res += f[p][i][digit];
	for (int len = p - 1; len >= 1; --len) {
		for (int j = 0; j < num[len]; ++j) res += f[len][j][digit];
		for (int j = p; j > len; --j)
			if (num[j] == digit) res += num[len] * pw10[len - 1];
	}
	return res;
}

int main(void)
{
	ULL a = read<ULL>(), b = read<ULL>();
	init();
	for (int i = 0; i < 10; ++i) printf("%llu ", calc(b + 1, i) - calc(a, i));
	putchar('\n');
	return 0;
}