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

const int N = 40010, BLEN = 250, B = 210;

int n, m;
int L[BLEN], R[BLEN], id[N];
int type[N], blockRes[BLEN][BLEN], blockCnt[BLEN][N];
int cnt[N];

void build(void)
{
	for (int i = 1, idx = 1; i <= n; i += B, ++idx) {
		L[idx] = i, R[idx] = std::min(n, i + B - 1);
		for (int j = L[idx]; j <= R[idx]; ++j)
			id[j] = idx;
	}
	for (int i = 1; i <= id[n]; ++i) {
		int res = 0;
		for (int j = i; j <= id[n]; ++j) {
			for (int k = L[j]; k <= R[j]; ++k) {
				++cnt[type[k]];
				if (cnt[type[k]] > cnt[res] || (cnt[type[k]] == cnt[res] && type[k] < res))
					res = type[k];
			}
			blockRes[i][j] = res;
		}
		std::memset(cnt, 0, sizeof cnt);
	}
	for (int i = 1; i <= id[n]; ++i) {
		for (int j = L[i]; j <= R[i]; ++j)
			++cnt[type[j]];
		std::memcpy(blockCnt[i], cnt, sizeof cnt);
	}
	std::memset(cnt, 0, sizeof cnt);
}
int query(int L, int R)
{
	if (id[R] - id[L] <= 1) {
		int res = 0;
		for (int i = L; i <= R; ++i) {
			++cnt[type[i]];
			if (cnt[type[i]] > cnt[res] || (cnt[type[i]] == cnt[res] && type[i] < res))
				res = type[i];
		}
		for (int i = L; i <= R; ++i)
			--cnt[type[i]];
		return res;
	}
	else {
		int res = blockRes[id[L] + 1][id[R] - 1];
		auto Getcnt = [L, R](int x) { return cnt[x] + blockCnt[id[R] - 1][x] - blockCnt[id[L]][x]; };
		for (int i = L; id[i] == id[L]; ++i) {
			++cnt[type[i]];
			if (Getcnt(type[i]) > Getcnt(res) || (Getcnt(type[i]) == Getcnt(res) && type[i] < res))
				res = type[i];
		}
		for (int i = R; id[i] == id[R]; --i) {
			++cnt[type[i]];
			if (Getcnt(type[i]) > Getcnt(res) || (Getcnt(type[i]) == Getcnt(res) && type[i] < res))
				res = type[i];
		}
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
	int lastans = 0;
	for (int i = 1; i <= m; ++i) {
		int l, r; read >> l >> r;
		l = (l + lastans - 1) % n + 1;
		r = (r + lastans - 1) % n + 1;
		if (l > r) std::swap(l, r);
		printf("%d\n", lastans = nums[query(l, r) - 1]);
	}
	return 0;
}
