#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Intentionally left blank -- Include the student's heap header file here.
#include "../hw8_sol/heap.h"

const int MAX_HEAP_ARY = 26;
const int DEFAULT_HEAP_ARY = 2;
const char *WORD_BANK_FILE = "word_banks/word_bank9.txt";

std::vector<std::string> WORD_BANK;

#define RANDOM_HEAP_ARY 0
#define RUN_LARGE_TESTS 1
#define RUN_2000 1
#define RUN_20000 1
#define RUN_200000 1

class HeapTest : public testing::Test
{
	protected:
		#if RANDOM_HEAP_ARY
		HeapTest() : D_ARY(rand() % MAX_HEAP_ARY + 2), mMinHeap(D_ARY) 
		{ 
			std::cout << "Running heap test with " << D_ARY << "-ary heap" << std::endl;
		}
		#else
		HeapTest() : D_ARY(DEFAULT_HEAP_ARY), mMinHeap(D_ARY) { }
		#endif

		~HeapTest() { }
		virtual void SetUp() { }
		virtual void TearDown() { }

		int D_ARY;
		MinHeap mMinHeap;
};

void readWordBankFile()
{
	std::ifstream wordBankFile(WORD_BANK_FILE);

	std::string wordCount;
	wordBankFile >> wordCount;

	std::string word;
	while(wordBankFile >> word)
	{
		if(word.size() <= 12)
		{
			WORD_BANK.push_back(word);
		}
	}

	wordBankFile.close();
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	readWordBankFile();

	return RUN_ALL_TESTS();
}

TEST_F(HeapTest, InitiallyEmpty_01)
{
	EXPECT_TRUE(mMinHeap.isEmpty());
}

TEST_F(HeapTest, PeekOnEmptyHeap_02)
{
	bool caughtException = false;

	try
	{
		std::string peekValue = mMinHeap.peek();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_TRUE(caughtException);
}

TEST_F(HeapTest, UpdateOnEmptyHeap_03)
{
	bool caughtException = false;

	try
	{
		mMinHeap.update("test", 20);
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_TRUE(caughtException);
}

TEST_F(HeapTest, RemoveOnEmptyHeap_04)
{
	bool caughtException = false;

	try
	{
		mMinHeap.remove();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_TRUE(caughtException);
}

TEST_F(HeapTest, AddSingleItem_05)
{
	bool caughtException = false;

	try
	{
		mMinHeap.add("test", 20);
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
}

TEST_F(HeapTest, AddSingleItemPeek_06)
{
	bool caughtException = false;
	std::string peekValue = "";

	try
	{
		mMinHeap.add("test", 20);
		peekValue = mMinHeap.peek();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(peekValue, "test");
}

TEST_F(HeapTest, AddSingleItemRemoveCheckEmpty_07)
{
	bool caughtException = false;

	try
	{
		mMinHeap.add("test", 20);
		mMinHeap.remove();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_TRUE(mMinHeap.isEmpty());
}

TEST_F(HeapTest, AddTwoItemsInOrderPeek_08)
{
	bool caughtException = false;
	std::string peekValue = "";

	try
	{
		mMinHeap.add("Gandalf", 10);
		mMinHeap.add("Sauron", 20);
		peekValue = mMinHeap.peek();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(peekValue, "Gandalf");
}

TEST_F(HeapTest, AddTwoItemsOutOfOrderPeek_09)
{
	bool caughtException = false;
	std::string peekValue = "";

	try
	{
		mMinHeap.add("Sauron", 20);
		mMinHeap.add("Gandalf", 10);
		peekValue = mMinHeap.peek();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(peekValue, "Gandalf");
}

TEST_F(HeapTest, AddTwoItemsSamePriorityInOrderPeek_10)
{
	bool caughtException = false;
	std::string peekValue = "";

	try
	{
		mMinHeap.add("Gandalf", 10);
		mMinHeap.add("Sauron", 10);
		peekValue = mMinHeap.peek();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(peekValue, "Gandalf");
}

TEST_F(HeapTest, AddTwoItemsSamePriorityOutOfOrderPeek_11)
{
	bool caughtException = false;
	std::string peekValue = "";

	try
	{
		mMinHeap.add("Sauron", 10);
		mMinHeap.add("Gandalf", 10);
		peekValue = mMinHeap.peek();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(peekValue, "Gandalf");
}

TEST_F(HeapTest, AddTwoItemsInOrderUpdatePeek_12)
{
	bool caughtException = false;
	std::string peekValue = "";

	try
	{
		mMinHeap.add("Sauron", 10);
		mMinHeap.add("Gandalf", 20);
		mMinHeap.update("Gandalf", 1);
		peekValue = mMinHeap.peek();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(peekValue, "Gandalf");
}

TEST_F(HeapTest, AddTwoItemsOutOfOrderUpdatePeek_13)
{
	bool caughtException = false;
	std::string peekValue = "";

	try
	{
		mMinHeap.add("Gandalf", 20);
		mMinHeap.add("Sauron", 10);
		mMinHeap.update("Gandalf", 1);
		peekValue = mMinHeap.peek();
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(peekValue, "Gandalf");
}

TEST_F(HeapTest, AddTenItemsRemoveUntilEmpty_14)
{
	bool caughtException = false;
	const int NUMBER_OF_ITEMS = 10;

	int numberOfItemsAdded = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.add(WORD_BANK.at(i), i);
			++numberOfItemsAdded;
		}

		std::string peekValue = "";
		int currentItem = 0;
		while(!mMinHeap.isEmpty())
		{
			peekValue = mMinHeap.peek();
			EXPECT_EQ(peekValue, WORD_BANK.at(currentItem));
			++currentItem;
			mMinHeap.remove();
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfItemsAdded, NUMBER_OF_ITEMS);
	EXPECT_TRUE(mMinHeap.isEmpty());
}

TEST_F(HeapTest, AddTenItemsUpdatePriorityRemoveUntilEmpty_15)
{
	bool caughtException = false;
	const int NUMBER_OF_ITEMS = 10;

	int numberOfItemsAdded = 0;
	int numberOfItemsUpdated = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.add(WORD_BANK.at(i), NUMBER_OF_ITEMS + 1);
			++numberOfItemsAdded;
		}

		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.update(WORD_BANK.at(i), i);
			++numberOfItemsUpdated;
		}

		std::string peekValue = "";
		int currentItem = 0;
		while(!mMinHeap.isEmpty())
		{
			peekValue = mMinHeap.peek();
			EXPECT_EQ(peekValue, WORD_BANK.at(currentItem));
			++currentItem;
			mMinHeap.remove();
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfItemsAdded, NUMBER_OF_ITEMS);
	EXPECT_EQ(numberOfItemsUpdated, NUMBER_OF_ITEMS);
	EXPECT_TRUE(mMinHeap.isEmpty());
}

TEST_F(HeapTest, Add200ItemsUpdatePriorityRemoveUntilEmpty_16)
{
	bool caughtException = false;
	const int NUMBER_OF_ITEMS = 200;

	int numberOfItemsAdded = 0;
	int numberOfItemsUpdated = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.add(WORD_BANK.at(i), NUMBER_OF_ITEMS + 1);
			++numberOfItemsAdded;
		}

		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.update(WORD_BANK.at(i), i);
			++numberOfItemsUpdated;
		}

		std::string peekValue = "";
		int currentItem = 0;
		while(!mMinHeap.isEmpty())
		{
			peekValue = mMinHeap.peek();
			EXPECT_EQ(peekValue, WORD_BANK.at(currentItem));
			++currentItem;
			mMinHeap.remove();
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfItemsAdded, NUMBER_OF_ITEMS);
	EXPECT_EQ(numberOfItemsUpdated, NUMBER_OF_ITEMS);
	EXPECT_TRUE(mMinHeap.isEmpty());
}

#if RUN_LARGE_TESTS

#if RUN_2000

TEST_F(HeapTest, Add2000ItemsUpdatePriorityRemoveUntilEmpty_17)
{
	bool caughtException = false;
	const int NUMBER_OF_ITEMS = 2000;

	int numberOfItemsAdded = 0;
	int numberOfItemsUpdated = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.add(WORD_BANK.at(i), NUMBER_OF_ITEMS + 1);
			++numberOfItemsAdded;
		}

		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.update(WORD_BANK.at(i), i);
			++numberOfItemsUpdated;
		}

		std::string peekValue = "";
		int currentItem = 0;
		while(!mMinHeap.isEmpty())
		{
			peekValue = mMinHeap.peek();
			EXPECT_EQ(peekValue, WORD_BANK.at(currentItem));
			++currentItem;
			mMinHeap.remove();
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfItemsAdded, NUMBER_OF_ITEMS);
	EXPECT_EQ(numberOfItemsUpdated, NUMBER_OF_ITEMS);
	EXPECT_TRUE(mMinHeap.isEmpty());
}

#endif

#if RUN_20000

TEST_F(HeapTest, Add20000ItemsUpdatePriorityRemoveUntilEmpty_18)
{
	bool caughtException = false;
	const int NUMBER_OF_ITEMS = 20000;

	int numberOfItemsAdded = 0;
	int numberOfItemsUpdated = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.add(WORD_BANK.at(i), NUMBER_OF_ITEMS + 1);
			++numberOfItemsAdded;
		}

		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.update(WORD_BANK.at(i), i);
			++numberOfItemsUpdated;
		}

		std::string peekValue = "";
		int currentItem = 0;
		while(!mMinHeap.isEmpty())
		{
			peekValue = mMinHeap.peek();
			EXPECT_EQ(peekValue, WORD_BANK.at(currentItem));
			++currentItem;
			mMinHeap.remove();
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfItemsAdded, NUMBER_OF_ITEMS);
	EXPECT_EQ(numberOfItemsUpdated, NUMBER_OF_ITEMS);
	EXPECT_TRUE(mMinHeap.isEmpty());
}

#endif

#if RUN_200000

TEST_F(HeapTest, Add200000ItemsUpdatePriorityRemoveUntilEmpty_19)
{
	bool caughtException = false;
	const int NUMBER_OF_ITEMS = 200000;

	int numberOfItemsAdded = 0;
	int numberOfItemsUpdated = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.add(WORD_BANK.at(i), NUMBER_OF_ITEMS + 1);
			++numberOfItemsAdded;
		}

		for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
		{
			mMinHeap.update(WORD_BANK.at(i), i);
			++numberOfItemsUpdated;
		}

		std::string peekValue = "";
		int currentItem = 0;
		while(!mMinHeap.isEmpty())
		{
			peekValue = mMinHeap.peek();
			EXPECT_EQ(peekValue, WORD_BANK.at(currentItem));
			++currentItem;
			mMinHeap.remove();
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfItemsAdded, NUMBER_OF_ITEMS);
	EXPECT_EQ(numberOfItemsUpdated, NUMBER_OF_ITEMS);
	EXPECT_TRUE(mMinHeap.isEmpty());
}

#endif

#endif