#include "gtest/gtest.h"
#include <functional> 
#include <string>

// Intentionally left blank -- Include the student's BST header file here.
#include ""

#define RUN_BST_TESTS 0

typedef RedBlackTree<std::string, int>::iterator StringIntIterator;
typedef RedBlackTree<int, double>::iterator IntDoubleIterator;

class RBTTest : public testing::Test
{
	protected:
		RBTTest() { }
		~RBTTest() { }
		virtual void SetUp() { }
		virtual void TearDown() { }

		RedBlackTree<std::string, int> mStringIntRBST;
		RedBlackTree<int, double> mIntDoubleRBST;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

#if RUN_BST_TESTS

TEST_F(RBTTest, InitiallyEmpty_01)
{
	EXPECT_EQ(mStringIntRBST.begin(), mStringIntRBST.end());

	EXPECT_EQ(mIntDoubleRBST.begin(), mIntDoubleRBST.end());
}

TEST_F(RBTTest, FindOnEmptyTree_02)
{
	StringIntIterator stringIntIT = mStringIntRBST.find("Testing");
	EXPECT_EQ(stringIntIT, mStringIntRBST.end());

	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(0);
	EXPECT_EQ(intDoubleIT, mIntDoubleRBST.end());
}

TEST_F(RBTTest, InsertSingleElementBeginNotEqualToEnd_03)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	EXPECT_NE(mStringIntRBST.begin(), mStringIntRBST.end());

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	EXPECT_NE(mIntDoubleRBST.begin(), mIntDoubleRBST.end());
}

TEST_F(RBTTest, InsertSingleElementFindNotEqualToEnd_04)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	StringIntIterator stringIntIT = mStringIntRBST.find("Gandalf");
	EXPECT_NE(stringIntIT, mStringIntRBST.end());

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(10);
	EXPECT_NE(intDoubleIT, mIntDoubleRBST.end());
}

TEST_F(RBTTest, InsertSingleElementDereferenceFirstSecond_05)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	StringIntIterator stringIntIT = mStringIntRBST.find("Gandalf");
	EXPECT_EQ(stringIntIT->first, "Gandalf");
	EXPECT_EQ(stringIntIT->second, 100);

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(10);
	EXPECT_EQ(intDoubleIT->first, 10);
	EXPECT_EQ(intDoubleIT->second, 100.5);
}

TEST_F(RBTTest, InsertSingleElementAssignToPairByDereference_06)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	StringIntIterator stringIntIT = mStringIntRBST.find("Gandalf");
	std::pair<std::string, int> myStringIntPair = *stringIntIT;
	EXPECT_EQ(myStringIntPair.first, "Gandalf");
	EXPECT_EQ(myStringIntPair.second, 100);

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(10);
	std::pair<int, double> myIntDoublePair = *intDoubleIT;
	EXPECT_EQ(myIntDoublePair.first, 10);
	EXPECT_EQ(myIntDoublePair.second, 100.5);
}

TEST_F(RBTTest, InsertSingleElementIncrementIterator_07)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	StringIntIterator stringIntIT = mStringIntRBST.find("Gandalf");
	++stringIntIT;
	EXPECT_EQ(stringIntIT, mStringIntRBST.end());

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(10);
	++intDoubleIT;
	EXPECT_EQ(intDoubleIT, mIntDoubleRBST.end());
}

TEST_F(RBTTest, InsertSingleElementFindNonexistentElementEqualToEnd_08)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	StringIntIterator stringIntIT = mStringIntRBST.find("Sauramon");
	EXPECT_EQ(stringIntIT, mStringIntRBST.end());

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(100);
	EXPECT_EQ(intDoubleIT, mIntDoubleRBST.end());
}

TEST_F(RBTTest, InsertTwoElementsFindOnBothNotEqualToEnd_09)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	mStringIntRBST.insert(std::make_pair("Sauramon", 200));
	StringIntIterator stringIntIT = mStringIntRBST.find("Gandalf");
	EXPECT_NE(stringIntIT, mStringIntRBST.end());
	stringIntIT = mStringIntRBST.find("Sauramon");
	EXPECT_NE(stringIntIT, mStringIntRBST.end());

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	mIntDoubleRBST.insert(std::make_pair(20, 200.5));
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(10);
	EXPECT_NE(intDoubleIT, mIntDoubleRBST.end());
	intDoubleIT = mIntDoubleRBST.find(20);
	EXPECT_NE(intDoubleIT, mIntDoubleRBST.end());
}

