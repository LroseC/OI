#include <set>
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
} io;

const int N = 3e5 + 10;

struct Vector
{
	int x, y;
	Vector(void) { x = y = 0; }
	Vector(int _x, int _y) : x(_x), y(_y) {}
	bool operator<(const Vector& other) const
	{
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};

int n;
set<int> S;
Vector chess[N];

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) {
		io >> chess[i].x >> chess[i].y;
	}
	sort(chess + 1, chess + 1 + n);
	for (int i = 1; i < k; ++i) {
		S.insert(chess[i].y);
	}
	int ans = 0;
	for (int i = k; i <= n; ++i) {
		S.insert(chess[i].y);
		int left = *S.begin(), right = S.back();
		if (right - left + 1 <= k) ans += k - right + left;
	}
	printf("%d\n", ans);
	return 0;
}
