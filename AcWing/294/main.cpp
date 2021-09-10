#include <string>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;
const int N = 110, M = 30;

int sz;
LL f[N][M];
int n1, n2;
string s1, s2;

int main(void)
{
	while (cin >> s2 >> n2 >> s1 >> n1) {
		bool flag = 0;

		sz = s1.size();
		for (int i = 0; i < sz; ++i) {
			f[i][0] = 0;
			int p = i;
			for (int j = 0; j < s2.size(); ++j) {
				int cnt = 0;
				while (s1[p] != s2[j]) {
					++cnt;
					p = (p + 1) % sz;
					if (cnt > sz) {
						flag = 1;
						break;
					}
				}
				if (flag) break;
				p = (p + 1) % sz;
				f[i][0] += cnt + 1;
			}
			if (flag) break;
		}

		if (flag) {
			cout << 0 << '\n';
			continue;
		}

		for (int j = 1; j < M; ++j)
			for (int i = 0; i < sz; ++i)
				f[i][j] = f[i][j - 1] + f[(i + f[i][j - 1]) % sz][j - 1];
		
		LL res = 0;
		for (int i = 0; i < sz; ++i) {
			LL p = i, t = 0;
			for (int j = M - 1; j >= 0; --j)
				if (p + f[p % sz][j] <= 1ll * sz * n1) {
					p += f[p % sz][j];
					t += 1 << j;
				}
			res = max(res, t);
		}
		cout << res / n2 << '\n';
	}
	return 0;
}