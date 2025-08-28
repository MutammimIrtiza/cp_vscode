#!/bin/bash

# Loop through all files named in, in1, in2, ...
for INPUT_FILE in in in[0-9]*; do
    if [ -f "$INPUT_FILE" ]; then
        echo ""
        echo "Input: $INPUT_FILE"
        cat "$INPUT_FILE"

        echo "Output:"
        ./a.exe < "$INPUT_FILE"
        echo ""
    fi
done
