#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} cin;

int n;

struct PII
{
	int x, y;
	PII(int _x, int _y) : x(_x), y(_y) {}
	bool operator<(const PII &other) const
	{
		return 1ll * y * other.x < 1ll * other.y * x;
	}
	bool operator<=(const PII &other) const
	{
		return 1ll * y * other.x <= 1ll * other.y * x;
	}
};

int main(void)
{
	cin >> n;
	vector< pair<PII, PII> > a;
	for (int i = 1; i <= n; ++i) {
		int x, y; cin >> x >> y;
		PII begin(x, y - 1), end(x - 1, y);
		a.emplace_back(make_pair(end, begin));
	}
	sort(a.begin(), a.end());
	int ans = 1;
	auto now = a[0].first;
	for (int i = 1; i < a.size(); ++i) {
		if (now <= a[i].second) {
			auto t = a[i];
			++ans;
			now = a[i].first;
		}
	}
	printf("%d\n", ans);
	return 0;
}