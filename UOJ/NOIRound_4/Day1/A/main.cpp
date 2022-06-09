#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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
const int N = 6e4 + 10, S = 1 << 8;

int f[N][10];
int min[S][S];

int main(void)
{
	int n, K;
	read >> n >> K;
	std::vector<int> a(n + 1), pre(n + 1);
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] ^ a[i];
	}
	std::memset(f, 0x3f ,sizeof f);
	f[0][0] = 0;
	for (int j = 1; j <= K; ++j) {
		std::memset(min, 0x3f, sizeof min);
		for (int i = 0; i <= n; ++i) {
			for (int t = 0; t < 1 << 8; ++t) {
				int res = min[pre[i] >> 8][t] + ((pre[i] & (1 << 8) - 1) ^ t);
				f[i][j] = std::min(f[i][j], res);
			}
			for (int t = 0; t < 1 << 8; ++t) {
				int fir8 = pre[i] >> 8;
				int sec8 = pre[i] & (1 << 8) - 1;
				min[t][sec8] = std::min(min[t][sec8], f[i][j - 1] + ((t ^ fir8) << 8));
			}
		}
	}
	for (int i = K; i <= n; ++i)
		printf("%d ", f[i][K]);
	puts("");
	return 0;
}
