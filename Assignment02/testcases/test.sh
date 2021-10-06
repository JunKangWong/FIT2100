#!/bin/bash

make='/home/student/Documents/FIT2100/Assgn/assignment_02'
test='/home/student/Documents/FIT2100/Assgn/assignment_02/testcases'

# run make
printf 'run make\n'
cd $make
make
cp task? $test

# run test cases
cd $test
for file in processes.txt test*.txt
do
    printf '\nTest case: %s\n' $file
    $make/task1 $file
    printf '\n'
    $make/task2 $file
    printf '\n'
    
    for res in result*.txt
    do
        printf '%s\n' $res
        cat $res
        printf '\n'
    done
done
    

