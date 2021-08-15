#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5e4 + 10;
const double eps = 1e-12;
const double pi = 3.141592653589793238462643383;

int sign(double x)
{
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
int cmpd(double a, double b)
{
	return sign(a - b);
}

struct Vector
{
	double x, y;
	Vector operator-(const Vector &b) const
	{
		return {x - b.x, y - b.y};
	}
	Vector operator+(const Vector &b) const
	{
		return {x + b.x, y + b.y};
	}
	bool operator<(const Vector &b) const
	{
		return x == b.x ? y < b.y : x < b.x;
	}
};
void Print(const Vector &b)
{
	printf("x = %lf, y = %lf\n", b.x, b.y);
}
Vector operator*(double a, const Vector &b)
{
	return {a * b.x, a * b.y};
}
double dot(Vector a, Vector b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(Vector a, Vector b)
{
	return a.x * b.y - a.y * b.x;
}
double get_len(Vector a)
{
	return sqrt(dot(a, a));
}
Vector rotate(Vector a, double theta)
{
	return {a.x * cos(theta) - a.y * sin(theta), a.x * sin(theta) + a.y * cos(theta)};
}

int n;
Vector q[N];
int stk[N], top = 0;
double ans = 1e10;
vector<int> convex;
Vector ansV[4];

void get_convex(void)
{
	sort(q + 1, q + 1 + n);

	top = 0;
	for (int i = 1; i <= n; ++i) {
		while (top >= 2 && sign(cross(q[stk[top]] - q[stk[top - 1]], q[i] - q[stk[top - 1]]) <= 0)) --top;
		stk[++top] = i;
	}
	for (int i = 1; i < top; ++i) convex.push_back(stk[i]);

	top = 0;
	for (int i = n; i >= 1; --i) {
		while (top >= 2 && sign(cross(q[stk[top]] - q[stk[top - 1]], q[i] - q[stk[top - 1]]) <= 0)) --top;
		stk[++top] = i;
	}
	for (int i = 1; i < top; ++i) convex.push_back(stk[i]);
}

void rotating_calipers(void)
{
	for (int i = 0, a = 2, b = 2, c = 2; i < convex.size(); ++i) {
		int u = convex[i], v = convex[(i + 1) % convex.size()];
		while (cmpd(cross(q[v] - q[u], q[convex[b + 1]] - q[u]), cross(q[v] - q[u], q[convex[b]] - q[u])) > 0) ++b, b %= convex.size();
		while (cmpd(dot(q[convex[a + 1]] - q[u], q[v] - q[u]), dot(q[convex[a]] - q[u], q[v] - q[u])) > 0) ++a, a %= convex.size();
		if (!i) c = b;
		while (cmpd(dot(q[convex[c + 1]] - q[v], q[u] - q[v]), dot(q[convex[c]] - q[v], q[u] - q[v])) > 0) ++c, c %= convex.size();
		double h = cross(q[v] - q[u], q[convex[b]] - q[u]) / get_len(q[v] - q[u]);
		double dax = dot(q[convex[a]] - q[v], q[v] - q[u]) / get_len(q[v] - q[u]);
		double dcx = dot(q[convex[c]] - q[u], q[u] - q[v]) / get_len(q[u] - q[v]);
		Vector normb = (1.0 / get_len(q[v] - q[u])) * (q[v] - q[u]);
		Vector normh = rotate(normb, pi / 2);
		Vector A, B, C, D;
		A = q[v] + dax * normb;
		B = A + h * normh;
		D = q[u] + (-dcx * normb);
		C = D + h * normh;
		double res = h * (dcx + get_len(q[v] - q[u]) + dax);
		if (res < ans) {
			ans = res;
			ansV[0] = A;
			ansV[1] = B;
			ansV[2] = C;
			ansV[3] = D;
		}
	}
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf", &q[i].x, &q[i].y);
	}
	get_convex();
	rotating_calipers();
	printf("%.5lf\n", ans);
	int k = 0;
	for (int i = 0; i < 4; ++i) {
		if (ansV[i].y < ansV[k].y) k = i;
		if (ansV[i].y == ansV[k].y && ansV[i].x < ansV[k].x) k = i;
	}
	for (int i = 0; i < 4; ++i) {
		if (sign(ansV[(i + k) % 4].x) == 0) ansV[(i + k) % 4].x = 0;
		if (sign(ansV[(i + k) % 4].y) == 0) ansV[(i + k) % 4].y = 0;
		printf("%.5lf %.5lf\n", ansV[(i + k) % 4].x, ansV[(i + k) % 4].y);
	}
	return 0;
}