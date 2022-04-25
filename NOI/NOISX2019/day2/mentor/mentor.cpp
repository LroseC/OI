#include <cctype>
#include <cstdio>
#include <cstring>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int mod = 998244353, N = 1010;

int n, K, res, c;
int C0, C1, D0, D1;
int C[2], D[2];
int zhenying[N], zhandui[N];
int belong[N], cnt[N], p[N];

void dfs(int id)
{
	if (id > n) {
		if (C[0] <= C0 && C[1] <= C1 && D[0] <= D0 && D[1] <= D1)
			++res;
		return;
	}
	if (zhenying[belong[id]] == -1) {
		for (int i = 0; i < 2; ++i) {
			zhenying[belong[id]] = i;
			dfs(id);
			zhenying[belong[id]] = -1;
		}
		return;
	}
	for (int i = 0; i < 2; ++i) {
		int tmp = zhenying[belong[id]] << 1 | i;
		if (p[id] == tmp) continue;
		zhandui[id] = tmp;
		C[zhenying[belong[id]]] += cnt[id];
		D[i] += cnt[id];
		dfs(id + 1);
		D[i] -= cnt[id];
		C[zhenying[belong[id]]] -= cnt[id];
		zhandui[id] = 0;
	}
}

int main(void)
{
	freopen("mentor.in", "r", stdin);
	freopen("mentor.out", "w", stdout);
	int T; read >> T;
	while (T--) {
		std::memset(p, -1, sizeof p);
		std::memset(zhenying, -1, sizeof zhenying);
		res = 0;
		read >> n >> c;
		read >> C0 >> C1 >> D0 >> D1;
		for (int i = 1; i <= n; ++i)
			read >> belong[i] >> cnt[i];
		read >> K;
		for (int i = 1, id; i <= K; ++i)
			read >> id >> p[id];
		dfs(1);
		printf("%d\n", res);
	}
	return 0;
}
