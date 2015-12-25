#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "stackint.h"

class StackIntTest : public testing::Test
{
	protected:
		StackIntTest() { }
		~StackIntTest() { }
		virtual void SetUp() 
		{

		}
		virtual void TearDown() 
		{ 
			
		}

		StackInt mStackInt;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(StackIntTest, InitiallyEmpty_01)
{
	EXPECT_TRUE(mStackInt.empty());
}

TEST_F(StackIntTest, SinglePushEmpty_02)
{
	mStackInt.push(0);
	EXPECT_FALSE(mStackInt.empty());
}

TEST_F(StackIntTest, SinglePushCheckTop_03)
{
	mStackInt.push(0);
	EXPECT_EQ(mStackInt.top(), 0);
}

TEST_F(StackIntTest, SinglePushPopEmpty_04)
{
	mStackInt.push(0);
	mStackInt.pop();
	EXPECT_TRUE(mStackInt.empty());
}

TEST_F(StackIntTest, MultiplePushCheckOrder_05)
{
	const int NUMBER_OF_ELEMENTS = 20;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mStackInt.push(i);
	}
	int numberOfItemsRemoved = 0;
	while(!mStackInt.empty())
	{
		EXPECT_EQ(mStackInt.top(), NUMBER_OF_ELEMENTS - 1 - numberOfItemsRemoved);
		mStackInt.pop();
		++numberOfItemsRemoved;
	}
	EXPECT_EQ(numberOfItemsRemoved, NUMBER_OF_ELEMENTS);
}

TEST_F(StackIntTest, Runtime1000Element_06)
{
	const int NUMBER_OF_ELEMENTS = 1000;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mStackInt.push(i);
	}
	int numberOfItemsRemoved = 0;
	while(!mStackInt.empty())
	{
		EXPECT_EQ(mStackInt.top(), NUMBER_OF_ELEMENTS - 1 - numberOfItemsRemoved);
		mStackInt.pop();
		++numberOfItemsRemoved;
	}
	EXPECT_EQ(numberOfItemsRemoved, NUMBER_OF_ELEMENTS);
}

TEST_F(StackIntTest, Runtime10000Elements_07)
{
	const int NUMBER_OF_ELEMENTS = 10000;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mStackInt.push(i);
	}
	int numberOfItemsRemoved = 0;
	while(!mStackInt.empty())
	{
		EXPECT_EQ(mStackInt.top(), NUMBER_OF_ELEMENTS - 1 - numberOfItemsRemoved);
		mStackInt.pop();
		++numberOfItemsRemoved;
	}
	EXPECT_EQ(numberOfItemsRemoved, NUMBER_OF_ELEMENTS);
}

TEST_F(StackIntTest, Runtime100000Elements_08)
{
	const int NUMBER_OF_ELEMENTS = 100000;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mStackInt.push(i);
	}
	int numberOfItemsRemoved = 0;
	while(!mStackInt.empty())
	{
		EXPECT_EQ(mStackInt.top(), NUMBER_OF_ELEMENTS - 1 - numberOfItemsRemoved);
		mStackInt.pop();
		++numberOfItemsRemoved;
	}
	EXPECT_EQ(numberOfItemsRemoved, NUMBER_OF_ELEMENTS);
}

TEST_F(StackIntTest, Runtime1000000Elements_09)
{
	const int NUMBER_OF_ELEMENTS = 1000000;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mStackInt.push(i);
	}
	int numberOfItemsRemoved = 0;
	while(!mStackInt.empty())
	{
		EXPECT_EQ(mStackInt.top(), NUMBER_OF_ELEMENTS - 1 - numberOfItemsRemoved);
		mStackInt.pop();
		++numberOfItemsRemoved;
	}
	EXPECT_EQ(numberOfItemsRemoved, NUMBER_OF_ELEMENTS);
}

// TEST_F(StackIntTest, Runtime10000000Elements)
// {
// 	const int NUMBER_OF_ELEMENTS = 10000000;
// 	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
// 	{
// 		mStackInt.push(i);
// 	}
// 	int numberOfItemsRemoved = 0;
// 	while(!mStackInt.empty())
// 	{
// 		EXPECT_EQ(mStackInt.top(), NUMBER_OF_ELEMENTS - 1 - numberOfItemsRemoved);
// 		mStackInt.pop();
// 		++numberOfItemsRemoved;
// 	}
// 	EXPECT_EQ(numberOfItemsRemoved, NUMBER_OF_ELEMENTS);
// }
