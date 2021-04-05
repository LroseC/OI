#!/bin/bash
g++ std.cpp -o std
g++ rand.cpp -o rand
for ((i=1;i<=10;++i))
do
	./rand > test$i.in
	./std < test$i.in > test$i.out
done
