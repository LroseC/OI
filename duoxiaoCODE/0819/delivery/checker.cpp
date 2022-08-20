#include <cstdio>
#include <cstdlib>

int main(void)
{
	system("g++ delivery.cpp -O2 -fsanitize=address,undefined,signed-integer-overflow -DDEBUG -o main");
	system("g++ brute.cpp -O2 -fsanitize=address,undefined,signed-integer-overflow -DDEBUG -o brute");
	system("g++ rand.cpp -O2 -o rand");
	for (int T = 1; T <= 1000; ++T) {
		fprintf(stderr, "Test #%d\n", T);
		system("./rand > test.in");
		system("./main < test.in > test.out");
		system("./brute < test.in > test.ans");
		if (system("diff test.out test.ans")) {
			fprintf(stderr, "WA\n");
			return -1;
		}
		fprintf(stderr, "Accepted.\n");
	}
	return 0;
}
