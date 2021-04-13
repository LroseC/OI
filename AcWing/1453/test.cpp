#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
const int N = 1e5 + 10;

int k, top;
char str[N];
char stk[N];

int main()
{
	scanf("%s\n%d", str + 1, &k);
	int len = strlen(str + 1);
	for (int i = 1; i <= len; ++i) {
		while (top && str[i] < stk[top] && k) --top, --k;
		stk[++top] = str[i];
	}
	while (k--) --top;
	bool flag = 1;
	for (int i = 1; i <= top; ++i) {
		if (flag && stk[i] == '0') continue;
		flag = 0;
		putchar(stk[i]);
	}
	if (flag) puts("0");

	return 0;
}
