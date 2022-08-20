#!/bin/bash
g++ graph.cpp -Wall -Wextra -Wshadow -fsanitize=undefined,address,signed-integer-overflow -DDEBUG
