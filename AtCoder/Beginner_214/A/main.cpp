#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main(void)
{
	int n;
	scanf("%d", &n);
	if (1 <= n && n <= 125) puts("4");
	else if (126 <= n && n <= 211) puts("6");
	else if (212 <= n && n <= 214) puts("8");
	return 0;
}