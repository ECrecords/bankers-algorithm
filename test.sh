#!/bin/bash
echo "Running Test..."
gcc bankers_algo.c -o bin.out
./bin.out < sample_test_case.txt