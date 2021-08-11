#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
const double pi = 3.1415926589793238462643383;
// const double pi = acos(-1);
const double eps = 1e-18;

int cmp(double a, double b)
{
	if (fabs(b - a) < eps) return 0;
	if (a < b) return -1;
	return 1;
}
int sign(double a)
{
	if (fabs(a) < eps) return 0;
	if (a < 0) return -1;
	return 1;
}

struct PDD
{
	double x, y;
	bool operator<(const PDD &b) const
	{
		if (cmp(x, b.x)) return x < b.x;
		return y < b.y;
	}
	PDD operator+(const PDD &b) const
	{
		return {x + b.x, y + b.y};
	}
	PDD operator-(const PDD &b) const
	{
		return {x - b.x, y - b.y};
	}
};
double dot(PDD a, PDD b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(PDD a, PDD b)
{
	return a.x * b.y - a.y * b.x;
}
double get_len(PDD a)
{
	return sqrt(dot(a, a));
}
PDD rotate(PDD a, double theta)
{
	return {cos(theta) * a.x + sin(theta) * a.y, -sin(theta) * a.x + cos(theta) * a.y};
}
void Print(PDD x)
{
	printf("x = %lf, y = %lf\n", x.x, x.y);
}

int n;
PDD point[N << 2];
int cnt;
double a, b, r;
int dx[] = {1, 1, -1, -1};
int dy[] = {1, -1, -1, 1};
int stk[N << 2];
bool vis[N];

double Andrew(void)
{
	int top = 0;
	sort(point + 1, point + 1 + cnt);
	int tmp = 1;
	stk[++top] = 1;
	for (int i = 2; i <= cnt; ++i) {
		while (top > tmp && cross(point[stk[top]] - point[stk[top - 1]], point[i] - point[stk[top - 1]]) >= 0)
			vis[stk[top--]] = 0;
		stk[++top] = i;
		vis[i] = 1;
	}
	vis[1] = 0;
	tmp = top;
	for (int i = cnt - 1; i; --i) {
		if (vis[i]) continue;
		while (top > tmp && cross(point[stk[top]] - point[stk[top - 1]], point[i] - point[stk[top - 1]]) >= 0) --top;
		stk[++top] = i;
	}
	double res = 0;
	for (int i = 2; i <= top; ++i) res += get_len(point[stk[i]] - point[stk[i - 1]]);
	return res;
}

int main(void)
{
	scanf("%d", &n);
	scanf("%lf%lf%lf", &a, &b, &r);
	a = a / 2 - r, b = b / 2 - r;
	while (n--) {
		double x, y, theta;
		scanf("%lf%lf%lf", &x, &y, &theta);
		for (int i = 0; i < 4; ++i) {
			auto t = rotate({b * dx[i], a * dy[i]}, -theta);
			point[++cnt] = t + PDD({x, y});
		}
	}
	printf("%.2lf\n", Andrew() + 2.0 * pi * r);
	return 0;
}