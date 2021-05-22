#include <cstdio>

using namespace std;

const int N = 3e4 + 10;

int T;
int fa[N], d[N], size[N];
inline int abs(int a) { return a < 0 ? -a : a; }

int get(int);
void merge(int, int);

int main()
{
	for (int i = 1; i < N; ++i) fa[i] = i, size[i] = 1;

	scanf("%d", &T);
	char type; int tmp1, tmp2;
	while (T--) {
		type = getchar();
		while (type == '\n' || type == ' ') type = getchar();
		scanf("%d%d", &tmp1, &tmp2);
		if (type == 'M') merge(tmp1, tmp2);
		else printf("%d\n", get(tmp1) == get(tmp2) ? abs(d[tmp1] - d[tmp2]) - 1: -1);
	}

	return 0;
}
int get(int x)
{
	if (fa[x] == x) return x;
	int tmp = get(fa[x]);
	d[x] += d[fa[x]];
	return fa[x] = tmp;
}
void merge(int x, int y)
{
	x = get(x), y = get(y);
	fa[x] = y;
	d[x] = size[y];
	size[y] += size[x];
}
