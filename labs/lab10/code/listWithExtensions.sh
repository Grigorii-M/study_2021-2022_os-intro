#!/bin/bash
extension_to_find=$1
extension_to_find=${extension_to_find:1}
search_dir=$2
for entry in "$search_dir"/*
do
  filename=$(basename -- "$entry")
  file_extension="${filename#*.}"
  if [ "$extension_to_find" == "$file_extension" ]; then
    echo $filename
  fi
done
