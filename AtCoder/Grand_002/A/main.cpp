#include <cctype>
#include <cstdio>

using namespace std;

struct FastStreamInput
{
	using FSI = FastStreamInput;
	template<typename T>
	FSI& operator >> (T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} cin;

int a, b;

int main(void)
{
	cin >> a >> b;
	if (a > 0) puts("Positive");
	else if (b > 0) puts("Zero");
	else puts((b - a) & 1 ? "Positive" : "Negative");
	return 0;
}