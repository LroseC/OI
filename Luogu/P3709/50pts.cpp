#include <cmath>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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

int B;
const int N = 2e5 + 10, BL = 120;

int n, m;
int type[N];
int L[N], R[N], id[N], cnt[N];
int blockRes[3010][3010];
std::vector<int> pos[N];

void build(void)
{
	for (int i = 1, idx = 1; i <= n; i += B, ++idx) {
		L[idx] = i, R[idx] = std::min(i + B - 1, n);
		for (int j = L[idx]; j <= R[idx]; ++j)
			id[j] = idx;
	}
	for (int i = 1; i <= id[n]; ++i) {
		int res = 0;
		for (int j = i; j <= id[n]; ++j) {
			for (int k = L[j]; k <= R[j]; ++k) {
				++cnt[type[k]];
				if (cnt[type[k]] > cnt[res])
					res = type[k];
			}
			blockRes[i][j] = res;
		}
		std::memset(cnt, 0, sizeof cnt);
	}
	for (int i = 1; i <= n; ++i)
		pos[type[i]].emplace_back(i);
}
int query(int L, int R)
{
	if (id[R] - id[L] <= 1) {
		int res = 0;
		for (int i = L; i <= R; ++i) {
			++cnt[type[i]];
			res = std::max(res, cnt[type[i]]);
		}
		for (int i = L; i <= R; ++i)
			--cnt[type[i]];
		return res;
	}
	else {
		int res = blockRes[id[L] + 1][id[R] - 1];
		auto Getcnt = [L, R](int x) {
			return std::upper_bound(pos[x].begin(), pos[x].end(), R) - std::lower_bound(pos[x].begin(), pos[x].end(), L);
		};
		for (int i = L; id[i] == id[L]; ++i) {
			++cnt[type[i]];
			if (Getcnt(type[i]) > Getcnt(res))
				res = type[i];
		}
		for (int i = R; id[i] == id[R]; --i) {
			++cnt[type[i]];
			if (Getcnt(type[i]) > Getcnt(res))
				res = type[i];
		}
		res = Getcnt(res);
		for (int i = L; id[i] == id[L]; ++i)
			--cnt[type[i]];
		for (int i = R; id[i] == id[R]; --i)
			--cnt[type[i]];
		return res;
	}
}

int main(void)
{
	read >> n >> m;
	B = n == 1 ? 1 : std::max(1, (int)std::sqrt(1.0 * n * n / (1.0 * m * std::log2(n))));
	std::vector<int> nums(n);
	for (int i = 1; i <= n; ++i) {
		read >> type[i];
		nums[i - 1] = type[i];
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		type[i] = std::lower_bound(nums.begin(), nums.end(), type[i]) - nums.begin() + 1;
	build();
	for (int i = 1; i <= m; ++i) {
		int l, r; read >> l >> r;
		printf("%d\n", -query(l, r));
	}
	return 0;
}
