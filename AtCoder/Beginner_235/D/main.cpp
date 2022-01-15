#include <queue>
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
} IO;

const int N = 1e6 + 10;

int base, n;
int dis[N];
queue<int> q;

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> base >> n;
	memset(dis, -1, sizeof dis);
	q.emplace(1);
	dis[1] = 0;
	while (q.size()) {
		int u = q.front(); q.pop();
		if (u % 10) {
			int len = 1;
			int tmp = u / 10;
			while (tmp) {
				len *= 10;
				tmp /= 10;
			}
			if (len != 1) {
				int v = u / 10 + (u % 10 * len);
				if (v <= 1e6 && dis[v] == -1) {
					dis[v] = dis[u] + 1;
					q.emplace(v);
				}
			}
		}
		long long v = 1ll * u * base;
		if (v > 1e6) continue;
		if (dis[v] != -1) continue;
		dis[v] = dis[u] + 1;
		q.emplace(v);
	}
	printf("%d\n", dis[n]);
	return 0;
}