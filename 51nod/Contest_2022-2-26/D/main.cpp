#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define int long long

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
} read;

using LL = long long;
inline int Mod(int x) { return x == 3 ? 0 : x; }

LL D, X, Y;
int cnt, Xcnt, Ycnt;
int digit[110], Xdigit[110], Ydigit[110];
LL f[110][3], g[110][3];

void init(void)
{
	cnt = Xcnt = Ycnt = 0;
	memset(digit, 0, sizeof digit);
	memset(Xdigit, 0, sizeof Xdigit);
	memset(Ydigit, 0, sizeof Ydigit);
	int t = X;
	while (t)
		Xdigit[++Xcnt] = t % 3, t /= 3;
	t = Y;
	while (t)
		Ydigit[++Ycnt] = t % 3, t /= 3;
	t = D;
	while (t)
		digit[++cnt] = t % 3, t /= 3;
}
void calc(void)
{
	LL res = 0;
	cnt = max(cnt, Xcnt);
	cnt = max(cnt, Ycnt);
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	f[0][0] = g[0][0] = 1;
	for (int i = 1; i <= cnt + 1; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k) {
				int nowX = Mod(Xdigit[i] + (Xdigit[i - 1] + k >= 3));
				int nowY = Mod(Ydigit[i] + (Ydigit[i - 1] + k >= 3));
				if ((nowX & 1) == (nowY & 1)) {
					f[i][j] += f[i - 1][k];
					if (j == digit[i] && k < digit[i - 1])
						g[i][j] += f[i - 1][k];
					else if (j == digit[i] && k == digit[i - 1])
						g[i][j] += g[i - 1][k];
				}
			}

	res += g[cnt + 1][digit[cnt + 1]];
	printf("%lld\n", res);
}

signed main(void)
{
	int T; read >> T;
	while (T--) {
		read >> D >> X >> Y;
		init();
		calc();
	}
	return 0;
}