TEST_F(RBTTest, InsertTwoElementsDereferenceFirstAndSecond_10)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	mStringIntRBST.insert(std::make_pair("Sauramon", 200));
	StringIntIterator stringIntIT = mStringIntRBST.find("Gandalf");
	EXPECT_EQ(stringIntIT->first, "Gandalf");
	EXPECT_EQ(stringIntIT->second, 100);
	stringIntIT = mStringIntRBST.find("Sauramon");
	EXPECT_EQ(stringIntIT->first, "Sauramon");
	EXPECT_EQ(stringIntIT->second, 200);

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	mIntDoubleRBST.insert(std::make_pair(20, 200.5));
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(10);
	EXPECT_EQ(intDoubleIT->first, 10);
	EXPECT_EQ(intDoubleIT->second, 100.5);
	intDoubleIT = mIntDoubleRBST.find(20);
	EXPECT_EQ(intDoubleIT->first, 20);
	EXPECT_EQ(intDoubleIT->second, 200.5);
}

TEST_F(RBTTest, InsertTwoElementsIncrementIterator_11)
{
	mStringIntRBST.insert(std::make_pair("Gandalf", 100));
	mStringIntRBST.insert(std::make_pair("Sauramon", 200));
	StringIntIterator stringIntIT = mStringIntRBST.find("Gandalf");
	EXPECT_EQ(stringIntIT->first, "Gandalf");
	EXPECT_EQ(stringIntIT->second, 100);
	++stringIntIT;
	EXPECT_EQ(stringIntIT->first, "Sauramon");
	EXPECT_EQ(stringIntIT->second, 200);
	++stringIntIT;
	EXPECT_EQ(stringIntIT, mStringIntRBST.end());

	mIntDoubleRBST.insert(std::make_pair(10, 100.5));
	mIntDoubleRBST.insert(std::make_pair(20, 200.5));
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.find(10);
	EXPECT_EQ(intDoubleIT->first, 10);
	EXPECT_EQ(intDoubleIT->second, 100.5);
	++intDoubleIT;
	EXPECT_EQ(intDoubleIT->first, 20);
	EXPECT_EQ(intDoubleIT->second, 200.5);
	++intDoubleIT;
	EXPECT_EQ(intDoubleIT, mIntDoubleRBST.end());
}

TEST_F(RBTTest, InsertTenElementsIncrementIteratorCheckOrder_12)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mStringIntRBST.insert(std::make_pair("TheOneRing" + std::to_string(i), i));
		mIntDoubleRBST.insert(std::make_pair(i, i * 0.5));
	}

	int counter = 0;
	StringIntIterator stringIntIT = mStringIntRBST.begin();
	while(stringIntIT != mStringIntRBST.end())
	{
		EXPECT_EQ(stringIntIT->first, "TheOneRing" + std::to_string(counter));
		EXPECT_EQ(stringIntIT->second, counter);
		++counter;
		++stringIntIT;
	}
	EXPECT_EQ(counter, NUMBER_OF_ELEMENTS);

	counter = 0;
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.begin();
	while(intDoubleIT != mIntDoubleRBST.end())
	{
		EXPECT_EQ(intDoubleIT->first, counter);
		EXPECT_EQ(intDoubleIT->second, counter * 0.5);
		++counter;
		++intDoubleIT;
	}
	EXPECT_EQ(counter, NUMBER_OF_ELEMENTS);
}

TEST_F(RBTTest, Insert10000RandomElementsIteratorCheckOrder_13)
{
	const int NUMBER_OF_ELEMENTS = 10000;

	srand(0);

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		int number = rand();
		mStringIntRBST.insert(std::make_pair("TheOneRing" + std::to_string(number), number));
		mIntDoubleRBST.insert(std::make_pair(number, number * 0.5));
	}

	int counter = 0;
	StringIntIterator stringIntIT = mStringIntRBST.begin();
	std::string previousString = stringIntIT->first;
	++stringIntIT;
	while(stringIntIT != mStringIntRBST.end())
	{
		EXPECT_LE(previousString, stringIntIT->first);
		previousString = stringIntIT->first;
		++counter;
		++stringIntIT;
	}
	EXPECT_EQ(counter, NUMBER_OF_ELEMENTS - 1);

	counter = 0;
	IntDoubleIterator intDoubleIT = mIntDoubleRBST.begin();
	int previousInt = intDoubleIT->first;
	++intDoubleIT;
	while(intDoubleIT != mIntDoubleRBST.end())
	{
		EXPECT_LE(previousInt, intDoubleIT->first);
		previousInt = intDoubleIT->first;
		++counter;
		++intDoubleIT;
	}
	EXPECT_EQ(counter, NUMBER_OF_ELEMENTS - 1);
}

#endif

TEST_F(RBTTest, Case3_14)
{
	mStringIntRBST.insert(std::make_pair("G", 0));
	mIntDoubleRBST.insert(std::make_pair(10, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("G"), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), black);
}

