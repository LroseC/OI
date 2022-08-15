#!/bin/bash
g++ splay.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG
