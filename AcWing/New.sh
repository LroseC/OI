#!/bin/bash
read last < ./New
git add ./$last
git commit -m "AcWing_$last"
read name
echo $name > New
mkdir $name
touch ./$name/main.cpp
cd $name