#!/bin/bash
g++ exit.cpp -o exitNum
./exitNum

num=$?

if [ $num = 2 ]; then
  echo Number \> 0
elif [ $num = 1 ]; then
  echo Number = 0
elif [ $num = 0 ]; then
  echo Number \< 0
fi
