#!/bin/bash

# Check if input file argument is provided
if [ $# -lt 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

INPUT_FILE="$1"

# Auto-detect the first .cpp file in the current folder
CPP_FILE=$(ls *.cpp 2>/dev/null | head -n 1)

if [ -z "$CPP_FILE" ]; then
    echo "No .cpp file found in the current directory."
    exit 1
fi

OUTPUT_FILE="a.exe"

# Path to debug.h (adjust if needed)
DEBUG_PATH="/mnt/c/Users/Mutammim/Desktop/cp_vscode/DEBUG"

# Compile the C++ file (release/fast version)
g++ -std=c++17 -I "$DEBUG_PATH" -Wshadow -Wall -O2 -Wno-unused-result "$CPP_FILE" -o "$OUTPUT_FILE"
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Start logging to output.txt
{
    echo -e "\nInput: "
    cat "$INPUT_FILE"
    echo -e "\Output: "
    # Run the compiled executable with the input file
    ./"$OUTPUT_FILE" < "$INPUT_FILE"
    echo ""
} | tee output.txt