TEST_F(RBTTest, BlackRootRedChildLeft_15)
{
	mStringIntRBST.insert(std::make_pair("G", 0));
	mStringIntRBST.insert(std::make_pair("F", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("G"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("F"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), red);
}

TEST_F(RBTTest, BlackRootRedChildRight_16)
{
	mStringIntRBST.insert(std::make_pair("G", 0));
	mStringIntRBST.insert(std::make_pair("H", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(11, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("G"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("H"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), red);
}

TEST_F(RBTTest, Case1Left_17)
{
	mStringIntRBST.insert(std::make_pair("G", 0));
	mStringIntRBST.insert(std::make_pair("F", 0));
	mStringIntRBST.insert(std::make_pair("H", 0));
	mStringIntRBST.insert(std::make_pair("E", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));
	mIntDoubleRBST.insert(std::make_pair(11, 0));
	mIntDoubleRBST.insert(std::make_pair(8, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("G"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("F"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("H"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("E"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), red);
}

TEST_F(RBTTest, Case1Right_18)
{
	mStringIntRBST.insert(std::make_pair("G", 0));
	mStringIntRBST.insert(std::make_pair("H", 0));
	mStringIntRBST.insert(std::make_pair("F", 0));
	mStringIntRBST.insert(std::make_pair("I", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(11, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));
	mIntDoubleRBST.insert(std::make_pair(12, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("G"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("H"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("F"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("I"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(12), red);
}

TEST_F(RBTTest, Case2Left_19)
{
	mStringIntRBST.insert(std::make_pair("C", 0));
	mStringIntRBST.insert(std::make_pair("A", 0));
	mStringIntRBST.insert(std::make_pair("D", 0));
	mStringIntRBST.insert(std::make_pair("B", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(11, 0));
	mIntDoubleRBST.insert(std::make_pair(8, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("D"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), red);
}

TEST_F(RBTTest, Case2Right_20)
{
	mStringIntRBST.insert(std::make_pair("B", 0));
	mStringIntRBST.insert(std::make_pair("A", 0));
	mStringIntRBST.insert(std::make_pair("D", 0));
	mStringIntRBST.insert(std::make_pair("C", 0));

	mIntDoubleRBST.insert(std::make_pair(9, 0));
	mIntDoubleRBST.insert(std::make_pair(11, 0));
	mIntDoubleRBST.insert(std::make_pair(8, 0));
	mIntDoubleRBST.insert(std::make_pair(10, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("D"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), red);
}

TEST_F(RBTTest, Case4LeftUncleNull_21)
{
	mStringIntRBST.insert(std::make_pair("C", 0));
	mStringIntRBST.insert(std::make_pair("B", 0));
	mStringIntRBST.insert(std::make_pair("A", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));
	mIntDoubleRBST.insert(std::make_pair(8, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), red);

	ASSERT_FALSE(mStringIntRBST.getRoot() == NULL);
	EXPECT_EQ(mStringIntRBST.getRoot()->getKey(), "B");
	ASSERT_FALSE(mIntDoubleRBST.getRoot() == NULL);
	EXPECT_EQ(mIntDoubleRBST.getRoot()->getKey(), 9);
}

TEST_F(RBTTest, Case4LeftUncleBlack_22)
{
	mStringIntRBST.insert(std::make_pair("C", 0));
	mStringIntRBST.insert(std::make_pair("B", 0));
	mStringIntRBST.insert(std::make_pair("D", 0));
	mStringIntRBST.setNodeColor("D", black);
	mStringIntRBST.insert(std::make_pair("A", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));
	mIntDoubleRBST.insert(std::make_pair(11, 0));
	mIntDoubleRBST.setNodeColor(11, black);
	mIntDoubleRBST.insert(std::make_pair(8, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("D"), black);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), black);

	ASSERT_FALSE(mStringIntRBST.getRoot() == NULL);
	EXPECT_EQ(mStringIntRBST.getRoot()->getKey(), "B");
	ASSERT_FALSE(mIntDoubleRBST.getRoot() == NULL);
	EXPECT_EQ(mIntDoubleRBST.getRoot()->getKey(), 9);
}

TEST_F(RBTTest, Case4RightUncleNull_23)
{
	mStringIntRBST.insert(std::make_pair("A", 0));
	mStringIntRBST.insert(std::make_pair("B", 0));
	mStringIntRBST.insert(std::make_pair("C", 0));

	mIntDoubleRBST.insert(std::make_pair(8, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));
	mIntDoubleRBST.insert(std::make_pair(10, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), red);

	ASSERT_FALSE(mStringIntRBST.getRoot() == NULL);
	EXPECT_EQ(mStringIntRBST.getRoot()->getKey(), "B");
	ASSERT_FALSE(mIntDoubleRBST.getRoot() == NULL);
	EXPECT_EQ(mIntDoubleRBST.getRoot()->getKey(), 9);
}

TEST_F(RBTTest, Case4RightUncleBlack_24)
{
	mStringIntRBST.insert(std::make_pair("B", 0));
	mStringIntRBST.insert(std::make_pair("C", 0));
	mStringIntRBST.insert(std::make_pair("A", 0));
	mStringIntRBST.setNodeColor("A", black);
	mStringIntRBST.insert(std::make_pair("D", 0));

	mIntDoubleRBST.insert(std::make_pair(9, 0));
	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(8, 0));
	mIntDoubleRBST.setNodeColor(8, black);
	mIntDoubleRBST.insert(std::make_pair(11, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("D"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), red);

	ASSERT_FALSE(mStringIntRBST.getRoot() == NULL);
	EXPECT_EQ(mStringIntRBST.getRoot()->getKey(), "C");
	ASSERT_FALSE(mIntDoubleRBST.getRoot() == NULL);
	EXPECT_EQ(mIntDoubleRBST.getRoot()->getKey(), 10);
}

TEST_F(RBTTest, Case5LeftUncleNull_25)
{
	mStringIntRBST.insert(std::make_pair("C", 0));
	mStringIntRBST.insert(std::make_pair("A", 0));
	mStringIntRBST.insert(std::make_pair("B", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(8, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), red);

	ASSERT_FALSE(mStringIntRBST.getRoot() == NULL);
	EXPECT_EQ(mStringIntRBST.getRoot()->getKey(), "B");
	ASSERT_FALSE(mIntDoubleRBST.getRoot() == NULL);
	EXPECT_EQ(mIntDoubleRBST.getRoot()->getKey(), 9);
}

TEST_F(RBTTest, Case5LeftUncleBlack_26)
{
	mStringIntRBST.insert(std::make_pair("C", 0));
	mStringIntRBST.insert(std::make_pair("A", 0));
	mStringIntRBST.insert(std::make_pair("D", 0));
	mStringIntRBST.setNodeColor("D", black);
	mStringIntRBST.insert(std::make_pair("B", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(8, 0));
	mIntDoubleRBST.insert(std::make_pair(11, 0));
	mIntDoubleRBST.setNodeColor(11, black);
	mIntDoubleRBST.insert(std::make_pair(9, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("D"), black);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(8), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), black);

	ASSERT_FALSE(mStringIntRBST.getRoot() == NULL);
	EXPECT_EQ(mStringIntRBST.getRoot()->getKey(), "B");
	ASSERT_FALSE(mIntDoubleRBST.getRoot() == NULL);
	EXPECT_EQ(mIntDoubleRBST.getRoot()->getKey(), 9);
}

TEST_F(RBTTest, Case5RightUncleNull_27)
{
	mStringIntRBST.insert(std::make_pair("B", 0));
	mStringIntRBST.insert(std::make_pair("D", 0));
	mStringIntRBST.insert(std::make_pair("C", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(12, 0));
	mIntDoubleRBST.insert(std::make_pair(11, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("D"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(12), red);

	ASSERT_FALSE(mStringIntRBST.getRoot() == NULL);
	EXPECT_EQ(mStringIntRBST.getRoot()->getKey(), "C");
	ASSERT_FALSE(mIntDoubleRBST.getRoot() == NULL);
	EXPECT_EQ(mIntDoubleRBST.getRoot()->getKey(), 11);
}

TEST_F(RBTTest, Case5RightUncleBlack_28)
{
	mStringIntRBST.insert(std::make_pair("B", 0));
	mStringIntRBST.insert(std::make_pair("D", 0));
	mStringIntRBST.insert(std::make_pair("A", 0));
	mStringIntRBST.setNodeColor("A", black);
	mStringIntRBST.insert(std::make_pair("C", 0));

	mIntDoubleRBST.insert(std::make_pair(10, 0));
	mIntDoubleRBST.insert(std::make_pair(12, 0));
	mIntDoubleRBST.insert(std::make_pair(9, 0));
	mIntDoubleRBST.setNodeColor(9, black);
	mIntDoubleRBST.insert(std::make_pair(11, 0));

	EXPECT_EQ(mStringIntRBST.getNodeColor("A"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("B"), red);
	EXPECT_EQ(mStringIntRBST.getNodeColor("C"), black);
	EXPECT_EQ(mStringIntRBST.getNodeColor("D"), red);

	EXPECT_EQ(mIntDoubleRBST.getNodeColor(9), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(10), red);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(11), black);
	EXPECT_EQ(mIntDoubleRBST.getNodeColor(12), red);

	ASSERT_FALSE(mStringIntRBST.getRoot() == NULL);
	EXPECT_EQ(mStringIntRBST.getRoot()->getKey(), "C");
	ASSERT_FALSE(mIntDoubleRBST.getRoot() == NULL);
	EXPECT_EQ(mIntDoubleRBST.getRoot()->getKey(), 11);
}
