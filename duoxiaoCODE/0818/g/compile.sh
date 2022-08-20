#!/bin/bash
g++ g.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined,signed-integer-overflow -DDEBUG
