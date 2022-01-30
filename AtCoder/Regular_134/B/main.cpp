#include <set>
#include <cctype>
#include <cstdio>

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

int n;
set<int> S[30];
char str[N];
char ans[N];

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n;
	scanf("%s", str + 1);
	for (int i = 1; i <= n; ++i) {
		ans[i] = str[i];
		S[str[i] - 'a'].insert(i);
	}
	int l = 1, r = n;
	int i = 0;
	while (l < r && i < 26) {
		auto it = S[i].upper_bound(r);
		if (it == S[i].begin()) {
			++i;
			continue;
		}
		--it;
		while (str[l] <= i + 'a' && l < *it)
			++l;
		if (l < *it) {
			swap(ans[l], ans[*it]);
			++l;
			r = *it - 1;
		}
		else ++i;
	}
	printf("%s\n", ans + 1);
	return 0;
}
