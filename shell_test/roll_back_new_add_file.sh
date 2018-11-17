#!/bin/bash

content=`git status`
git status > test.txt
# echo ${content}
# for line in `git status`; do
#     #statements
#     echo "${line}"
# done

git status | grep "new file:" | awk '{print $3}' | while read lines; do
    #statements
    # git reset ${lines}
    
    echo "reset ${lines} is ok!!"

done