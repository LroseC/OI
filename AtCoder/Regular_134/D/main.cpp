#include <set>
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
} IO;

struct PII
{
	int val, pos;

	PII(void) { val = pos = 0; }
	PII(int _v, int _p) : val(_v), pos(_p) {}
	bool operator<(const PII &other) const
	{
		if (val != other.val)
			return val < other.val;
		return pos < other.pos;
	}
};

const int N = 2e5 + 10;

int n;
int a[N << 1];
vector<PII> arr;
vector<int> ans;

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n;
	for (int i = 1; i <= n << 1; ++i)
		IO >> a[i];
	for (int i = 1; i <= n; ++i)
		arr.emplace_back(a[i], i);
	sort(arr.begin(), arr.end());
	int flag;
	int l = 0;
	for (auto t : arr) {
		if (t.pos < l) continue;
		if (!ans.size()) {
			ans.emplace_back(t.pos);
			l = t.pos + 1;
		}
		else if (ans.size() == 1) {
			if (t.val < a[ans[0] + n]) {
				ans.emplace_back(t.pos);
				l = t.pos + 1;
				if (a[ans[0] + n] < a[ans[1] + n])
					flag = 1;
				else if (a[ans[0] + n] == a[ans[1] + n])
					flag = 0;
				else flag = -1;
			}
		}
		else {
			if (t.val < a[ans[0] + n] || (t.val == a[ans[0] + n] && flag == 1)) {
				ans.emplace_back(t.pos);
				l = t.pos + 1;
				int sz = ans.size() - 1;
				if (flag == 0) {
					if (a[ans[sz - 1] + n] < a[ans[sz] + n])
						flag = 1;
					else if (a[ans[sz - 1] + n] == a[ans[sz] + n])
						flag = 0;
					else flag = -1;
				}
			}
		}
	}
	int val = a[ans[0]];
	int res = 0x3f3f3f3f;
	for (int i = 1; i <= n; ++i)
		if (val == a[i])
			res = min(res, a[i + n]);
	vector<int> tans;
	for (auto t : ans)
		tans.emplace_back(a[t]);
	for (auto t : ans)
		tans.emplace_back(a[t + n]);
	if (res <= tans[1]) {
		printf("%d %d\n", val, res);
		return 0;
	}
	for (auto t : tans)
		printf("%d ", t);
	puts("");
	return 0;
}
