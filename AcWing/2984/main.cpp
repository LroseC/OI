#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;
const double eps = 1e-8;
struct PDD
{
	double x, y;
	PDD operator-(const PDD &b) const
	{
		return {x - b.x, y - b.y};
	}
};
void Print(PDD x)
{
	printf("x = %lf, y = %lf\n", x.x, x.y);
}

int T;
int n;
PDD q[N << 1];

int cmp(double x, double y)
{
	if (fabs(x - y) < eps) return 0;
	if (x < y) return -1;
	return 1;
}
int sign(double x)
{
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}
double cross(PDD a, PDD b)
{
	return a.x * b.y - b.x * a.y;
}

bool check(void)
{
	for (int i = 1; i <= n * 2; ++i)
		for (int j = i + 1; j <= n * 2; ++j) {
			if (!cmp(q[i].x, q[j].x) && !cmp(q[i].y, q[j].y)) continue;
			bool flag = 1;
			for (int k = 1; k <= n; ++k) {
				if (sign(cross(q[j] - q[i], q[k] - q[i])) * sign(cross(q[j] - q[i], q[k + n] - q[i])) > 0) {
					flag = 0;
					break;
				}
			}
			if (flag) return 1;
		}
	return 0;
}

int main(void)
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			double x1, y1, x2, y2;
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			q[i] = {x1, y1}, q[i + n] = {x2, y2};
		}

		if (check()) puts("Yes!");
		else puts("No!");
	}
	return 0;
}