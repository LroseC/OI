#include <cmath>
#include <cctype>
#include <cstdio>

using namespace std;

const double eps = 1e-6;

struct Vector
{
	double x, y;

	Vector(void) { x = y = 0; }
	Vector(double _x, double _y) : x(_x), y(_y) {}

	friend Vector operator+(const Vector &a, const Vector &b)
	{
		return Vector(a.x + b.x, a.y + b.y);
	}
	friend Vector operator-(const Vector &a, const Vector &b)
	{
		return Vector(a.x - b.x, a.y - b.y);
	}
	friend Vector operator*(Vector a, double p)
	{
		a.x *= p;
		a.y *= p;
		return a;
	}
};

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
	FSI& operator>>(Vector &a)
	{
		*this >> a.x >> a.y;
		return *this;
	}
} IO;

Vector A, B, C, D;
double p, q, r;

double sq(double x) { return x * x; }
double Getdis(Vector X, Vector Y)
{
	return sqrt(sq(Y.x - X.x) + sq(Y.y - X.y));
}

double calc3(Vector X, Vector Y)
{
	return Getdis(A, X) / p + Getdis(X, Y) / r + Getdis(Y, D) / q;
}

double calc2(Vector X, Vector C, Vector D)
{
	Vector l = C, r = D;
	while (Getdis(l, r) > eps) {
		Vector lmid = l + (r - l) * (1.0 / 3), rmid = l + (r - l) * (2.0 / 3);
		if (calc3(X, lmid) < calc3(X, rmid))
			r = rmid;
		else l = lmid;
	}
	return calc3(X, l);
}
	
double calc(Vector A, Vector B, Vector C, Vector D)
{
	Vector l = A, r = B;
	while (Getdis(l, r) > eps) {
		Vector lmid = l + (r - l) * (1.0 / 3), rmid = l + (r - l) * (2.0 / 3);
		if (calc2(lmid, C, D) < calc2(rmid, C, D))
			r = rmid;
		else l = lmid;
	}
	return calc2(l, C, D);
}

int main(void)
{
	IO >> A >> B >> C >> D;
	IO >> p >> q >> r;
	printf("%.2lf\n", calc(A, B, C, D));
	return 0;
}
