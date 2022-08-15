#!/bin/bash
g++ template.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined -DDEBUG
