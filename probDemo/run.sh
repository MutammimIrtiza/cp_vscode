#!/bin/bash

# Check if exactly one argument is given
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

INPUT_FILE="$1"

# Check if input file exists
if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: File '$INPUT_FILE' not found."
    exit 1
fi

# Print input
echo ""
echo "Input:"
cat "$INPUT_FILE"

# Print output
echo "Output:"
./a.exe < "$INPUT_FILE"
echo ""
