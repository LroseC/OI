#!/bin/bash
g++ luckymoney.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG -std=c++11
