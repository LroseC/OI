#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;
using LL = long long;
using i128 = __int128;
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

const int N = 2e5 + 10;

int n, K;
LL a[N];
LL sum[N];
priority_queue< LL, vector<LL>, greater<LL> > heap;

int main(void)
{
	io >> n >> K;
	for (int i = 1; i <= n; ++i) {
		io >> a[i];
		a[i] = min(a[i], K);
	}
	sort(a + 1, a + 1 + n, greater<LL>());
	LL cha = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		LL x = a[i];
		heap.emplace(x + cha);
		if (heap.size() == K) {
			LL tmp = heap.top(); heap.pop();
			ans += tmp - cha; cha = tmp;
			while (heap.size() && heap.top() - cha <= 0) heap.pop();
		}
	}
	io << ans << endl;
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}