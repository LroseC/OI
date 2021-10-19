#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

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

int T;
LL A, B, C;

inline bool check(void)
{
	int turn = 0;
	LL a = A, b = B, c = C;
	if (!b) return 0;
	--b; turn ^= 1;
	turn ^= (a & 1);
	LL m = min(b, c);
	b -= m, c -= m;
	if (b) turn ^= 1;
	return turn;
}

int main(void)
{
	T = read();
	while (T--) {
		A = read<LL>(), B = read<LL>(), C = read<LL>();
		bool second = 1;
		for (int i = 0; i < 2; ++i) {
			if (check()) second = 0;
			swap(B, C);
		}
		if (!second) puts("First");
		else puts("Second");
	}
	return 0;
}