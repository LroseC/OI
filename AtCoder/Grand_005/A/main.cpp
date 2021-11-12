#include <cctype>
#include <cstdio>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} io;

char stk[1000010]; int top;
char str[1000010];

int main(void)
{
	scanf("%s", str + 1);
	for (int i = 1; str[i]; ++i) {
		if (top && stk[top] == 'S' && str[i] == 'T') --top;
		else stk[++top] = str[i];
	}
	printf("%d\n", top);
	return 0;
}