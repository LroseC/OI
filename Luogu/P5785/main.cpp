#include <cctype>
#include <cstdio>
#include <cstring>
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
   f[i] = f[j] + (w[i] - w[j]) * t[i] + (w[n] - w[j]) * s
   <=> f[i] - w[i] * t[i] = -t[i] * w[j] + (w[n] - w[j]) * s + f[j];
   <=> t[i] * w[j] + f[i] - w[i] * t[i] = f[j] + (w[n] - w[j]) * s;
   最小化 f[i].
   所以设 X = w[j], Y = f[j] + (w[n] - w[j]) * s; 维护一个下凸壳即可
   K = t[i], B = f[i] - w[i] * t[i];
   KX + B = Y;
*/

using LL = long long;
const int N = 3e5 + 10;

int n, s;
int stk[N], top;
LL T[N], w[N], f[N], X[N], Y[N];

void insert(int id)
{
	LL x = X[id], y = Y[id];
	int a = stk[top], b = stk[top - 1];
	while (top > 1 && (long double)(Y[id] - Y[b]) * (X[a] - X[b]) <= (long double)(Y[a] - Y[b]) * (X[id] - X[b])) {
		--top;
		a = stk[top], b = stk[top - 1];
	}
	stk[++top] = id;
}
int main(void)
{
	read >> n >> s;
	for (int i = 1; i <= n; ++i)
		read >> T[i] >> w[i];
	for (int i = 1; i <= n; ++i)
		T[i] += T[i - 1], w[i] += w[i - 1];
	memset(f, 0x7f, sizeof f);
	f[0] = 0; Y[0] = w[n] * s;
	insert(0);
	for (int i = 1; i <= n; ++i) {
		int l = 1, r = top;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			int a = stk[mid], b = stk[mid - 1];
			if (T[i] * (X[a] - X[b]) <= (Y[a] - Y[b]))
				r = mid - 1;
			else
				l = mid;
		}
		int j = stk[l];
		f[i] = Y[j] - T[i] * X[j] + w[i] * T[i];

		X[i] = w[i], Y[i] = f[i] + (w[n] - w[i]) * s;
		insert(i);
	}
	printf("%lld\n", f[n]);
	return 0;
}
/*
   f[i] = f[j] + (w[i] - w[j]) * t[i] + (w[n] - w[j]) * s
   <=> f[i] - w[i] * t[i] = -t[i] * w[j] + (w[n] - w[j]) * s + f[j];
   <=> t[i] * w[j] + f[i] - w[i] * t[i] = f[j] + (w[n] - w[j]) * s;
   最小化 f[i].
   所以设 X = w[j], Y = f[j] + (w[n] - w[j]) * s; 维护一个下凸壳即可
   K = t[i], B = f[i] - w[i] * t[i];
   KX + B = Y;
*/
