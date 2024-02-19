#!/bin/bash

# Access command line arguments
cppFileToCompile=$1

# Remove .cpp extension from file name
fileOutName="${cppFileToCompile%.cpp}"

# compile with cpp 20
g++ ./$cppFileToCompile -o $fileOutName -std=c++20

#run compiled prog
./$fileOutName