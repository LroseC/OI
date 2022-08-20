#!/bin/bash
g++ manipulation.cpp -Wall -Wextra -Wshadow -fsanitize=undefined,address,signed-integer-overflow -DDEBUG
