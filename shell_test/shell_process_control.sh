#!/bin/bash
# to test process control

# if test
a=2
if [[ a -lt 4 ]]; then
    echo "a < 4"
else
    echo "a >= 4"
fi

# for test
num=1
for (( i = 0; i < 10; i++ )); do
    echo "num"${num}
    let "num++"
done

arr_num=(1 2 3 4 5 6 7 8)
for i in arr_num; do
    echo "the num is "${i}
done

# while test
index=6
while [[ index -ge 3 ]]; do
    #statements
    echo "index:${index}"
    let "index--"
done

# until test
until [[ index -eq 8 ]]; do
    #statements
    echo "this is ok"
    index=`expr ${index} + 1`
done

# case test
while true; do
    #statements
    echo "input num from 1 to 8"
    read num
    case ${num} in
        1)
            echo "you input 1"
            ;;
        2)
            echo "you input 2"
            ;;
        3)
            echo "you input 3"
            ;;
        4)
            echo "you input 4"
            ;;
        5)
            echo "you input 5"
            ;;
        6)
            continue
            echo "you input 6"
            ;;
        7)
            echo "you input 7"
            continue
            ;;
        8)
            break


    esac
done