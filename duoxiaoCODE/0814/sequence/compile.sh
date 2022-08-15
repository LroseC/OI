#!/bin/bash
g++ sequence.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG -std=c++11
