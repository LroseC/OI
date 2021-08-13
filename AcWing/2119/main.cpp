#include <cmath>
#include <random>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;
const double eps = 1e-12;

mt19937 myrand(time(NULL));

double rand_eps(void)
{
	return (1.0 * myrand() / UINT_MAX - 0.5) * eps;
}

struct Vector
{
	double x, y, z;
	Vector operator+(const Vector &b) const
	{
		return {x + b.x, y + b.y, z + b.z};
	}
	Vector operator-(const Vector &b) const
	{
		return {x - b.x, y - b.y, z - b.z};
	}
	void shake(void)
	{
		x += rand_eps();
		y += rand_eps();
		z += rand_eps();
	}
};
Vector operator*(double t, const Vector &a)
{
	return {t * a.x, t * a.y, t * a.z};
}
double dot(const Vector &a, const Vector &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector cross(const Vector &a, const Vector &b)
{
	return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
double get_len(const Vector &a)
{
	return sqrt(dot(a, a));
}
Vector q[N];
struct Plain
{
	int v[3];
	Vector norm(void)
	{
		return cross(q[v[1]] - q[v[0]], q[v[2]] - q[v[0]]);
	}
	double area(void)
	{
		return get_len(norm()) / 2;
	}
	bool above(const Vector &p)
	{
		return (dot(p - q[v[0]], norm()) >= 0);
	}
};

int n, m, idx;
bool g[N][N];
Plain plain[N * 3], np[N * 3];

void get_convex_3d(void)
{
	plain[1] = {1, 2, 3}, plain[2] = {3, 2, 1};
	m = 2;
	for (int i = 4; i <= n; ++i) {
		idx = 0;
		for (int j = 1; j <= m; ++j) {
			bool t = plain[j].above(q[i]);
			for (int k = 0; k < 3; ++k) {
				int a = plain[j].v[k], b = plain[j].v[(k + 1) % 3];
				g[a][b] = t;
			}
			if (!t) np[++idx] = plain[j];
		}
		for (int j = 1; j <= m; ++j)
			for (int k = 0; k < 3; ++k) {
				int a = plain[j].v[k], b = plain[j].v[(k + 1) % 3];
				if (g[a][b] && !g[b][a]) {
					np[++idx] = {a, b, i};
				}
			}
		m = idx;
		for (int j = 1; j <= m; ++j) plain[j] = np[j];
	}
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lf%lf%lf", &q[i].x, &q[i].y, &q[i].z);
	for (int i = 1; i <= n; ++i) q[i].shake();

	get_convex_3d();
	double res = 0;
	for (int i = 1; i <= m; ++i) {
		res += plain[i].area();
	}
	printf("%.6lf\n", res);
}