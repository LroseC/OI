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
} io;

struct Change
{
	int op, id, color;
};

set<int> DEL1, DEL2;
long long n, m, c, q;
long long ans[(int)3e5 + 10];
Change cg[(int)3e5 + 10];

int main(void)
{
	io >> n >> m >> c >> q;
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	for (int i = 1; i <= q; ++i) {
		io >> cg[i].op >> cg[i].id >> cg[i].color;
	}
	for (int i = q; i >= 1; --i) {
		int op = cg[i].op, id = cg[i].id, color = cg[i].color;
		if (op == 1) {
			if (DEL1.count(id)) continue;
			DEL1.insert(id);
			ans[color] += m;
			--n;
		}
		else {
			if (DEL2.count(id)) continue;
			DEL2.insert(id);
			ans[color] += n;
			--m;
		}
	}
	for (int i = 1; i <= c; ++i) io << ans[i] << ' ';
	io << endl;
	return 0;
}