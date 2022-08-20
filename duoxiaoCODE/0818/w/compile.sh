#!/bin/bash
g++ w.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined,signed-integer-overflow -DDEBUG
