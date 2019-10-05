#!/bin/bash
a=(A1 "B2" 'C3')
a[2]=CC
echo "the length is ${#a[*]}"
echo "${a[0]} ${a[2]}"
echo "${a[@]}"
