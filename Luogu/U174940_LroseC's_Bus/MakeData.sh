#!/bin/bash

g++ rand.cpp -o rand
g++ main.cpp -o std

for ((i=7;i<=8;++i))
do
	./rand > test$i.in
	./std < test$i.in > test$i.out
done

rm rand std
