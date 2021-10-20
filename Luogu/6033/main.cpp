#include <queue>
#include <cctype>
#include <cstdio>

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

int n;
int a[(int)1e5 + 10];
queue<LL> q1, q2;

inline LL get(void)
{
	if (q1.empty()) { LL t = q2.front(); q2.pop(); return t; }
	if (q2.empty()) { LL t = q1.front(); q1.pop(); return t; }
	if (q1.front() < q2.front()) { LL t = q1.front(); q1.pop(); return t; }
	else { LL t = q2.front(); q2.pop(); return t; }
}

int main(void)
{
	LL ans = 0;
	n = read();
	while (n--) ++a[read()];
	for (int i = 1; i <= 1e5; ++i)
		for (int j = 0; j < a[i]; ++j)
			q1.emplace(i);
	while (q1.size() + q2.size() > 1) {
		LL x = get(), y = get();
		ans += x + y;
		q2.emplace(x + y);
	}
	write(ans);
	return 0;
}