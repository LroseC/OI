#include <vector>
#include <cstdio>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

using LL = long long;

struct block
{
	int a, b, h;
	block(int _a, int _b, int _h)
	{
		if (_a > _b) swap(_a, _b);
		a = _a;
		b = _b;
		h = _h;
	}
	bool operator<(const block &others)
	{
		return 1ll * a * b > 1ll * others.a * others.b;
	}
};

int n;
LL f[1010];
vector<block> num;

int main(void)
{
	ios::sync_with_stdio(0);
	int caseid = 0;
	while (cin >> n, n) {
		++caseid;
		num.clear();
		memset(f, 0, sizeof f);
		num.emplace_back(INT_MAX, INT_MAX, 0);
		for (int i = 1; i <= n; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			num.emplace_back(b, c, a);
			num.emplace_back(a, c, b);
			num.emplace_back(a, b, c);
		}
		sort(num.begin(), num.end());

		LL ans = 0;
		for (int i = 1; i < num.size(); ++i) {
			for (int j = 0; j < i; ++j)
				if (num[i].a < num[j].a && num[i].b < num[j].b) {
					f[i] = max(f[i], f[j] + num[i].h);
					ans = max(ans, f[i]);
				}
		}
		printf("Case %d: maximum height = %lld\n", caseid, ans);
	}
	return 0;
}
