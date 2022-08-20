#!/bin/bash
g++ tree.cpp -Wall -Wextra -Wshadow -fsanitize=undefined,address,signed-integer-overflow -DDEBUG
