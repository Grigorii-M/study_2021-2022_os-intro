#!/bin/bash

inputFile=""
outputFile=""
pattern=""
isCaseSensitive=0
printLineNumbers=0

while getopts i:o:p:Cn optletters; do
  case $optletters in
    i)  inputFile="$OPTARG";;
    o)  outputFile="$OPTARG";;
    p)  pattern="$OPTARG";;
    C)  isCaseSensitive=1;;
    n)  printLineNumbers=1;;
    *) echo Illegal option $optletters; exit;;
  esac
done

if [ -z "$inputFile" ] || [ -z "$outputFile" ] || [ -z "$pattern" ]; then
  echo inputFile, outputFile and pattern are mandatory arguments
  exit
fi

if [ $isCaseSensitive == 1 ] && [ $printLineNumbers == 1 ]; then
  grep $pattern -n $inputFile > $outputFile
elif [ $isCaseSensitive == 1 ] && [ $printLineNumbers == 0 ]; then
  grep $pattern $inputFile > $outputFile
elif [ $isCaseSensitive == 0 ] && [ $printLineNumbers == 1 ]; then
  grep $pattern -i -n $inputFile > $outputFile
else
  grep $pattern -i $inputFile > $outputFile
fi
