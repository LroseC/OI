#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int n, m;
char s1[N], s2[N];
int nex[N];

int main(void)
{
	scanf("%s%s", s1, s2);
	n = strlen(s1);
	m = strlen(s2);
	for (int i = 1, j = 0; i < m; ++i) {
		while (j && s2[i] != s2[j])
			j = nex[j - 1];
		if (s2[i] == s2[j])
			++j;
		nex[i] = j;
	}
	for (int i = 0, j = 0; i < n; ++i) {
		while (j && s1[i] != s2[j])
			j = nex[j - 1];
		if (s1[i] == s2[j])
			++j;
		if (j == m)
			printf("%d\n", i - m + 2);
	}
	for (int i = 0; i < m; ++i)
		printf("%d ", nex[i]);
	puts("");
	return 0;
}
