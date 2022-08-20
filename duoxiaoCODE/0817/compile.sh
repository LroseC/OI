#!/bin/bash
g++ template.cpp -Wall -Wextra -Wshadow -fsanitize=undefined,address,signed-integer-overflow -DDEBUG
