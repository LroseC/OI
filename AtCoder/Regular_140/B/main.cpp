#include <set>
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
const int N = 2e5 + 10;

int n;
char str[N];
int cntA[N], cntC[N];
std::multiset<int> ARC;

bool check(char str[])
{ return str[0] == 'A' && str[1] == 'R' && str[2] == 'C'; }
int main(void)
{
	read >> n;
	scanf("%s", str + 1);
	for (int i = 1; i <= n; ++i)
		if (str[i] == 'A')
			cntA[i] = cntA[i - 1] + 1;
	for (int i = n; i >= 1; --i)
		if (str[i] == 'C')
			cntC[i] = cntC[i + 1] + 1;
	for (int i = 1; i <= n; ++i)
		if (check(str + i))
			ARC.insert(std::min(cntA[i - 1], cntC[i + 3]) + 1);
	int res = 0;
	while (ARC.size()) {
		++res;
		auto t = ARC.end();
		--t;
		int tmp = *t;
		ARC.erase(t);
		if (tmp != 1) ARC.insert(tmp - 1);
		if (!ARC.size()) break;
		++res;
		ARC.erase(ARC.begin());
	}
	printf("%d\n", res);
	return 0;
}
