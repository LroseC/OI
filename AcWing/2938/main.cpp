#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5e4 + 10;

struct Vector
{
	int x, y;
	void Print(void)
	{
		printf("x = %d, y = %d\n", x, y);
	}
	bool operator<(const Vector &b) const
	{
		return x == b.x ? y < b.y : x < b.y;
	}
	Vector operator+(const Vector &b) const
	{
		return {x + b.x, y + b.y};
	}
	Vector operator-(const Vector &b) const
	{
		return {x - b.x, y - b.y};
	}
};
Vector operator*(int a, const Vector &b)
{
	return {a * b.x, a * b.y};
}
int dot(Vector a, Vector b)
{
	return a.x * b.x + a.y * b.y;
}
int cross(Vector a, Vector b)
{
	return a.x * b.y - a.y * b.x;
}

int n, ans;
Vector q[N];
vector<int> convex;
int stk[N];
bool vis[N];

void get_convex(void)
{
	sort(q + 1, q + 1 + n);
	int top = 0;
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		while (top >= 2 && cross(q[stk[top]] - q[stk[top - 1]], q[i] - q[stk[top - 1]]) <= 0) vis[stk[top--]] = 0;
		vis[stk[++top] = i] = 1;
	}
	for (int i = 1; i < top; ++i) convex.push_back(stk[i]);
	top = 0;
	vis[1] = vis[n] = 0;
	for (int i = n; i >= 1; --i) {
		if (vis[i]) continue;
		while (top >= 2 && cross(q[stk[top]] - q[stk[top - 1]], q[i] - q[stk[top - 1]]) <= 0) vis[stk[top--]] = 0;
		vis[stk[++top] = i] = 1;
	}
	for (int i = 1; i < top; ++i) convex.push_back(stk[i]);
	return;
}
void rotating_calipers(void)
{
	for (int i = 0, j = 1; i < convex.size(); ++i) {
		auto u = convex[i], v = convex[(i + 1) % convex.size()];
		while (cross(q[v] - q[u], q[convex[j]] - q[u]) < cross(q[v] - q[u], q[convex[(j + 1) % convex.size()]] - q[u]))
			j = (j + 1) % convex.size();
		ans = max(dot(q[convex[j]] - q[u], q[convex[j]] - q[u]), ans);
		ans = max(dot(q[convex[j]] - q[v], q[convex[j]] - q[v]), ans);
	}
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &q[i].x, &q[i].y);
	get_convex();
	for (auto x : convex) q[x].Print();
	rotating_calipers();
	printf("%d\n", ans);
	return 0;
}