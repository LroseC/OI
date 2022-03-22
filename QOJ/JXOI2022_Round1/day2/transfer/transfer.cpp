#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

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

using i64 = long long;

const int N = 1e5 + 10;

int n, m, K;
i64 ans = LLONG_MAX;
int S[N];
int Cnt[30][30];
int a[N], pos[N];
bool vis[N];

double factor(int x)
{
	double res = 1;
	for (int i = 1; i <= x; ++i)
		res *= x;
	return res;
}

void dfs(int id);

i64 getAns(int id)
{
	i64 res = 0;
	for (int i = 1; i < id; ++i) {
		res += 1ll * Cnt[a[id]][a[i]] * (i + id) * K;
		res += 1ll * Cnt[a[i]][a[id]] * (id - i);
	}
	for (int i = id + 1; i <= m; ++i) {
		res += 1ll * Cnt[a[id]][a[i]] * (i - id);
		res += 1ll * Cnt[a[i]][a[id]] * (i + id) * K;
	}
	return res;
}
int myrand(int l, int r) { return rand() % (r - l + 1) + l; }
void sa(void)
{
	i64 res = 0;
	for (int i = 1; i <= m; ++i) {
		a[i] = i;
		res += getAns(i);
	}
	ans = std::min(ans, res);
	for (double T = 1e8; T >= 1e-8; T *= 0.99999) {
		int l = myrand(1, m), r = myrand(1, m);
		int tl = a[l], tr = a[r];
		if (l == r) continue;
		i64 delta = res;
		res -= getAns(l);
		a[l] = 0;
		res -= getAns(r);
		a[r] = tl;
		res += getAns(r);
		a[l] = tr;
		res += getAns(l);
		delta = res - delta;
		ans = std::min(ans, res);
		if (1.0 * rand() / RAND_MAX > std::exp(-delta / T)) {
			res -= getAns(l);
			a[l] = 0;
			res -= getAns(r);
			a[r] = tr;
			res += getAns(r);
			a[l] = tl;
			res += getAns(l);
		}
//		for (int i = 1; i <= m; ++i)
//			printf("%d ", a[i]);
//		puts("");
//		printf("res = %lld\n", res);
	}
}

int main(void)
{
//	freopen("transfer.in", "r", stdin);
//	freopen("transfer.out", "w", stdout);
	read >> n >> m >> K;
	for (int i = 1; i <= n; ++i)
		read >> S[i];
	if (factor(m) * n <= 1e8) {
		dfs(1);
		printf("%lld\n", ans);
	}
	else {
		for (int i = 1; i < n; ++i)
			++Cnt[S[i]][S[i + 1]];
		while (1.0 * clock() / CLOCKS_PER_SEC < 0.9)
			sa();
		printf("%lld\n", ans);
	}
	return 0;
}

void dfs(int id)
{
	if (id > m) {
		for (int i = 1; i <= m; ++i)
			pos[a[i]] = i;
		i64 res = 0;
		for (int i = 1; i < n; ++i) {
			if (pos[S[i + 1]] >= pos[S[i]])
				res += pos[S[i + 1]] - pos[S[i]];
			else
				res += (pos[S[i]] + pos[S[i + 1]]) * K;
		}
		ans = std::min(res, ans);
		return;
	}
	for (int i = 1; i <= m; ++i)
		if (!vis[i]) {
			a[id] = i;
			vis[i] = 1;
			dfs(id + 1);
			vis[i] = 0;
		}
}
