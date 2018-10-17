#!/bin/bash
# to test shell variable 

your_name="luccy"
age=21
# the double quotes usage
echo "your name is ${your_name}"
echo "your age is ${age}\""
#get the length of string
echo "the length of name is ${#your_name}"
echo "the substring of name is ${your_name:1:3}"
# the single quotes usage
person_info='name is '${your_name}', age is '${age}
echo ${person_info}
# back quotes usage
for file_info in `ls `; do
    echo 'the file information is '${file_info}
done

:<<doc
this is a comment1
this is a comment2
doc

:<<!
this is a comment3
this is a comment4
!

:<<test
this is a comment5
this is a comment6
test

# find substring index
string="hello world"
echo `expr index "${string}" ed`
# find substring
echo `expr substr "${string}" 7 11`

# array
array_num=("one" "two" "three")
array_num[3]="four"
array_num[5]="six"
echo "all value of array:${array_num[@]}"
echo "length of array:${#array_num[*]}"
echo "one of array:${array_num[3]}"
echo "one of array:${array_num[4]}"

# parameter passing
i=0
for param in $@; do
    echo "param:$param"
done
unset i
echo 'all param:'${*}
echo 'all param:'${@}
echo 'last process id:'${!}
echo "param num is ${#}"
echo "current process id:${$}"
echo "current option:${-}"
echo "quit state:${?}"
