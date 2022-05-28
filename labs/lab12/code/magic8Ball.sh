#!/bin/bash

wordSize=$(( $RANDOM % 30 + 1 ))
chars=abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ

for ((i=0; i<wordSize;i++)); do
  echo -n "${chars:RANDOM%${#chars}:1}"
done
echo
