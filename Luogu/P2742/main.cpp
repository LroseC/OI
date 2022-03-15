#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

struct PDD
{
	double x, y;
	bool operator<(const PDD &b) const
	{
		return x == b.x ? y < b.y : x < b.x;
	}
	PDD operator-(const PDD &b) const
	{
		return {x - b.x, y - b.y};
	}
	double operator*(const PDD &b) const
	{
		return x * b.x + y * b.y;
	}
};
double cross(const PDD &a, const PDD &b)
{
	return a.x * b.y - b.x * a.y;
}
double get_len(PDD x)
{
	return sqrt(x * x);
}
void Print(PDD x)
{
	printf("x = %lf, y = %lf\n", x.x, x.y);
}


int n;
PDD point[N];
int stk[N];
bool vis[N];

double Andrew(void)
{
	int top = 0;
	sort(point + 1, point + 1 + n);
	for (int i = 1; i <= n; ++i) {
		double tmp;
		while (top >= 2 && cross(point[stk[top]] - point[stk[top - 1]], point[i] - point[stk[top - 1]]) >= 0)
			--top;
		stk[++top] = i;
	}
	for (int i = n - 1; i; --i) {
		while (cross(point[stk[top]] - point[stk[top - 1]], point[i] - point[stk[top - 1]]) > 0) --top;
		stk[++top] = i;
	}
	double res = 0;
	for (int i = 2; i <= top; ++i) res += get_len(point[stk[i]] - point[stk[i - 1]]);
	return res;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf", &point[i].x, &point[i].y);
	}
	double res = Andrew();
	printf("%.2lf\n", res);
	return 0;
}