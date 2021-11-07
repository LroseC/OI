#include <set>
#include <cctype>
#include <cstdio>
#include <cstdlib>
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

const int N = 510;
using PII = pair<int, int>;

int n;
PII pos[N];
set<PII> S;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) {
		io >> pos[i].first >> pos[i].second;
		for (int j = 1; j < i; ++j) {
			int dx = pos[i].first - pos[j].first;
			int dy = pos[i].second - pos[j].second;
			int d = gcd(dx, dy);
			dx /= d;
			dy /= d;
			S.insert(make_pair(dx, dy));
			S.insert(make_pair(-dx, -dy));
		}
	}
	io << S.size() << endl;
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}