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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 1e5 + 10;

struct Query
{
	int id, l, r;

	bool operator<(const Query &other)
	{
		if (r != other.r) return r < other.r;
		return l < other.l;
	}
};

int n, m;
char str[N];
int pos[40];
i64 ans[N];
int idx;
int tim[N * 40];
int ch[N * 40][2];
Query q[N];

void insert(char str[], int id)
{
	int u = 0;
	for (int i = 0; i < 35 && id + i <= n; ++i) {
		int now = str[i] - '0';
		if (!ch[u][now])
			ch[u][now] = ++idx;
		u = ch[u][now];
		pos[i + 1] = std::max(pos[i + 1], tim[u]);
		tim[u] = id;
	}
}

int main(void)
{
	read >> n >> m;
	scanf("%s", str + 1);
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(q + 1, q + 1 + m);
	int R = 0;
	for (int i = 1; i <= m; ++i) {
		while (R < q[i].r) {
			++R;
			insert(str + R, R);
		}
		i64 res = 0;
		for (int j = 1; j <= 35; ++j)
			if (pos[j] >= q[i].l)
				res += 1ll * j * (pos[j] - std::max(q[i].l - 1, pos[j + 1]));
		ans[q[i].id] = res;
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
