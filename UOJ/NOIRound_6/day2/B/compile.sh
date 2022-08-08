#!/bin/bash
g++ main.cpp grader.cpp -Wall -Wextra -Wshadow -fsanitize=address,undefined
