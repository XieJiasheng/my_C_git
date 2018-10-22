#!/bin/bash
# to test function

fun_test(){
    for (( i = 1; i <= $#; i++ )); do
        num=`eval 'echo ${'${i}'}'`
        # echo '--------------------------'${num}
        printf "the parameter %d is %s\n" $i "${num}"
        # printf "show %s\n" $2
    done
    return $$
}


fun_test 1 2 3
fun_test 34 5435 jkjkf
fun_test e 43 534

fun_test aa bb ee ff gg hh ii jj kk ll mm oo pp qq