# CSCI 104 - HW # 3 Tests

All the tests for HW # 3 are now posted in their respective folders as described below.

#### Before you dispute your grade:

It is recommended that you first make sure that your program worked correctly. If your program failed any of the tests, try debugging by using `gdb` and see what was the issue. Once you're sure that everything worked fine, first reach out to the grader and then the TAs. Always tag your grader using `@<grader-github-ID>` in your disputes so that they get notified.

#### Problem 2:
 
 + The GTest file `gtest_alistint.cpp`used to test this problem is provided. 

#### Problem 3:
 
 + The GTest file `gtest_stackint.cpp`used to test this problem is provided

#### Problem 4:
 
 + The solution for problem 4 is posted as a pdf file. You may be penalized if you didn't provide a satisfactory answer, or didn't justify your final answer. Simply giving a one-line answer of the problem is not sufficient, even if it is correct.

#### Problem 5:
 
 + This folder contains the `.in`, `.vars` files used to test problem 5. Use these files with your program. You can compare the output provided by your program with the solution output given in the `output.txt` files.

#### Compiling GTest programs:

 To compile your program with a GTest file, it is preferred that you create a `Makefile`. Alternately, use following commands: 

```shell
$ g++ -g -Wall <source_files> \
-I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread \
-o <executable_file>
```

Note that <source_files> refers to all the source cpp files including the GTest file, and <excutable_file> is the name of the final executable file. `< >` are used to point out the required or optional parameters, don't use `< >` themselves when you enter filenames or other arguments.

#### Valgrind

After generating the executable, use valgrind to test any memory leaks or invalid reads. Note that `<args>` may be optional for some of the above tests.

```shell
$ valgrind --tool=memcheck --leak-check=yes ./<executable_file> <arg1> <arg2> ...
```
