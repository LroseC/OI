#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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
} read;

using i64 = long long;
const int N = 5e3 + 10;

struct Vector
{
	int id, x, y;

	Vector(void) {}
	Vector(int _x, int _y)
	{
		x = _x, y = _y;
	}
	bool operator<(const Vector &other)
	{
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
	Vector operator-(const Vector &other)
	{
		return Vector(x - other.x, y - other.y);
	}
	Vector operator+(const Vector &other)
	{
		return Vector(x + other.x, y + other.y);
	}
};
i64 cross(const Vector &a, const Vector &b)
{
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

int n;
char str[N];
std::vector<Vector> point;

int main(void)
{
	read >> n;
	point.resize(n);
	for (int i = 0; i < n; ++i) {
		point[i].id = i + 1;
		read >> point[i].x >> point[i].y;
	}
	scanf("%s", str);
	std::sort(point.begin(), point.end());

	std::vector<int> vis(n), ans;
	int u = 0;
	vis[0] = 1;
	ans.emplace_back(point[0].id);
	for (int i = 0; i < n - 2; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j)
			if (!vis[j]) {
				if (v == -1) v = j;
				else {
					i64 tmp = cross(point[j] - point[u], point[v] - point[u]);
					Vector ta = point[j] - point[u], tb = point[v] - point[u];
					if (str[i] == 'L' && tmp > 0)
						v = j;
					if (str[i] == 'R' && tmp < 0)
						v = j;
				}
			}
		vis[u = v] = 1;
		ans.emplace_back(point[u].id);
	}
	for (int i = 0; i < n; ++i)
		if (!vis[i]) ans.emplace_back(point[i].id);
	for (int i = 0; i < ans.size(); ++i)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}
