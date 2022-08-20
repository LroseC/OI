#!/bin/bash
g++ s.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined,signed-integer-overflow -DDEBUG
