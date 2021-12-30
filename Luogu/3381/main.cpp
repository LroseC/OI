#include <cctype>
#include <cstdio>

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
} IO;

int n, m, S, T;
int idx = 1, head[N], nex[M], to[M], w[M], c[M];

void AddEdge(int u, int v, int wi, int ci)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, w[idx] = wi, c[idx] = ci;
}

int main(void)
{
	IO >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, wi, ci; IO >> u >> v >> wi >> ci;
		AddEdge(u, v, wi, ci);
		AddEdge(v, u, -wi, 0);
	}
	S = N - 1, T = N - 2;
	printf("%d\n", Dinic::main());
	return 0;
}
