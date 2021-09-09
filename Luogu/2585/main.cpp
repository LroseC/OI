#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 5e5 + 10;

int cnt;
char str[N];
int fmin[N][3], fmax[N][3];
int ansmax = INT_MIN, ansmin = INT_MAX;

template<typename Int>
Int min(Int a, Int b, Int c)
{
	return min(a, min(b, c));
}
template<typename Int>
Int max(Int a, Int b, Int c)
{
	return max(a, max(b, c));
}

void dfs(int x)
{
	if (str[x] == '0') {
		fmin[x][0] = fmax[x][0] = 1;
		return;
	}
	int l = ++cnt;
	dfs(l);
	if (str[x] == '1') {
		fmin[x][0] = min(fmin[l][1], fmin[l][2]) + 1;
		fmin[x][1] = min(fmin[l][0], fmin[l][2]);
		fmin[x][2] = min(fmin[l][0], fmin[l][1]);

		fmax[x][0] = max(fmax[l][1], fmax[l][2]) + 1;
		fmax[x][1] = max(fmax[l][0], fmax[l][2]);
		fmax[x][2] = max(fmax[l][0], fmax[l][1]);
		return;
	}
	int r = ++cnt;
	dfs(r);
	if (str[x] == '2') {
		fmin[x][0] = min(fmin[l][1] + fmin[r][2], fmin[l][2] + fmin[r][1]) + 1;
		fmin[x][1] = min(fmin[l][0] + fmin[r][2], fmin[l][2] + fmin[r][0]);
		fmin[x][2] = min(fmin[l][0] + fmin[r][1], fmin[l][1] + fmin[r][0]);

		fmax[x][0] = max(fmax[l][1] + fmax[r][2], fmax[l][2] + fmax[r][1]) + 1;
		fmax[x][1] = max(fmax[l][0] + fmax[r][2], fmax[l][2] + fmax[r][0]);
		fmax[x][2] = max(fmax[l][0] + fmax[r][1], fmax[l][1] + fmax[r][0]);
	}
}

int main(void)
{
	scanf("%s", str + 1);
	dfs(++cnt);
	printf("%d %d\n", max(fmax[1][0], fmax[1][1], fmax[1][2]), min(fmin[1][0], fmin[1][1], fmin[1][2]));
	return 0;
}