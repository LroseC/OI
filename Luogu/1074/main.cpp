#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;

template<typename Int> inline void read(Int &res)
{
	res = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) { res = res * 10 + (ch ^ '0'); ch = getchar(); }
}
template<typename Int> inline void write(Int x)
{
	static char buf[50]; int p = -1;
	if (!x) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10 ^ '0'; x /= 10; }
	while (p >= 0) { putchar(buf[p]); --p; }
}

const int N = 9;

inline int lowbit(int x) { return x & -x; }

int ans = -1;
int cnt = 0, score = 0;
int G[9][9];
int val[9][9];
int line[N], cur[N], block[N];

inline int gb(int x, int y)
{
	return x / 3 * 3 + y / 3;
}

void dfs(int dep)
{
	if (!dep) {
		// puts("begin");
		// for (int i = 0; i < N; ++i, puts(""))
		// 	for (int j = 0; j < N; ++j)
		// 		printf("%d ", G[i][j]);
		// puts("end");
		int res = 0;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				res += val[i][j] * G[i][j];
		ans = max(ans, res);
		return;
	}
	int minx = 0, miny = 0, minn = 0x3f3f3f3f;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (!G[i][j]) {
				int k = gb(i, j);
				int t = line[i] | cur[j] | block[k];
				t ^= (1 << 10) - 1 ^ 1;
				int tmp = 0;
				for (int w = t; w; w -= lowbit(w)) ++tmp;
				if (tmp < minn) {
					minx = i;
					miny = j;
					minn = tmp;
				}
			}
	int r = minx, c = miny, b = gb(r, c);
	int t = line[r] | cur[c] | block[b];
	t ^= (1 << 10) - 1 ^ 1;
	for (int i = 1; i < 10; ++i)
		if (t >> i & 1) {
			line[r] ^= 1 << i;
			cur[c] ^= 1 << i;
			block[b] ^= 1 << i;
			G[r][c] = i;
			dfs(dep - 1);
			G[r][c] = 0;
			line[r] ^= 1 << i;
			cur[c] ^= 1 << i;
			block[b] ^= 1 << i;
		}
}

int main(void)
{
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j) {
			int x = min(i, 8 - i);
			int y = min(j, 8 - j);
			val[i][j] = min(x, y) + 6;
		}
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j) {
			read(G[i][j]);
			if (G[i][j]) {
				line[i] ^= 1 << G[i][j];
				cur[j] ^= 1 << G[i][j];
				block[gb(i, j)] ^= 1 << G[i][j];
			}
			score += G[i][j] * val[i][j];
			cnt += !G[i][j];
		}
	dfs(cnt);
	write(ans); putchar('\n');
	return 0;
}