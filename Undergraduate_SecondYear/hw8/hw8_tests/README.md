# CSCI 104 - HW 08 Tests

##Problem 1: Build a Hashtable (20%)

[`hashtable_gtest.cpp`](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/hashtable_gtest.cpp):
+ Line [6](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/hashtable_gtest.cpp#L6) should include your header file for the hashtable class.

+ Line [12](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/hashtable_gtest.cpp#L12) can be toggled to turn on/off the large tests. 

+ Lines [13-16](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/hashtable_gtest.cpp#L13) can be individually toggled to turn on/off specific large tests so that only some are run.

###Running the Tests:
To compile the tests after the above lines have been edited, use following commands: 

```shell
$ g++ -g -Wall -std=c++0x hashtable_gtest.cpp  <other_files_as_needed> \
-I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread \
-o hashtable_gtest
```

###Test Descriptions:
In total there are 19 tests for the hashtable as described below:

+ 01: Intentionally tries to have an exception thrown by performing `find` on an empty hashtable.
+ 02: Intentionally tries to have an exception thrown by performing `remove` on an empty hashtable.
+ 03: Intentionally tries to have an exception thrown by performing `update` on an empty hashtable.
+ 04: Intentionally tries to have an exception thrown by performing two `add` operations with the same element.
+ 05: Performs a single `add` operation and tries to `find` that element.
+ 06: Performs a single `add` operation and tries to `remove` that same element.
+ 07: Performs a single `add` operation, tries to `remove` that element, and then tries to perform `find` on that element.
+ 08: Performs a single `add` operation, tries to `update` the element, and then tries to `find` the element and check it was updated.
+ 09: Performs two `add` operations with the same element and tries to `find` the first element that was added.
+ 10: Performs two `add` operations with different elements to make sure no exception is thrown.
+ 11: Performs two `add` operations with different elements, and tries to `find` both elements and check their values. 
+ 12: Performs two `add` operations and tries to `update` both elements to make sure no exception is thrown.
+ 13: Performs two `add` operations and tries to `update` both elements, checking that their values are properly updated. 
+ 14: Performs 32 `add` operations with distinct elements to cause the table to resize, checks that 32 elements were inserted. 
+ 15: Performs 32 `add` operations with distinct elements and attempts to `find` all 32 elements. 
+ 16: Performs 200 `add` operations with distinct elements and attempts to `find` all 200 elements. 
+ 17: Performs 2000 `add` operations with distinct elements and attempts to `find` all 2000 elements. 
+ 18: Performs 20000 `add` operations with distinct elements and attempts to `find` all 20000 elements. 
+ 19: Performs 200000 `add` operations with distinct elements and attempts to `find` all 200000 elements. 


##Problem 2: Build a d-ary Heap (30%)

[`heap_gtest.cpp`](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/heap_gtest.cpp):
+ Line [8](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/heap_gtest.cpp#L8) should include the student's header file for the heap class.
+ Line [16](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/heap_gtest.cpp#L16) can be toggled to have a random d-ary heap. This test should be run at least once in addition to the normal test. When this option is turned off, the heap will default to a binary heap.
+ Line [17](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/heap_gtest.cpp#L17) can be toggled to turn on/off the large tests. 
+ Lines [18-20](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/heap_gtest.cpp#L18) can be individually toggled to turn on/off specific large tests so that only some are run.

###Running the Tests:
To compile the tests after the above lines have been edited, use following commands: 

```shell
$ g++ -g -Wall -std=c++0x heap_gtest.cpp  <other_files_as_needed> \
-I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread \
-o hashtable_gtest
```

###Test Descriptions:
In total there are 19 tests for the heap as described below:

+ 01: Checks that the heap is initially empty.
+ 02: Intentionally tries to throw an exception by performing `peek` on an empty heap.
+ 03: Intentionally tries to throw an exception by performing `update` on an empty heap.
+ 04: Intentionally tries to throw an exception by performing `remove` on an empty heap.
+ 05: Performs a single `add` operation and checks that no exception is thrown.
+ 06: Performs a single `add` operation and checks that no exception is thrown. 
+ 07: Performs a single `add` operation and tries to `remove` that item, checking that no exception is thrown. 
+ 08: Performs two `add` operations in the order they should be in the heap, and performs a single `peek` operation to make sure the right value is on the top of the heap.
+ 09: Performs two `add` operations in the opposite order they should be in the heap, and performs a single `peek` operation to make sure the right value gets put on the top of the heap.
+ 10: Performs two `add` operations with items of the same priority in the right order, and performs a single `peek` operation to make sure the right value is on the top.
+ 11: Performs two `add` operations with items of the same priority in the opposite order, and performs a single `peek` operation to make sure the right alphabetic value is put on the top of the heap. 
+ 12: Performs two `add` operations on items of different priority, added in the right order, and then performs a single `update` operation on the bottom element to make sure it gets put on the top of the heap.
+ 13: Performs two `add` operations on items of different priority, added in the opposite order, and then performs a single `update` operation on the bottom element to make sure it gets put on the top of the heap.
+ 14: Performs 10 `add` operations on distinct items, and attempts to `remove` all of the items until the heap is empty.
+ 15: Performs 10 `add` operations on distinct items, attempts to `update` the piority of the items, and then tries to `remove` all items from the heap until empty.
+ 16: Performs 200 `add` operations on distinct items with the same priority, updates all of the priorities of the elements to be different, and then tries to `remove` all of the elements until empty and checks the priority of the elements. 
+ 17: Performs 2000 `add` operations on distinct items with the same priority, updates all of the priorities of the elements to be different, and then tries to `remove` all of the elements until empty and checks the priority of the elements.
+ 18: Performs 20000 `add` operations on distinct items with the same priority, updates all of the priorities of the elements to be different, and then tries to `remove` all of the elements until empty and checks the priority of the elements.
+ 19: Performs 200000 `add` operations on distinct items with the same priority, updates all of the priorities of the elements to be different, and then tries to `remove` all of the elements until empty and checks the priority of the elements.


##Problem 3: A* Puzzle Solver (50%)

The test files that were use to test your program are provided in the [`word_banks/`](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/word_banks/) directory. Description is given below:

+ [word_bank1.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank1.txt) HEAD -> TAIL: Contains 6 words.
+ [word_bank2.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank2.txt) APE -> MAN: Contains 20 words.
+ [word_bank3.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank3.txt) FLOUR -> BREAD: Contains 25 words.
+ [word_bank4.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank4.txt) ONE -> TWO: Contains 57 words.
+ [word_bank5.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank5.txt) BLACK -> WHITE: Contains 110 words.
+ [word_bank6.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank6.txt) BLUE -> PINK: Contains 2009 words.
+ [word_bank7.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank7.txt) RIVER -> SHORE: Contains 3231 words.
+ [word_bank8.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank8.txt) WITCH -> FAIRY: Contains 3235 words.
+ [word_bank9.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank9.txt) SLEEP -> DREAM: Contains 274926 words.
+ [word_bank10.txt](https://github.com/usc-csci104-fall2015/homework-resources/edit/master/hw8_tests/word_banks/word_bank10.txt) RIVER -> GOTEE: Contains 83 words.

Solutions are provided in the [`doublet_sol/`](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw8_tests/doublet_sol/) directory to compare output from your program with the reference solution output. 

###Running the Tests:
Compile your program, run with the test files and compare output with the reference solution provided.


