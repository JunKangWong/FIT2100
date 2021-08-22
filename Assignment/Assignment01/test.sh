#!/bin/bash

input='/home/student/Documents/FIT2100/Assgn/assignment_01/input/test.txt'
dest='/home/student/Documents/FIT2100/Assgn/assignment_01/output'
wrong_dest='/home/student/Documents/FIT2100/Assgn/assignment_01/output/wrong'

# Test Task 1
printf 'Test Task 1\n'

# Test functionality: print 10 lines of sample.txt from current dir
printf 'Test functionality\n'
./fileutil

# Test error handling: print an error message
printf '\nTest error handling\n'
mv sample.txt input
./fileutil
mv input/sample.txt .


# Test Task 2
printf '\nTest Task 2\n'

# Test functionality: print 10 lines of test.txt from ./input
printf 'Test functionality\n'
./fileutil $input


# Test Task 3
printf '\nTest Task 3\n'

# clear dest dir
rm $dest/*

# Test functionality: copy 10 lines of sample.txt to ./output
printf 'Test functionality\n'
./fileutil -d $dest
cat ./output/sample.txt
echo

# Test functionality: copy 10 lines of input to ./output
./fileutil $input -d $dest
cat ./output/test.txt

# Test error handling:  file already exists at the dest
printf '\nTest error handling: file already exists at the dest\n'
./fileutil -d $dest
./fileutil $input -d $dest

# Test error handling: dest dir does not exist
printf '\nTest error handling: dest dir does not exist\n'
./fileutil -d $wrong_dest
./fileutil $input -d $wrong_dest


# Test Task 4
printf '\nTest Task 4\n'

# Test functionality: print 0, 5, 100 lines of sample.txt
printf 'sample.txt\nPrint 0 line\n'
./fileutil -n 0

printf '\nPrint 5 lines\n'
./fileutil -n 5

printf '\nPrint 100 lines\n'
./fileutil -n 100

# Test functionality: print 0, 5, 100 lines of input
printf '\n%s\nPrint 0 line\n' $input
./fileutil $input -n 0

printf '\nPrint 5 lines\n'
./fileutil $input -n 5

printf '\nPrint 100 lines\n'
./fileutil $input -n 100


# Test Task 5
printf '\nTest Task 5'

# Test functionality: print sample.txt in tail mode
printf '\nprint sample.txt in tail mode\n'
./fileutil -L

# Test functionality: print input in tail mode
printf '\nprint %s in tail mode\n' $input
./fileutil $input -L  
