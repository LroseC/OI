#include <cstdio>
#include <cstring>

using namespace std;

const int N = 5e5 + 10;

int n;
int nex[N];
char str[N];
int f[N], pos[N];

int main(void)
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int i = 2, j = 0; i <= n; ++i) {
		while (j && str[i] != str[j + 1])
			j = nex[j];
		if (str[i] == str[j + 1])
			++j;
		nex[i] = j;
	}
//	for (int i = 1; i <= n; ++i)
//		printf(" %c ", str[i]);
//	puts("");
//	for (int i = 1; i <= n; ++i)
//		printf("%2d ", nex[i]);
//	puts("");
	f[1] = 1;
	pos[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (i - pos[f[nex[i]]] <= nex[i])
			f[i] = f[nex[i]];
		else f[i] = i;
		pos[f[i]] = i;
	}
//	for (int i = 1; i <= n; ++i)
//		printf("%2d ", f[i]);
//	puts("");
	printf("%d\n", f[n]);
	return 0;
}
