#include <queue>
#include <vector>
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
using PII = pair<int, int>;

int n, m;
int D[N];
int stk[N];
vector<PII> ans;
priority_queue< PII, vector<PII>, greater<PII> > heap;

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n >> m;
	int sum = 0;
	for (int i = 1; i <= n; ++i)
		IO >> D[i];
	for (int i = 1; i <= n; ++i)
		sum += D[i];
	if (sum != 2 * n - 2) {
		puts("-1");
		return 0;
	}
	for (int i = 1; i <= m; ++i) {
		int u, v; IO >> u >> v;
		--D[u], --D[v];
	}
	for (int i = 1; i <= n; ++i) {
		if (D[i] < 0) {
			puts("-1");
			return 0;
		}
		if (D[i] == 0) continue;
		heap.emplace(D[i], i);
	}
	int top = 0;
	while (heap.size()) {
		auto t = heap.top(); heap.pop();
		if (top - (t.first - 1) < 0) {
			puts("-1");
			return 0;
		}
		for (int i = 1; i < t.first; ++i) {
			ans.emplace_back(stk[top--], t.second);
		}
		stk[++top] = t.second;
	}
	if (top != 0 && top != 2) {
		puts("-1");
		return 0;
	}
	else {
		for (int i = 1; i <= top; i += 2)
			ans.emplace_back(stk[i], stk[i + 1]);
	}
	if (ans.size() != n - m - 1) {
		puts("-1");
		return 0;
	}
	for (auto t : ans)
		--D[t.first], --D[t.second];
	for (int i = 1; i <= n; ++i)
		if (D[i] != 0) return -1;
	for (auto t : ans)
		printf("%d %d\n", t.first, t.second);
	return 0;
}
