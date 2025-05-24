#!/bin/sh

# Check if both arguments are provided
if [ $# -ne 2 ]; then
    echo "Error: Invalid number of arguments."
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

filesdir="$1"
searchstr="$2"

# Check if filesdir exists and is a directory
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir is not a valid directory."
    exit 1
fi

# Find the number of files in the directory and subdirectories
file_count=$(find "$filesdir" -type f | wc -l)

# Find the number of matching lines across all files
line_count=$(grep -r "$searchstr" "$filesdir" | wc -l)

# Print the results
echo "The number of files are $file_count and the number of matching lines are $line_count"

exit 0
