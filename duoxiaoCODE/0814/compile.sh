#!/bin/bash
g++ template.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG -std=c++11
