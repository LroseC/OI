#include <cctype>
#include <cstdio>
#include <cstring>

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

const int N = 2e5 + 10;

int a[N], b[N];
int cnt[2];
int change[2][N];

int main(void)
{
	int T;
	io >> T;
	while (T--) {
		int n; io >> n;
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j <= n * 2; ++j)
				change[i][j] = 0;
		for (int i = 1; i <= n * 2; ++i) {
			io >> a[i];
			--a[i];
		}
		for (int i = 1; i <= n * 2; ++i) {
			io >> b[i];
			--b[i];
		}
		cnt[0] = cnt[1] = n;
		for (int i = 1; i <= n * 2; ++i) {
			if ((a[i] + 1) % 3 == b[i]) continue;
			else {
				if (cnt[0]) {
					--cnt[0];
					a[i] = (b[i] + 2) % 3;
					change[i][0] = 1;
				}
				else if (cnt[1]) {
					--cnt[1];
					b[i] = (a[i] + 1) % 3;
					change[i][1] = 1;
				}
			}
		}
		for (int i = 1; i <= n * 2; ++i) {
			if ((a[i] + 1) % 3 == b[i]) {
				if (cnt[0] && cnt[1]) {
					--cnt[0]; --cnt[1];
					a[i] = (a[i] + 1) % 3;
					b[i] = (b[i] + 1) % 3;
				}
			}
			else {
				if (change[i][0] && cnt[1]) {
					--cnt[1];
					a[i] = (a[i] + 1) % 3;
					b[i] = (b[i] + 1) % 3;
				}
				else if (change[i][1] && cnt[0]) {
					--cnt[0];
					a[i] = (a[i] + 1) % 3;
					b[i] = (b[i] + 1) % 3;
				}
			}
		}
		io << n * 2 << endl;
		for (int i = 1; i <= n * 2; ++i) io << a[i] + 1 << ' ';
		io << endl;
		for (int i = 1; i <= n * 2; ++i) io << b[i] + 1 << ' ';
		io << endl;
	}
	return 0;
}