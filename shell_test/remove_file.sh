#!/bin/bash
# in order to delete specific file.

if [[ $# -eq 0 ]]; then
    echo "please input argument: such as xxx.pyc"
    exit
fi
# if [[ -e $1 ]]; then
#     if [[ -d $1 ]]; then
#         echo "this is a directory file"
#         find -name $1 | echo

#     elif [[ -f $1 ]]; then
#         echo "this is an ordinary file"
#         find -name "$1"
#     else
#         echo "this is an other file"
#     fi
# else
#     echo "do nothing"
#     find -name "$1"
# fi
# find -name "*.pyc" | xargs rm -f
# echo "do nothing"
find -name "$1" | xargs rm -rf
# bash $2