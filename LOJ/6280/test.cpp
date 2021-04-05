#include <cmath>
#include <cstdio>

using namespace std;

#define ll long long
const int N = 5e4 + 10;

int n, T;
int id[N];
ll a[N], sum[N], b[N];

void build();
void add(int, int, int);
int query(int, int, int);

int main()
{
	scanf("%d\n", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld\n", &a[i]);
	
	T = sqrt(n);
	build();

	int opt, l, r, c;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &opt, &l, &r, &c);
		if (opt)
			printf("%d\n", query(l, r, c + 1));
		else
			add(l, r, c);
	}
	return 0;
}
void build()
{
	for (int i = 1; i <= n; ++i) {
		id[i] = (i - 1) / T + 1;
		sum[id[i]] += a[i];
	}
}
void add(int l, int r, int c)
{
	int lid = id[l], rid = id[r];
	if (lid == rid) {
		for (int i = l; i <= r; ++i) a[i] += c, sum[lid] += c;
		return;
	}
	for (int i = l; id[i] == lid; ++i) a[i] += c, sum[lid] += c;
	for (int i = lid + 1; i < rid; ++i) b[i] += c, sum[lid] += c * T;
	for (int i = r; id[i] == rid; --i) a[i] += c, sum[rid] += c;
}
int query(int l, int r , int mod) {
	int lid = id[l], rid = id[r];
	ll ans = 0;
	if (lid == rid) {
		for (int i = l; i <= r; ++i) ans = (ans + a[i] + b[lid]) % mod;
		return ans;
	}
	for (int i = l; id[i] == lid; ++i) ans = (ans + a[i] + b[lid]) % mod;
	for (int i = lid + 1; i < rid; ++i) ans = (ans + sum[i]) % mod;
	for (int i = r; id[i] == rid; --i) ans = (ans + a[i] + b[lid]) % mod;
	return ans;
}
