#!/bin/bash
search_dir=$1
for entry in "$search_dir"/*
do
  echo $(basename -- "$entry") $(stat -c %A "$entry")
done
