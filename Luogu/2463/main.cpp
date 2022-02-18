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

const int N = 1100000;

int n, m, q;
int id[N], tmp[N], str[N];
int sa[N], rk[N], height[N], x[N << 1], y[N << 1], c[N];

void buildSA(void)
{
	m = 100010;
	for (int i = 1; i <= n; ++i) ++c[x[i] = str[i]];
	for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
	for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++num] = sa[i] - k;

		for (int i = 0; i <= m; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) ++c[x[i]];
		for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

		swap(x, y);
		num = 1, x[sa[1]] = 1;
		for (int i = 2; i <= n; ++i)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
		if (num == n) break;
		m = num;
	}
	for (int i = 1; i <= n; ++i)
		rk[sa[i]] = i;
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) continue;
		if (k) --k;
		int j = sa[rk[i] - 1];
		while (i + k <= n && j + k <= n && str[i + k] == str[j + k])
			++k;
		height[rk[i]] = k;
	}
}


bool vis[N];
int stk[N], top;
void clear(void)
{
	while (top)
		vis[stk[top--]] = 0;
}
void insert(int i)
{
	if (id[sa[i]] && !vis[id[sa[i]]]) {
		vis[id[sa[i]]] = 1;
		stk[++top] = id[sa[i]];
	}
}
bool check(int len)
{
	clear();
	for (int i = 1; i <= n; ++i) {
		if (height[i] < len)
			clear();
		insert(i);
		if (top == q) return 1;
	}
	return 0;
}

int main(void)
{
	read >> q;
	for (int i = 1; i <= q; ++i) {
		int len; read >> len;
		for (int j = 1; j <= len; ++j)
			read >> tmp[j];
		for (int j = len; j >= 2; --j)
			tmp[j] = tmp[j] - tmp[j - 1];
		for (int j = 2; j <= len; ++j) {
			str[++n] = tmp[j] + 2e4;
			id[n] = i;
		}
		str[++n] = 1e5;
	}

	buildSA();
//	for (int i = 1; i <= n; ++i)
//		printf("%d ", str[i]);
//	puts("");
//	for (int i = 1; i <= n; ++i)
//		printf("%d ", rk[i]);
//	puts("");
//	for (int i = 1; i <= n; ++i)
//		printf("%d ", height[i]);
//	puts("");

	int l = 0, r = 100;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(mid)) l = mid;
		r = mid - 1;
	}
	printf("%d\n", l + 1);
	return 0;
}
