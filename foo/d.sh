#!/bin/bash

# Check if input file argument is provided
if [ $# -lt 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

INPUT_FILE="$1"

# Auto-detect the first .cpp file in the current folder
CPP_FILE="demo.cpp"

if [ -z "$CPP_FILE" ]; then
    echo "No .cpp file found in the current directory."
    exit 1
fi

OUTPUT_FILE="a.exe"

# Compile the C++ file with the given flags
g++ -std=c++17 -I /mnt/c/Users/Mutammim/Desktop/cp_vscode/DEBUG -DLOCAL -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG "$CPP_FILE" -o "$OUTPUT_FILE"
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Start logging to output.txt
{
    echo -e "\nInput: "
    cat "$INPUT_FILE"
    echo -e "Output: "
    # Run the compiled executable with the input file
    ./"$OUTPUT_FILE" < "$INPUT_FILE"
    echo ""
} | tee output.txt
