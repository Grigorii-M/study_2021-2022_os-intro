#!/bin/bash
directory=$1
find $directory -mtime -7 | tar -cf compress.tar $directory
