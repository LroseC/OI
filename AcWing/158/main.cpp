#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e6 + 10;

int n;
char a[N], b[N];

int getmin(char s[])
{
	int i = 0, j = 1;
	while (i < n && j < n) {
		int k = 0;
		while (k < n && (s[i + k] == s[j + k])) ++k;
		if (n == k) break;
		if (s[i + k] < s[j + k]) j += k + 1;
		else i += k + 1;
		if (i == j) ++j;
	}
	
	int k = min(i, j);
	s[k + n] = 0;
	return k;
}

int main(void)
{
	scanf("%s%s", a, b);
	n = strlen(a);
	memcpy(a + n, a, n);
	memcpy(b + n, b, n);

	int x = getmin(a), y = getmin(b);
	if (strcmp(a + x, b + y)) puts("No");
	else {
		puts("Yes");
		printf("%s\n", a + x);
	}
	return 0;
}