#!/bin/bash 
# to test shell operator

# test array
arr1=(1 3 5 7 9)
echo "the second data is ${arr1[2]}"
echo "the length of array is ${#arr1[*]}"
echo "the length of array is ${#arr1[@]}"

# arithmetic operation
echo 'addition:'`expr ${arr1[0]} + ${arr1[1]}`
echo 'subtraction:'`expr ${arr1[0]} - ${arr1[1]}`
echo 'multiplication:'`expr ${arr1[0]} \* ${arr1[1]}`
echo 'division:'`expr ${arr1[0]} / ${arr1[1]}`
echo 'residual:'`expr ${arr1[4]} % ${arr1[0]}`
arr1[5]=20
echo assigment:`expr arr1[5] = 25`
echo arr1[5]=${arr1[5]}
if [ ${arr1[0]} != ${arr1[1]} ]; then
    echo 'arr1[0] != arr1[1]'
fi

a=1
b=2
c=1
# relation operation
if [ ${a} -eq ${c} ]; then
    echo 'a==c'
else
    echo 'a!=c'
fi

if [ ${a} -ne ${b} ]; then
    echo 'a!=b'
fi

if [ ${b} -gt ${a} ]; then
    echo 'b>a'
fi

if [ ${a} -lt ${b} ]; then
    echo 'b<a'
fi

if [ ${a} -ge ${c} ]; then
    echo 'a>=c'
fi

if [ ${a} -le ${b} ]; then
    echo 'a<=b'
fi

# boolean operation
if [ ${a} -gt ${b} -o ${a} -eq ${c} ]; then
    echo 'a>b or a==c'
fi
if [ $a -lt $b -a $a -eq $c ]; then
    echo 'a<b and a==c'
fi
if [ ! $a -ge $b ]; then
    echo '!(a>=b)'
fi

# logic operation
if [[ $a -ge 4 || $b -le 2 ]]; then
    echo 'a>=4 || b<=2'
fi
if [[ $a -ge 0 && $b -le 2 ]]; then
    echo 'a>=0 && b<=2'
fi

# string operation
str1=abc
str2=defg
str3=''
if [[ $str1 = $str3 ]]; then
    #statements
    echo 'str1==str2'
fi
if [[ $str1 != $str2 ]]; then
    #statements
    echo 'str1==str2'
fi
if [[ ! -z $str1 ]]; then
    #statements
    echo 'str1 is not None'
fi
if [[ -n $str1 ]]; then
    #statements
    echo 'length of str1 is not None'
fi
if [[ ! $str3 ]]; then
    #statements
    echo 'str3 is None'
fi

# file test operation
file1=`pwd`'/first_shell.sh'
dir1='./'
if [[ ! -b $file1 ]]; then
    echo 'the file is not block file'
fi
if [[ ! -c $file1 ]]; then
    echo 'the file is not character file'
fi
if [[ ! -d $dir1 ]]; then
    echo 'the dir is a directory'
fi
if [[ -f $file1 ]]; then
    echo 'the file is a ordinary file'
fi
if [[ -p $file1 ]]; then
    echo 'the file is not a pipe file'
fi
if [[ -r $file1 ]]; then
    echo 'the file is readable'
fi
if [[ -w $file1 ]]; then
    echo 'the file is writable'
fi
if [[ -x $file1 ]]; then
    echo 'the file is executable'
fi
if [[ -s $file1 ]]; then
    echo 'the file is not None'
fi
if [[ ! -e `pwd`'/test.sh' ]]; then
    echo 'the file is not exist'
fi

# test echo 
var1=helloworld
var2=world
var3=${var1#}
echo $var3
echo -e "ok! \n"
echo -e "this is a test"
echo -e "ok! \c"
echo -e "this is a test"
echo `date`

# test printf
printf "%-10s %-8s %-4s\n" name gender weight/kg
printf "%-10s %-8s %-4.2f\n" john boy 66.1234
printf "%-10s %-8s %-4.2f\n" luccy girl 48.1234
printf "%-10s %-8s %-4.2f\n" lili girl 45.1234

# test command same as [ xx ]
num1=100
num2=200
if test $num1 -eq 100; then
    echo "equal"
fi
if test $num1 -ne $num2; then
    echo "not equal"
fi
if test $num1 -le $num2; then
    echo "num1 <= num2"
fi

# arithmetic operation
a=1
b=2
c=3
result=$[ a + b ]
echo "a+b:$result"
result=$[ a - b ]
echo "a-b:$result"
result=$[ a*b ]
echo  "a*b:$result"
result=$[ a/b ]
echo "a/b:$result"
result=$[ a%b ]
echo "a%b:$result"
result=`expr $a + $b`
echo "another way: a+b:$result"
