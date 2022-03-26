#include <bits/stdc++.h>

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
} myread;

using i64 = long long;
const int N = 5e5 + 10, LG = 20;

int n, m;
int stk[N], top;
int a[N], b[N];
int nex[N][LG];
int last[N];
int st[N][LG];
int lg2[N];
int Link[N];

void build(void)
{
	lg2[1] = 0;
	for (int i = 2; i <= n; ++i)
		lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; i <= n; ++i)
		st[i][0] = b[i];
	for (int j = 1; j < LG; ++j)
		for (int i = 1; i <= n; ++i)
			st[i][j] = std::max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
}
int query(int l, int r)
{
	int t = lg2[r - l + 1];
	return std::max(st[l][t], st[r - (1 << t) + 1][t]);
}

int main(void)
{
//	freopen("stack.in", "r", stdin);
//	freopen("stack.out", "w", stdout);
	myread >> n >> m;
	for (int i = 1; i <= n; ++i)
		myread >> a[i];
	bool flag = 1;
	for (int i = 1; i <= n; ++i) {
		myread >> b[i];
		if (b[i] != n - i + 1)
			flag = 0;
	}
//	if (flag) {
//		for (int i = 1; i <= m; ++i)
//			puts("1");
//		return 0;
//	}
//	if (n <= 1000 && m <= 1000) {
//		for (int i = 1; i <= m; ++i) {
//			int res = 0;
//			int top = 0;
//			int l, r; myread >> l >> r;
//			for (int j = l; j <= r; ++j) {
//				while (top && (a[j] == a[stk[top]] || b[j] >= b[stk[top]]))
//					--top;
//				if (top == 0)
//					++res;
//				stk[++top] = j;
//			}
//			printf("%d\n", res);
//		}
//	}
//	else {
		build();
		stk[++top] = n;
		last[a[n]] = n;
		for (int i = n - 1; i >= 1; --i) {
			while (top && b[i] >= b[stk[top]])
				--top;
			Link[i] = last[a[i]];
			while (Link[i]) {
				if (query(i + 1, Link[i]) <= b[Link[i]])
					break;
				Link[i] = Link[Link[i]];
			}
			if (last[a[i]] && top)
				nex[i][0] = std::min(last[a[i]], stk[top]);
			else nex[i][0] = stk[top] + last[a[i]];
			last[a[i]] = i;
			stk[++top] = i;
		}
		for (int i = 1; i <= n; ++i)
			printf("%d ", Link[i]);
		for (int j = 1; j < LG; ++j)
			for (int i = 1; i <= n; ++i)
				nex[i][j] = nex[nex[i][j - 1]][j - 1];

		for (int i = 1; i <= m; ++i) {
			int l, r; myread >> l >> r;
			int res = 1;
			for (int j = LG - 1; j >= 0; --j)
				if (nex[l][j] && nex[l][j] <= r) {
					res += 1 << j;
					l = nex[l][j];
				}
			printf("%d\n", res);
		}
//	}
	return 0;
}
