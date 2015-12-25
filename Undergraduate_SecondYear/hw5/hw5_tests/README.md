# CSCI 104 - HW05 Tests


##Step 3: Implement MergeSort (25%)

Before running each test, you should modify the following lines in the `gtest_msort.cpp` file.

 - Change line [9](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw5_tests/gtest_msort.cpp#L9) to include your `msort.h` file.

 - Starting on line [13](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw5_tests/gtest_msort.cpp#L13) are several `typedef`s for the kinds of containers that you may have used. By default the `vector` container type is defined. If a you have used a different container, uncomment the appropriate type. The Google Test uses iterators to check the contents of the containers, so no further modification is needed. 

 - Change line [22](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw5_tests/gtest_msort.cpp#L22) to indicate the name of the MergeSort function. By default, the function is called `msort()`, but you may have named it differently.

 - Compile with following command:

```shell
$ g++ -g -Wall -std=c++0x gtest_msort.cpp  \
-I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread \
-o msort_test
```

##Step 4: Put a Qt frontend on it (60%)

There are 3 data sets for test the Qt frontend.

  - `data3/index.txt` is used test different feature of the GUI.
  - Run program with `data4/index.txt`. Only `test2.txt` files contains links to test1 and itself.
  - Search the term `file` with any option. It should result in links to both test1 and test2 files.
  - If you display test1 file, there will be only one incoming link from test2 and no outgoing link.
  - Click on test2 to see its contents. It will have one incoming link from itself and two outgoing links (to test1 and itself.)

**Testing all features**
  - Run program with `data5/index.txt`.
  - Searching with term `file` should 5 files given below. Opening each file in new window should show with following link configurations:
   - Test1: Outgoing: (test 5), Incoming: (test 3)
   - Test2: Outgoing: (test 3, and 4), Incoming: (test 4)
   - Test3: Outgoing: (test 1, and 4), Incoming: (test 2, and 5)
   - Test4: Outgoing: (test 2, and 5), Incoming: (test 2, and 3)
   - Test5: Outgoing: (test 3), Incoming: (test 1, and 4)

In main window, search with `file` and test for the sorting functionality using following guidelines:
  - based on filename: test1 (on top), test2, test3, test4, and test5 (at bottom)
  - based on incoming: test2 (on top), test1, test5, test4, and test3 (at bottom)
  - based on outgoing: test5 (on top), test1, test3, test4, and test2 (at bottom)

Additionally, search with `OR peer links` and verify following:
  - based on filename: test2 (on top), test3, test4, and test5 (at bottom)
  - based on incoming: test2 (on top), test5, test4, and test3 (at bottom)
  - based on outgoing: test5 (on top), test3, test4, and test2 (at bottom)

Finally, you should also test program for different functions as given below:
  - ` OR interesting observations` should show: test4.txt, and test5.txt
  - `AND interesting observations` will fail
  - `withfile` search with any option and it should result in test2.txt
  - `AND pagerank explained` should show test3.txt

