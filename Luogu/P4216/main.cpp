#include <cctype>
#include <cstdio>
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

int root;

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> fa[i][0];
		if (!fa[i][0]) root = i;
	}
	getFa(root);

	read >> m;
	for (int tim = 1; tim <= m; ++tim) {
		int op; read >> op;
		if (op == 1) {
			int u, v, c;
			read >> u >> v >> c;
			q.emplace_back(u, v, tim - c - 1);
		}
		else {
			int u; read >> u;
			cg.emplace_back(u, tim);
		}
	}
	std::sort(q.begin(), q.end());
	std::sort(cg.begin(), cg.end());
	int i = 0, j = 0;
	for (int tim = 1; tim <= m; ++tim) {
		if (j < cg.size() && cg[i].tim == tim)
			color(cg.u);
		while (i < q.size() && q[i].tim == tim) {
		}
	}
	return 0;
}
