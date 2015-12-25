#include "gtest/gtest.h"
#include <string>
#include <fstream>

// Intentionally left blank -- Include the student's hashtable header here
#include "../hw8_sol/hashtable.h"

const char *WORD_BANK_FILE = "word_banks/word_bank9.txt";

std::vector<std::string> WORD_BANK;

#define RUN_LARGE_TESTS 1
#define RUN_200 1
#define RUN_2000 1
#define RUN_20000 1
#define RUN_200000 1

class HashTableTest : public testing::Test
{
	protected:
		HashTableTest() { }
		~HashTableTest() { }
		virtual void SetUp() { }
		virtual void TearDown() { }

		HashTable mHashTable;
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

TEST_F(HashTableTest, FindOnEmptyTable_01)
{
	bool caughtException(false);

	try
	{
		mHashTable.find("test");
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_TRUE(caughtException);
}

TEST_F(HashTableTest, RemoveOnEmptyTable_02)
{
	bool caughtException(false);

	try
	{
		mHashTable.remove("test");
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_TRUE(caughtException);
}

TEST_F(HashTableTest, UpdateOnEmptyTable_03)
{
	bool caughtException(false);

	try
	{
		mHashTable.update(std::make_pair("test", 20));
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_TRUE(caughtException);
}

TEST_F(HashTableTest, AddSameElementTwice_04)
{
	bool caughtException = false;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.add(std::make_pair("test", 10));
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_TRUE(caughtException);
}

TEST_F(HashTableTest, AddSinglePairFind_05)
{
	bool caughtException = false;
	int value = 0;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		value = mHashTable.find("test");
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(value, 20);
}

TEST_F(HashTableTest, AddSinglePairRemove_06)
{
	bool caughtException = false;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.remove("test");
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
}

TEST_F(HashTableTest, AddSinglePairRemoveFind_07)
{
	bool caughtException = false;
	int value = 0;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.remove("test");
		value = mHashTable.find("test");
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_TRUE(caughtException);
	EXPECT_EQ(value, 0);
}

TEST_F(HashTableTest, AddSinglePairUpdate_08)
{
	bool caughtException = false;
	int value = 0;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.update(std::make_pair("test", 10));
		value = mHashTable.find("test");
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(value, 10);
}

TEST_F(HashTableTest, AddSameElementTwiceFind_09)
{
	bool caughtFirstException = false;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.add(std::make_pair("test", 10));
	}
	catch(...)
	{
		caughtFirstException = true;
	}

	EXPECT_TRUE(caughtFirstException);

	bool caughtSecondException = false;
	int testValue = 0;

	try
	{
		testValue = mHashTable.find("test");
	}
	catch(...)
	{
		caughtSecondException = true;
	}

	EXPECT_FALSE(caughtSecondException);
	EXPECT_EQ(testValue, 20);
}

TEST_F(HashTableTest, AddTwoPairs_10)
{
	bool caughtException = false;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.add(std::make_pair("cs104", 100));
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
}

TEST_F(HashTableTest, AddTwoPairsFind_11)
{
	bool caughtException = false;
	int testValue = 0;
	int cs104Value = 0;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.add(std::make_pair("cs104", 100));
		testValue = mHashTable.find("test");
		cs104Value = mHashTable.find("cs104");
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(testValue, 20);
	EXPECT_EQ(cs104Value, 100);
}

TEST_F(HashTableTest, AddTwoPairsUpdate_12)
{
	bool caughtException = false;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.add(std::make_pair("cs104", 100));
		mHashTable.update(std::make_pair("test", 10));
		mHashTable.update(std::make_pair("cs104", 5));
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
}

TEST_F(HashTableTest, AddTwoPairsUpdateFind_13)
{
	bool caughtException = false;
	int testValue = 0;
	int cs104Value = 0;

	try
	{
		mHashTable.add(std::make_pair("test", 20));
		mHashTable.add(std::make_pair("cs104", 100));
		mHashTable.update(std::make_pair("test", 10));
		mHashTable.update(std::make_pair("cs104", 5));
		testValue = mHashTable.find("test");
		cs104Value = mHashTable.find("cs104");
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(testValue, 10);
	EXPECT_EQ(cs104Value, 5);
}

TEST_F(HashTableTest, ResizeTable_14)
{
	bool caughtException = false;
	const int NUMBER_OF_ELEMENTS = 32;
	int numberOfElementsInserted = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.add(std::make_pair(WORD_BANK.at(i), i));
			++numberOfElementsInserted;
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfElementsInserted, NUMBER_OF_ELEMENTS);
}

TEST_F(HashTableTest, ResizeTableFindElements_15)
{
	bool caughtException = false;
	const int NUMBER_OF_ELEMENTS = 32;
	int numberOfElementsFound = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.add(std::make_pair(WORD_BANK.at(i), i));
		}

		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.find(WORD_BANK.at(i));
			++numberOfElementsFound;
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfElementsFound, NUMBER_OF_ELEMENTS);
}

#if RUN_LARGE_TESTS

#if RUN_200

TEST_F(HashTableTest, Add200ElementsFind_16)
{
	bool caughtException = false;
	const int NUMBER_OF_ELEMENTS = 200;
	int numberOfElementsInserted = 0;
	int numberOfElementsFound = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.add(std::make_pair(WORD_BANK.at(i), i));
			++numberOfElementsInserted;
		}

		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.find(WORD_BANK.at(i));
			++numberOfElementsFound;
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfElementsFound, NUMBER_OF_ELEMENTS);
	EXPECT_EQ(numberOfElementsInserted, NUMBER_OF_ELEMENTS);
}

#endif

#if RUN_2000

TEST_F(HashTableTest, Add2000ElementsFind_17)
{
	bool caughtException = false;
	const int NUMBER_OF_ELEMENTS = 2000;
	int numberOfElementsInserted = 0;
	int numberOfElementsFound = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.add(std::make_pair(WORD_BANK.at(i), i));
			++numberOfElementsInserted;
		}

		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.find(WORD_BANK.at(i));
			++numberOfElementsFound;
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfElementsFound, NUMBER_OF_ELEMENTS);
	EXPECT_EQ(numberOfElementsInserted, NUMBER_OF_ELEMENTS);
}

#endif

#if RUN_20000

TEST_F(HashTableTest, Add20000ElementsFind_18)
{
	bool caughtException = false;
	const int NUMBER_OF_ELEMENTS = 20000;
	int numberOfElementsInserted = 0;
	int numberOfElementsFound = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.add(std::make_pair(WORD_BANK.at(i), i));
			++numberOfElementsInserted;
		}

		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.find(WORD_BANK.at(i));
			++numberOfElementsFound;
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfElementsFound, NUMBER_OF_ELEMENTS);
	EXPECT_EQ(numberOfElementsInserted, NUMBER_OF_ELEMENTS);
}

#endif

#if RUN_200000

TEST_F(HashTableTest, Add200000ElementsFind_19)
{
	bool caughtException = false;
	const int NUMBER_OF_ELEMENTS = 200000;
	int numberOfElementsInserted = 0;
	int numberOfElementsFound = 0;

	try
	{
		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.add(std::make_pair(WORD_BANK.at(i), i));
			++numberOfElementsInserted;
		}

		for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			mHashTable.find(WORD_BANK.at(i));
			++numberOfElementsFound;
		}
	}
	catch(...)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(numberOfElementsFound, NUMBER_OF_ELEMENTS);
	EXPECT_EQ(numberOfElementsInserted, NUMBER_OF_ELEMENTS);
}

#endif

#endif