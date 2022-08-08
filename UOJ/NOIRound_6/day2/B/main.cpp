#include "tree.h"
#include <vector>
#include <cctype>
#include <cstdio>
#include <random>
#include <cstring>
#include <algorithm>

using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 2010;

i32 G[N][N], insame[2][N][N];
std::random_device srd;
std::mt19937 rd(srd());

std::vector<std::pair<int, int>> solve(int n)
{
	std::vector<PII> edge;
	vi32 q(n - 1);
	for (int i = 0; i < n - 1; ++i) {
		q[i] = 1;
		auto t = query(q);
		q[i] = 0;
		for (auto vec : t) {
			if (vec.size() != 1)
				edge.emplace_back(vec[0], vec[1]);
		}
	}
	return edge;
}
