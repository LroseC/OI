#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

struct FastInput
{
	template<typename T>
	FastInput& operator>>(T &res)
	{
		res = 0; int f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		return *this;
	}
};
struct FastOutput
{
	FastOutput& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FastOutput& operator<<(const char *x)
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FastOutput& operator<<(const T res)
	{
		T x = res;
		static char buf[50]; int p = -1;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
};

FastInput cin;
FastOutput cout;
const char endl = '\n';
const int N = 5e4 + 10;

int n, k;
int rd[N];
int id[N];
int ans[N];
bool vis[N];

int randcnt = 0;
int mrand(void)
{
	++randcnt;
	if (randcnt > k) randcnt = 1;
	return rd[randcnt];
}

int main(void)
{
	cin >> n >> k;
	for (int i = 1; i <= k; ++i) cin >> rd[i];
	for (int i = 1; i <= n; ++i) id[i] = i;

	int high = n, low = 1, minid = 1, maxid = n, i = 1, j = n;
	for (int k = 1; k <= n; ++k) {
		int key_index = (mrand() % (high - low + 1)) + low;
		if (id[key_index] != minid) {
			ans[id[key_index]] = j--;
			swap(id[key_index], id[high--]);
		}
		else {
			ans[id[key_index]] = i++;
			swap(id[key_index], id[low++]);
		}
	}
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}