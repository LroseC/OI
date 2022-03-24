#include <vector>
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

const int M = 23, N = 1e5 + 10;
inline int lowbit(int x) { return x & -x; }

int n, m, K;
int S[N];
int Cnt[M][M];
std::vector<int> state[30];
std::vector< std::vector<int> > val[2];

int getCnt(int x)
{
	int res = 0;
	while (x) {
		++res;
		x -= lowbit(x);
	}
	return res;
}

// 1352078

int main(void)
{
	read >> n >> m >> K;
	for (int i = 1; i <= n; ++i)
		read >> S[i];
	for (int i = 1; i < n; ++i)
		++Cnt[S[i]][S[i + 1]];
	for (int i = 0; i < 1 << m; ++i)
		state[getCnt(i)].emplace_back(i);
	for (int i = 0; i <= 23; ++i)
		printf("%d ", state[i].size());
	for (int k = 1; k <= m; ++k) {
		for (int st : state[k])
			for (int i = 0; i < m; ++i)
				val[k & 1][
	}
	return 0;
}
