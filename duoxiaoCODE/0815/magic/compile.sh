#!/bin/bash
g++ magic.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG
