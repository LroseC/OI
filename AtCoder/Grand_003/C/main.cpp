#include <vector>
#include <cctype>
#include <cstdio>
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
} cin;

int n;
vector<int> nums;
int a[100010], b[100010];

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		nums.emplace_back(a[i]);
	}
	sort(nums.begin(), nums.end());
	for (int i = 0; i < n; ++i)
		a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (i % 2 != a[i] % 2) ++cnt;
	}
	printf("%d\n", cnt / 2);
	return 0;
}