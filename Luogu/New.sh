#!/bin/bash
read last < ./test.bk
git add ./$last
git commit -m "Luogu_$last"
read name
echo $name > New
mkdir $name
touch ./$name/main.cpp
cd $name