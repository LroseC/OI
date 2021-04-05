#include <cstdio>

using namespace std;

int r, c;
int f[1010][1010];

int main()
{
	scanf("%d%d", &r, &c);
	for (int i = 1; i <= r ; ++i)
		for (int j = 1; j <= c; ++j) scanf("%d", &f[i][j]);
	return 0;
}
