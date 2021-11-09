#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} io;

const int N = 5e5 + 10;

char str[N]; int n;
int nex1[N], nex2[N];

void kmp(int nex[])
{
	for (int i = 1, j = 0; i < n; ++i) {
		while (j && str[i] != str[j]) j = nex[j - 1];
		if (str[i] == str[j]) ++j;  nex[i] = j;
	}
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	scanf("%s", str);
	n = strlen(str);
	kmp(nex1);
	reverse(str, str + n);
	kmp(nex2);
	reverse(str, str + n);
	reverse(nex2, nex2 + n);
	int len = n - nex1[n - 1];
	if (!nex1[n - 1] || n % len) {
		printf("1\n1\n");
		return 0;
	}
	if (len == 1) {
		printf("%d\n%d\n", n, 1);
		return 0;
	}
	int res = 0;
	for (int i = 1; i < n; ++i) {
		int l1 = i - nex1[i - 1], l2 = n - i - nex2[i];
		if ((!nex1[i - 1] || i % l1) && (!nex2[i] || (n - i) % l2)) ++res;
	}
	printf("2\n%d\n", res);
	return 0;
}