#!/bin/bash
g++ delivery.cpp -Wall -Wextra -Wshadow -fsanitize=undefined,address,signed-integer-overflow -DDEBUG
