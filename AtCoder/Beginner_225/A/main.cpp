#include <set>
#include <cstdio>
#include <string>

using namespace std;

char str[10];
set<string> S;

int main(void)
{
	scanf("%s", str + 1);
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j)
			if (j != i)
				for (int k = 1; k <= 3; ++k)
					if (k != j && k != i) {
						string tmp;
						tmp.push_back(str[i]);
						tmp.push_back(str[j]);
						tmp.push_back(str[k]);
						S.insert(tmp);
					}
	printf("%d\n", S.size());
	return 0;
}