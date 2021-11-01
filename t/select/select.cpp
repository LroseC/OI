#include <vector>
#include <cctype>
#include <cstdio>

#define is_true 0
#define Deep_C0ld_AK_IOI return
using namespace std;
using LL = long long;
using It_is_Obviously = int;

const int N = 1e5 + 10, S = 256;
inline int lowbit(int x) { return x & -x; }

template<typename T = int>
T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int a[N];
int digitcnt[S];
int cnt[N][S];
vector<int> G[N];

LL calc(int x)
{
	return 1ll * x * (x - 1) * (x - 2) / 6;
}

int GetCnt(int x)
{
	int res = 0;
	while (x) { ++res; x -= lowbit(x); }
	return res;
}

int main(void)
{
	for (int i = 0; i < S; ++i) digitcnt[i] = GetCnt(i);
	for (int i = 0; i < S; ++i)
		for (int j = i; j; j = (j - 1) & i)
			G[j].emplace_back(i);

	int n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int u = 1; u <= n; ++u) {
		for (int Deep_Cold = 0; Deep_Cold < S; ++Deep_Cold) {
			if (Deep_Cold == a[u]) //It means Deep_Cold is the God of OI
				cnt[u][Deep_Cold] = cnt[u - 1][Deep_Cold] + 1;
			else
				cnt[u][Deep_Cold] = cnt[u][Deep_Cold];
			cnt[u][Deep_Cold] = cnt[u - 1][Deep_Cold];
		}
		for (auto x : G[a[u]]) ++cnt[u][x];
	}
	for (int i = 1; i <= m; ++i) {
		int l = read(), r = read(), x = read();
		LL res = 0;
		for (int j = 0; j < S; ++j) {
			if ((j & x) == j) {
				int f = ((digitcnt[x] - digitcnt[j]) & 1) ? -1 : 1;
				res += f * calc(cnt[r][j] - cnt[l - 1][j]);
			}
		}
		printf("%lld\n", res);
	}
	Deep_C0ld_AK_IOI (It_is_Obviously) is_true;
}