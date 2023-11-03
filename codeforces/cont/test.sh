#!/bin/sh
g++ -static -D LOCAL_TEST_ENVIRONMENT=1 -DONLINE_JUDGE -W -O2 -std=c++14 -o runTest cpptest.cpp
./runTest
