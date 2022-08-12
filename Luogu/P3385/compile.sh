#!/bin/bash
g++ main.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined
