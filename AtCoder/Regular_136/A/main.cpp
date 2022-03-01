#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <iostream>

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
} IO;

const int N = 2e5 + 10;

char str[N];
vector<char> s;

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	int n;
	scanf("%d%s", &n, str + 1);
	for (int i = 1; str[i]; ++i)
		if (str[i] == 'A') {
			s.emplace_back('B');
			s.emplace_back('B');
		}
		else s.emplace_back(str[i]);
	for (int i = 0; i < s.size(); ++i) {
		if (i != s.size() - 1 && s[i] == 'B' && s[i + 1] == 'B')
			putchar('A'), ++i;
		else putchar(s[i]);
	}
	puts("");
	return 0;
}
