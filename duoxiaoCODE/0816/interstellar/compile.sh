#!/bin/bash
g++ interstellar.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG
