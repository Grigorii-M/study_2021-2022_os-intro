#!/bin/bash

numToCreate=0
shouldCreate=0
shouldDelete=0

while getopts c:d opts; do
  case $opts in
    c)  shouldCreate=1; numToCreate=$OPTARG;;
    d)  shouldDelete=1;;
    *) echo Illegal argument in $opts;;
  esac
done

if [ $shouldCreate == 1 ]; then
  mkdir ~/files
  for i in $(seq 1 $numToCreate); do
    touch ~/files/file${i}.txt
  done
elif [ $shouldDelete == 1 ]; then
  rm -R ~/files
fi
