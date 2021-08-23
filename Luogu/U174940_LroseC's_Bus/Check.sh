#!/bin/bash

g++ test.cpp -o test

for ((i=7;i<=8;++i))
do
	./test < test$i.in > test$i.ans
	diff test$i.out test$i.ans
done

rm test