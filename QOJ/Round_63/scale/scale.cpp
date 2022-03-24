#include <cctype>
#include <cstdio>

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

struct Query
{
	int op;
	int x, y;
};
const int N = 3e5 + 10, LG = 20;

int n, m;
int height[N];
int nex[N][LG];
Query q[N];
int stk[N], top;

int main(void)
{
//	freopen("scale.in", "r", stdin);
//	freopen("scale.out", "w", stdout);
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> height[i];
	bool flag = 1;
	for (int i = 1; i <= m; ++i) {
		read >> q[i].op >> q[i].x >> q[i].y;
		if (q[i].op == 1)
			flag = 0;
	}
	if (flag) {
		for (int i = n; i >= 1; --i) {
			while (top && height[i] >= height[stk[top]])
				--top;
			nex[i][0] = stk[top];
			stk[++top] = i;
		}
		for (int k = 1; k < LG; ++k)
			for (int i = 1; i <= n; ++i)
				nex[i][k] = nex[nex[i][k - 1]][k - 1];
		for (int i = 1; i <= m; ++i) {
			int l = q[i].x, r = q[i].y;
			int res = 1;
			for (int k = LG - 1; k >= 0; --k)
				if (nex[l][k] && nex[l][k] <= r) {
					res += 1 << k;
					l = nex[l][k];
				}
			printf("%d\n", res);
		}
	}
	else {
		for (int i = 1; i <= m; ++i) {
			if (q[i].op == 1)
				height[q[i].x] = q[i].y;
			else {
				int now = q[i].x;
				int res = 1;
				for (int j = q[i].x + 1; j <= q[i].y; ++j)
					if (height[j] > height[now]) {
						++res;
						now = j;
					}
				printf("%d\n", res);
			}
		}
	}
	return 0;
}
