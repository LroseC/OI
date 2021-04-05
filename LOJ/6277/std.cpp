#include <cstdio>
#include <cmath>

using namespace std;

#define ll long long
const int N = 50010;

int n, len;
int id[N], a[N], b[N];

void add(int l, int r, int x)
{
	int lid = id[l], rid = id[r];
	if (lid == rid) {
		for (int i = l; i <= r; ++i) a[i] += x;
		return;
	}
	for (int i = l; id[i] == lid; ++i) a[i] += x;
	for (int i = lid + 1; i < rid; ++i) b[i] += x;
	for (int i = r; id[i] == rid; --i) a[i] += x;
}
int main()
{
	scanf("%d", &n);
	len = sqrt(n);

	for (int i = 0; i < n; ++i) {
		scanf("%d\n", &a[i]);
		id[i] = i / len;
	}
	int opt, l, r, c;
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d%d", &opt, &l, &r, &c);
		if (opt) printf("%d\n", a[r - 1] + b[id[r - 1]]);
		else add(l - 1, r - 1, c);
	}
	return 0;
}
