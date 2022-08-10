#!/bin/bash
read name
mkdir $name
cp ./template.cpp ./$name/main.cpp
cp ./compile.sh ./$name/
