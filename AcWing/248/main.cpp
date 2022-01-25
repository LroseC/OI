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
} IO;

struct Operation
{
	int x, l, r, val;

	void Operation(void) : x(0), l(0), r(0), val(0) {}
	void Operation(int _x, int _l, int _r, int _v) : x(_x), l(_l), r(_r), val(_v) {}
	bool operator<(const Operation &other) const
	{
		if (x != other.x)
			return x < other.x;
		return v < other.v;
	}
};

int n, W, H;
vector<int> nums;
vector<Operation> op;

int main(void)
{
	while (~scanf("%d%d%d", &n, &W, &H)) {
		op.clear();
		nums.clear();
		for (int i = 1; i <= n; ++i) {
			int x, y, val;
			IO >> x >> y >> val;
			op.emplace_back(x + 1, y + 1, y + H - 1, val);
			op.emplace_back(x + W - 1, y + 1, y + H - 1, val);
			nums.emplace_back(y + 1);
			nums.emplace_back(y + H - 1);
		}
		sort(nums.begin(), nums.end());
		nums.erase(unique(nums.begin(), nums.end()), nums.end());
	}
	return 0;
}
