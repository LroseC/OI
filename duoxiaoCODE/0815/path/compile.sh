#!/bin/bash
g++ path.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG
