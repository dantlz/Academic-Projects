#include "stackint.h"
#include "gtest/gtest.h"

using namespace std;
class StackIntTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	StackIntTest() {
		// You can do set-up work for each test here.
	}

	virtual ~StackIntTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		stack.push(0);
		stack.push(1);
		stack.push(2);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	StackInt stack;
};

TEST_F(StackIntTest, Empty) {
	// Exepct 0th element to be 1, 1st elemnt to be 2, etc.
	EXPECT_EQ(stack.empty(), false);
}

TEST_F(StackIntTest, pop) {
	stack.pop();
	stack.pop();
	stack.pop();
	EXPECT_EQ(stack.empty(), true);
}

TEST_F(StackIntTest, push) {
	stack.push(100);
	EXPECT_EQ(stack.top(),100);
}

TEST_F(StackIntTest, top) {
	EXPECT_EQ(stack.top(), 2);
	stack.pop();
	EXPECT_EQ(stack.top(), 1);
	stack.pop();
	EXPECT_EQ(stack.top(), 0);
	stack.pop();
	EXPECT_EQ(stack.empty(),true);
}