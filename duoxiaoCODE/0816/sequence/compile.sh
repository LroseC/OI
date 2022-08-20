#!/bin/bash
g++ sequence.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG
