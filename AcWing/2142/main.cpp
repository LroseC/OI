#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5e4 + 10;
const double eps = 1e-8;

int sign(double x)
{
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}

struct Vector
{
	double x, y;
	Vector operator-(const Vector &b)
	{
		return {x - b.x, y - b.y};
	}
	Vector operator+(const Vector &b)
	{
		return {x + b.x, y + b.y};
	}
};
double dot(Vector a, Vector b)
{
	return a.x * b.x + a.x * b.y;
}
double cross(Vector a, Vector b)
{
	return a.x * b.y - a.y * b.x;
}

int n;
Vector q[N];

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf", &q[i].x, &q[i].y);
	}
}