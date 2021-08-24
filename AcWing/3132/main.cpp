#include <cstdio>
#include <cctype>

using namespace std;

#define gc getchar
#define pc putchar
typedef __int128 LL;
typedef long long ll;
const int Mod = 10007;

LL read(void)
{
	LL res = 0;
	char ch = gc();
	while (!isdigit(ch)) ch = gc();
	while (isdigit(ch)) {
		res = (res * 10 + (ch ^ '0')) % Mod;
		ch = getchar();
	}
	return res;
}
void write(LL x)
{
	static char buf[128];
	int p = -1;
	if (!x) pc('0');
	else while (x) buf[++p] = x % 10 ^ '0', x /= 10;
	while (~p) putchar(buf[p--]);
}

int main(void)
{
	int n = (int)read();
	write((LL)n * (n + 1) * (n + 2) / 6 % Mod);
	putchar('\n');
	return 0;
}