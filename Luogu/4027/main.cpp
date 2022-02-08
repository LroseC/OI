#include <cmath>
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
} read;

/*
   设 f[i] 表示第 i 天能获得的最大金额
   f[i] => f[j], 兑换的 B 券为 f[i] / (R[i] * A[i] + B[i]);
   则有 f[0] = S, f[i] = max(j = 0; j < i) A[i] * (R[j] * f[j] / (R[j] * A[j] + B[j])) + B[i] * (f[j] / (R[j] * A[j] + B[j]))
   同时需要再做一遍 f[i] = max(j = 0; j < i) (f[i], f[j]); 可以简化为 f[i] = max(f[i], f[i - 1])
   <=> f[i] = max(j = 0; j < i) (A[i] * R[j] + B[i]) * f[j] / (A[j] * R[j] + B[j])
   <=> f[i] / B[i] = A[i] / B[i] * f[j] * R[j] / (A[j] * R[j] + B[j]) + f[j] / (A[j] * R[j] + B[j]);
*/

const int N = 1e5 + 10;
const double eps = 1e-10;

int n;
double f[N];

struct Vector
{
	double x, y;
} stk[N];
struct node
{
	int id;
	double A, B, R, K;
	Vector vec;
} q[N], tmp[N];

double slope(Vector a, Vector b)
{
	if (fabs(a.x - b.x) < eps) return 1e12;
	return (a.y - b.y) / (a.x - b.x);
}

void CDQ(int l, int r)
{
	if (l == r) {
		f[l] = max(f[l], f[l - 1]);
		q[l].vec.y = f[l] / (q[l].A * q[l].R + q[l].B);
		q[l].vec.x = q[l].vec.y * q[l].R;
		return;
	}

	int mid = l + r >> 1;
	CDQ(l, mid);

	int top = 0;
	for (int i = l; i <= mid; ++i) {
		while (top > 1 && slope(stk[top - 1], q[i].vec) - slope(stk[top - 1], stk[top]) >= eps)
			--top;
		stk[++top] = q[i].vec;
	}
	for (int i = mid + 1; i <= r; ++i) {
		int l = 1, r = top, mid;
		while (l < r) {
			mid = l + r + 1 >> 1;
			double Kmid = mid == 1 ? 1e20 : slope(stk[mid - 1], stk[mid]);
			if (Kmid - q[i].K > eps) l = mid;
			else r = mid - 1;
		}
		f[q[i].id] = max(f[q[i].id], stk[l].x * q[i].A + stk[l].y * q[i].B);
	}
	CDQ(mid + 1, r);

	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (q[i].vec.x < q[j].vec.x || (q[i].vec.x == q[j].vec.x && q[i].vec.y < q[j].vec.y))
			tmp[k++] = q[i++];
		else
			tmp[k++] = q[j++];
	}
	while (i <= mid)
		tmp[k++] = q[i++];
	while (j <= r)
		tmp[k++] = q[j++];

	for (int i = l; i <= r; ++i)
		q[i] = tmp[i];
}

int main(void)
{
	read >> n >> f[0];
	for (int i = 1; i <= n; ++i) {
		q[i].id = i;
		scanf("%lf%lf%lf", &q[i].A, &q[i].B, &q[i].R);
		q[i].K = -q[i].A / q[i].B;
	}
	CDQ(1, n);
	printf("%.3lf\n", f[n]);
	return 0;
}
