#!/bin/bash
g++ string.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG
