#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "../hw2_sol/llistint.h"

class LListIntTest : public testing::Test
{
	protected:
		LListIntTest() { }
		~LListIntTest() { }
		virtual void SetUp() 
		{
			mLListInt = new LListInt();
		}
		virtual void TearDown() 
		{ 
			mLListInt->clear();
			delete mLListInt;
		}

		LListInt *mLListInt;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(LListIntTest, InitiallyEmpty_01)
{
	EXPECT_TRUE(mLListInt->empty());
}

TEST_F(LListIntTest, InitiallySizeZero_02)
{
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, EmptyInsertLess_03)
{
	mLListInt->insert(-1, 10);
	EXPECT_TRUE(mLListInt->empty());
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, EmptyInsertGreater_04)
{
	mLListInt->insert(1, 10);
	EXPECT_TRUE(mLListInt->empty());
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, EmptyRemoveLess_05)
{
	mLListInt->remove(-1);
	EXPECT_TRUE(mLListInt->empty());
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, EmptyRemoveGreater_06)
{
	mLListInt->remove(1);
	EXPECT_TRUE(mLListInt->empty());
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, SingleInsertNotEmpty_07)
{
	mLListInt->insert(0, 10);
	EXPECT_FALSE(mLListInt->empty());
}

TEST_F(LListIntTest, SingleInsertSize_08)
{
	mLListInt->insert(0, 10);
	EXPECT_EQ(mLListInt->size(), 1);
}

TEST_F(LListIntTest, SingleInsertThenRemoveEmpty_09)
{
	mLListInt->insert(0, 10);
	mLListInt->remove(0);
	EXPECT_TRUE(mLListInt->empty());
}

TEST_F(LListIntTest, SingleInsertThenRemoveSize_10)
{
	mLListInt->insert(0, 10);
	mLListInt->remove(0);
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, MultipleInsertHeadCheckOrder_11)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(0, i);
		EXPECT_EQ(mLListInt->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListInt->get(i), NUMBER_OF_ELEMENTS - i - 1);
	}
}

TEST_F(LListIntTest, MultipleInsertTailCheckOrder_12)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(mLListInt->size(), i);
		EXPECT_EQ(mLListInt->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListInt->get(i), i);
	}
}

TEST_F(LListIntTest, MultipleInsertMiddleCheckOrder_13)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(mLListInt->size() / 2, i);
		EXPECT_EQ(mLListInt->size(), i + 1);
	}

	EXPECT_EQ(mLListInt->get(0), 1);
	EXPECT_EQ(mLListInt->get(1), 3);
	EXPECT_EQ(mLListInt->get(2), 5);
	EXPECT_EQ(mLListInt->get(3), 7);
	EXPECT_EQ(mLListInt->get(4), 9);
	EXPECT_EQ(mLListInt->get(5), 8);
	EXPECT_EQ(mLListInt->get(6), 6);
	EXPECT_EQ(mLListInt->get(7), 4);
	EXPECT_EQ(mLListInt->get(8), 2);
	EXPECT_EQ(mLListInt->get(9), 0);
}

TEST_F(LListIntTest, MultipleInsertRandomThenRemoveRandom_14)
{
	const int NUMBER_OF_ELEMENTS = 10;

	mLListInt->insert(0, 0);

	for(int i = 1; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(rand() % mLListInt->size(), i);
		EXPECT_EQ(mLListInt->size(), i + 1);
	}

	int size = mLListInt->size();
	while(mLListInt->size() != 1)
	{
		mLListInt->remove(rand() % (mLListInt->size() - 1));
		EXPECT_EQ(mLListInt->size(), --size);
	}
}

TEST_F(LListIntTest, LargeInputStressTest_15)
{
	const int NUMBER_OF_ELEMENTS = 10000;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(0, i);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListInt->get(0), NUMBER_OF_ELEMENTS - i - 1);
		mLListInt->remove(0);
		EXPECT_EQ(mLListInt->size(), NUMBER_OF_ELEMENTS - i - 1);
	}
}