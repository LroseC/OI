#include <cstdio>
#include <cstdlib>

int main(void)
{
	system("g++ main.cpp -o main -O2");
	system("g++ brute.cpp -o brute -O2");
	system("g++ rand.cpp -o rand -O2");
	for (int T = 1; T <= 1000; ++T) {
		system("./rand > test.in");
		system("./brute < test.in > test.ans");
		system("./main < test.in > test.out");
		if (system("diff test.out test.ans")) {
			fprintf(stderr, "Wa on #%d\n", T);
			return -1;
		}
		fprintf(stderr, "AC on #%d\n", T);
	}
	return 0;
}
