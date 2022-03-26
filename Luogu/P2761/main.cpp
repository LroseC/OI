#include <queue>
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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int M = 110, S = 1 << 20;

int n, m;
int w[M];
int B1[M], B2[M], F1[M], F2[M];
int dis[S], INF;
bool inque[S];
char str1[100], str2[100];

int SPFA(void)
{
	std::queue<int> q;
	memset(dis, 0x3f, sizeof dis);
	memset(&INF, 0x3f, sizeof INF);
	dis[(1 << n) - 1] = 0;
	q.emplace((1 << n) - 1);
	while (q.size()) {
		int u = q.front(); q.pop();
		inque[u] = 0;
		for (int i = 1; i <= m; ++i)
			if ((u & B1[i]) == B1[i] && (u & B2[i]) == 0) {
				int v = u & ((1 << n) - 1 & ~F1[i]);
				v |= F2[i];
				if (dis[v] > dis[u] + w[i]) {
					dis[v] = dis[u] + w[i];
					if (!inque[v]) {
						q.emplace(v);
						inque[v] = 1;
					}
				}
			}
	}
	if (dis[0] == INF) return 0;
	return dis[0];
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		read >> w[i];
		scanf("%s%s", str1, str2);
		for (int j = 0; j < n; ++j) {
			if (str1[j] == '+')
				B1[i] ^= 1 << j;
			if (str1[j] == '-')
				B2[i] ^= 1 << j;
			if (str2[j] == '-')
				F1[i] ^= 1 << j;
			if (str2[j] == '+')
				F2[i] ^= 1 << j;
		}
	}
	printf("%d\n", SPFA());
	return 0;
}