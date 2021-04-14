#include <cstdio>

using namespace std;

#define reg register
#define ll long long
#define max(a, b) (a > b ? a : b)
#define lowbit(x) (x & -x)
const int N = 9;

int ans = -1, cnt;
int f[N][N];
int rd[N], cd[N], bd[N];
int dw[N][N];
int mp[1 << N];
int point[N][N] = {
	{6, 6, 6, 6, 6, 6, 6, 6, 6},
	{6, 7, 7, 7, 7, 7, 7, 7, 6},
	{6, 7, 8, 8, 8, 8, 8, 7, 6},
	{6, 7, 8, 9, 9, 9, 8, 7, 6},
	{6, 7, 8, 9, 10, 9, 8, 7, 6},
	{6, 7, 8, 9, 9, 9, 8, 7, 6},
	{6, 7, 8, 8, 8, 8, 8, 7, 6},
	{6, 7, 7, 7, 7, 7, 7, 7, 6},
	{6, 6, 6, 6, 6, 6, 6, 6, 6}
};

void Init(void);
int get_b(int, int);
void draw(int, int, int);
void DFS(int);
void Print(void);
void Print(int x);

int main()
{
	Init();
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) {
			scanf("%d", &f[i][j]);
			f[i][j] -= 1;
			if (~f[i][j]) draw(i, j, f[i][j]);
			else ++cnt;
		}
	DFS(cnt);
	printf("%d\n", ans);

	return 0;
}
void Init(void)
{
	for (int i = 0; i < N; ++i) mp[1 << i] = i;
	return;
}
void Print(int x)
{
	for (int i = 0; i < N; ++i) printf("%d ", (x >> i) & 1);
}
void Print(void)
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) printf("%d%c", f[i][j] + 1, j == 8 ? '\n' : ' ');
	for (int i = 0; i < N; ++i)
		Print(rd[i]), puts("!");
	for (int i = 0; i < N; ++i)
		Print(cd[i]), puts("!!");
	for (int i = 0; i < N; ++i)
		Print(bd[i]), puts("!!!");

	putchar('\n');
}
#define get_b(r, c) (r / 3 * 3 + c / 3)
void draw(int r, int c, int x)
{
	if (dw[r][c]) f[r][c] = -1;
	else f[r][c] = x;
	int b = get_b(r, c);
	rd[r] ^= (1 << x);
	cd[c] ^= (1 << x);
	bd[b] ^= (1 << x);
	dw[r][c] ^= 1;
	return;
}
void DFS(int dep)
{
	if (!dep) {
		int res = 0;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) res += (f[i][j] + 1) * point[i][j];
		ans = max(ans, res);
		return;
	}
//	Print();
	int minx = 0, miny = 0;
	int minn = 0x3f3f3f3f;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) {
			if (dw[i][j]) continue;
			int k = get_b(i, j);
			int t = rd[i] | cd[j] | bd[k];
			t ^= (1 << 9) - 1;
			int cnt = 0;
			for (int w = t; w; w -= lowbit(w)) ++cnt;
			if (cnt < minn) {
				minn = cnt;
				minx = i, miny = j;
			}
		}
	if (dw[minx][miny]) return;
	int r = minx, c = miny, b = get_b(minx, miny);
	int t = rd[r] | cd[c] | bd[b];
	t ^= (1 << 9) - 1;
//	Print(t);
//	puts("???");
	for (int w = t; w; w -= lowbit(w)) {
		int tod = mp[lowbit(w)];
//		printf("%d:%d...\n", lowbit(w), tod);
		draw(r, c, tod);
		DFS(dep - 1);
		draw(r, c, tod);
	}
	return;
}
#undef get_b
