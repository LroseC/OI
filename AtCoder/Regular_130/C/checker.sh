#!/bin/bash
g++ main.cpp -o main
g++ rand.cpp -o rand
g++ brute.cpp -o brute -O2
g++ gd.cpp -o getdiff
for((i=1;;++i))
do
	echo case $i
	./rand > test.in
	./brute < test.in > test.ans
	./main < test.in > test.out
	if ./getdiff < test.ans > test.out;
	then
		echo AC
	else
		echo WA
		break;
	fi
done