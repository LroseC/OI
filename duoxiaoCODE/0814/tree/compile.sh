#!/bin/bash
g++ tree.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG -std=c++11
