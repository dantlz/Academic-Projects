#include "gtest/gtest.h"
#include <functional> 
#include <string>
#include <list>
#include <deque>
#include <vector>

// Change following to include the student's msort.h file here.
#include "mergesort.h"

// Change these typedef statements if students have used a container different
// from a vector.
typedef std::vector<int> IntContainer;
typedef std::vector<std::string> StringContainer;
// typedef std::list<int> IntContainer;
// typedef std::list<std::string> StringContainer;
// typedef std::deque<int> IntContainer;
// typedef std::deque<std::string> StringContainer;

// Change the function call to match the name of the merge sort function provided
// by the student.
#define MERGE_SORT(container, comparator) msort(container, comparator);

#define RUN_WEBPAGE_TEST 0
#if RUN_WEBPAGE_TEST 
	#include "webpage.h"
	#include "myset.h"
	typedef std::vector<WebPage *> WebPageContainer;
	// typedef std::list<WebPage *> WebPageContainer;
	// typedef std::deque<WebPage *> WebPageContainer;
	struct WebPageFileComp
	{
		bool operator()(WebPage *lhs, WebPage *rhs)
		{
			return lhs->filename() < rhs->filename();
		}
	};
#endif

class MSortTest : public testing::Test
{
	protected:
		MSortTest() { }
		~MSortTest() { }
		virtual void SetUp() { }
		virtual void TearDown() { }

		IntContainer mIntContainer;
		StringContainer mStringContainer;

		#if RUN_WEBPAGE_TEST
			WebPageContainer mWebPageContainer;
			WebPageFileComp mWebPageFileComp;
			void DeleteWebPages(WebPageContainer container)
			{
				for(WebPageContainer::iterator it = container.begin(); it != container.end(); ++it)
				{
					delete *it;
				}
				container.clear();
			}
		#endif
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

/*
	These are tests for integers. In total, there are 12 tests for the integers. They are:
	1. IntInOrderLess -- Checks on list that is already sorted in increasing order.
	2. IntInOrderGreater -- Checks on list that is already sorted in decreasing order. 
	3. IntScrambledLess -- Checks on list with scrambled integers, and looks for increasing order. 
	4. IntScrambledGreater -- Checks on list with scrambled integers, and looks for decreasing order.
	5. IntDuplicateLess -- Checks on list with scrambled integers containing duplicates, looking for increasing.
	6. IntDuplicateGreater -- Checks on list with scrambled integers containing duplicates, looks for decreasing.
	7 - 9. IntLarge*Less -- Inserts 10,000/100,000/1,000,000 random integers and looks for increasing order.
	10 - 12. IntLarge*Greater -- Inserts 10,000/100,000/1,000,000 random integers and looks for decreasing order. 
*/

TEST_F(MSortTest, IntInOrderLess_01)
{
	mIntContainer.push_back(0);
	mIntContainer.push_back(1);
	mIntContainer.push_back(2);
	mIntContainer.push_back(3);
	mIntContainer.push_back(4);
	mIntContainer.push_back(5);

	std::less<int> comp;
	MERGE_SORT(mIntContainer, comp)

	int i = 0;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++it, ++i)
	{
		EXPECT_EQ(*it, i);
	}
}

#
TEST_F(MSortTest, IntInOrderGreater_02)
{
	mIntContainer.push_back(5);
	mIntContainer.push_back(4);
	mIntContainer.push_back(3);
	mIntContainer.push_back(2);
	mIntContainer.push_back(1);
	mIntContainer.push_back(0);

	std::greater<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++it, ++i)
	{
		EXPECT_EQ(*it, 5 - i);
	}
}

TEST_F(MSortTest, IntScrambledLess_03)
{
	mIntContainer.push_back(0);
	mIntContainer.push_back(5);
	mIntContainer.push_back(3);
	mIntContainer.push_back(2);
	mIntContainer.push_back(4);
	mIntContainer.push_back(1);

	std::less<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++it, ++i)
	{
		EXPECT_EQ(*it, i);
	}
}

TEST_F(MSortTest, IntScrambledGreater_04)
{
	mIntContainer.push_back(0);
	mIntContainer.push_back(5);
	mIntContainer.push_back(3);
	mIntContainer.push_back(2);
	mIntContainer.push_back(4);
	mIntContainer.push_back(1);

	std::greater<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++it, ++i)
	{
		EXPECT_EQ(*it,  5 - i);
	}
}


TEST_F(MSortTest, IntDuplicateLess_05)
{
	mIntContainer.push_back(0);
	mIntContainer.push_back(1);
	mIntContainer.push_back(3);
	mIntContainer.push_back(3);
	mIntContainer.push_back(1);
	mIntContainer.push_back(5);

	std::less<int> comp;
	MERGE_SORT(mIntContainer, comp);

	IntContainer::iterator it = mIntContainer.begin();
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*it, 0);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 1);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 1);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 3);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 3);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 5);
}

TEST_F(MSortTest, IntDuplicateGreater_06)
{
	mIntContainer.push_back(0);
	mIntContainer.push_back(1);
	mIntContainer.push_back(3);
	mIntContainer.push_back(3);
	mIntContainer.push_back(1);
	mIntContainer.push_back(5);

	std::greater<int> comp;
	MERGE_SORT(mIntContainer, comp);

	IntContainer::iterator it = mIntContainer.begin();
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*it, 5);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 3);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 3);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 1);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 1);
	ASSERT_FALSE(it == mIntContainer.end()); EXPECT_EQ(*(++it), 0);
}

TEST_F(MSortTest, IntLarge10000Less_07)
{
	const int NUMBER_OF_ITEMS = 10000;
	for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
	{
		mIntContainer.push_back(rand());
	}

	std::less<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	int leftValue, rightValue;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++i)
	{
		leftValue = *it;
		*(++it);
		if(it != mIntContainer.end())
		{
			rightValue = *it;
			EXPECT_LE(leftValue, rightValue);
		}
	}

	EXPECT_EQ(i, NUMBER_OF_ITEMS);
}

TEST_F(MSortTest, IntLarge100000Less_08)
{
	const int NUMBER_OF_ITEMS = 100000;
	for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
	{
		mIntContainer.push_back(rand());
	}

	std::less<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	int leftValue, rightValue;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++i)
	{
		leftValue = *it;
		*(++it);
		if(it != mIntContainer.end())
		{
			rightValue = *it;
			EXPECT_LE(leftValue, rightValue);
		}
	}

	EXPECT_EQ(i, NUMBER_OF_ITEMS);
}

TEST_F(MSortTest, IntLarge1000000Less_09)
{
	const int NUMBER_OF_ITEMS = 1000000;
	for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
	{
		mIntContainer.push_back(rand());
	}

	std::less<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	int leftValue, rightValue;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++i)
	{
		leftValue = *it;
		*(++it);
		if(it != mIntContainer.end())
		{
			rightValue = *it;
			EXPECT_LE(leftValue, rightValue);
		}
	}

	EXPECT_EQ(i, NUMBER_OF_ITEMS);
}

TEST_F(MSortTest, IntLarge10000Greater_10)
{
	const int NUMBER_OF_ITEMS = 10000;
	for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
	{
		mIntContainer.push_back(rand());
	}

	std::greater<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	int leftValue, rightValue;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++i)
	{
		leftValue = *it;
		*(++it);
		if(it != mIntContainer.end())
		{
			rightValue = *it;
			EXPECT_GE(leftValue, rightValue);
		}
	}

	EXPECT_EQ(i, NUMBER_OF_ITEMS);
}

TEST_F(MSortTest, IntLarge100000Greater_11)
{
	const int NUMBER_OF_ITEMS = 100000;
	for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
	{
		mIntContainer.push_back(rand());
	}

	std::greater<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	int leftValue, rightValue;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++i)
	{
		leftValue = *it;
		*(++it);
		if(it != mIntContainer.end())
		{
			rightValue = *it;
			EXPECT_GE(leftValue, rightValue);
		}
	}

	EXPECT_EQ(i, NUMBER_OF_ITEMS);
}

TEST_F(MSortTest, IntLarge1000000Greater_12)
{
	const int NUMBER_OF_ITEMS = 1000000;
	for(int i = 0; i < NUMBER_OF_ITEMS; ++i)
	{
		mIntContainer.push_back(rand());
	}

	std::greater<int> comp;
	MERGE_SORT(mIntContainer, comp);

	int i = 0;
	int leftValue, rightValue;
	for(IntContainer::iterator it = mIntContainer.begin(); it != mIntContainer.end(); ++i)
	{
		leftValue = *it;
		*(++it);
		if(it != mIntContainer.end())
		{
			rightValue = *it;
			EXPECT_GE(leftValue, rightValue);
		}
	}

	EXPECT_EQ(i, NUMBER_OF_ITEMS);
}

/*
	These are tests for strings. In total there are 6 tests for strings. They are:
	13. StringInOrderLess -- Checks on list with strings already in increasing order, looking for increasing.
	14. StringInOrderGreater -- Checks on list with strings already inserted in decreasing order, looking for decreasing.
	15. StringScrambledLess -- Checks on list with scrambled strings order, looking for increasing.
	16. StringScrambledGreater -- Checks on list with scrambled strings order, looking for decreasing.
	17. StringDuplicateLess -- Checks on list with scrambled string order and duplicates, looking for increasing.
	18. StringDuplicateGreater -- Checks on list with scrambled string order and duplicates, looking for increasing.
*/

TEST_F(MSortTest, StringInOrderLess_13)
{
	mStringContainer.push_back("Aaron");
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Carla");
	mStringContainer.push_back("David");
	mStringContainer.push_back("Esther");

	std::less<std::string> comp;
	MERGE_SORT(mStringContainer, comp);

	StringContainer::iterator it = mStringContainer.begin();
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*it, "Aaron");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Carla");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "David");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Esther");
}

TEST_F(MSortTest, StringInOrderGreater_14)
{
	mStringContainer.push_back("Esther");
	mStringContainer.push_back("David");
	mStringContainer.push_back("Carla");
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");

	std::greater<std::string> comp;
	MERGE_SORT(mStringContainer, comp);

	StringContainer::iterator it = mStringContainer.begin();
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*it, "Esther");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "David");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Carla");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Aaron");
}

TEST_F(MSortTest, StringScrambledLess_15)
{
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");
	mStringContainer.push_back("Esther");
	mStringContainer.push_back("Carla");
	mStringContainer.push_back("David");

	std::less<std::string> comp;
	MERGE_SORT(mStringContainer, comp);

	StringContainer::iterator it = mStringContainer.begin();
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*it, "Aaron");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Carla");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "David");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Esther");
}

TEST_F(MSortTest, StringScrambledGreater_16)
{
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");
	mStringContainer.push_back("Esther");
	mStringContainer.push_back("Carla");
	mStringContainer.push_back("David");

	std::greater<std::string> comp;
	MERGE_SORT(mStringContainer, comp);

	StringContainer::iterator it = mStringContainer.begin();
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*it, "Esther");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "David");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Carla");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Aaron");
}

TEST_F(MSortTest, StringDuplicateLess_17)
{
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");
	mStringContainer.push_back("Esther");
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");

	std::less<std::string> comp;
	MERGE_SORT(mStringContainer, comp);

	StringContainer::iterator it = mStringContainer.begin();
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*it, "Aaron");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Aaron");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Esther");
}

TEST_F(MSortTest, StringDuplicateGreater_18)
{
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");
	mStringContainer.push_back("Esther");
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");

	std::greater<std::string> comp;
	MERGE_SORT(mStringContainer, comp);

	StringContainer::iterator it = mStringContainer.begin();
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*it, "Esther");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Aaron");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Aaron");
}

/*

*/

#if RUN_WEBPAGE_TEST

TEST_F(MSortTest, WebPageInOrder_19)
{
	mWebPageContainer.push_back(new WebPage("Aaron"));
	mWebPageContainer.push_back(new WebPage("Betty"));
	mWebPageContainer.push_back(new WebPage("Carla"));
	mWebPageContainer.push_back(new WebPage("David"));
	mWebPageContainer.push_back(new WebPage("Esther"));

	MERGE_SORT(mWebPageContainer, mWebPageFileComp);

	WebPageContainer::iterator it = mWebPageContainer.begin();
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*it)->filename(), "Aaron");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Betty");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Carla");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "David");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Esther");

	DeleteWebPages(mWebPageContainer);
}

TEST_F(MSortTest, WebPageReversed_20)
{
	mWebPageContainer.push_back(new WebPage("Esther"));
	mWebPageContainer.push_back(new WebPage("David"));
	mWebPageContainer.push_back(new WebPage("Carla"));
	mWebPageContainer.push_back(new WebPage("Betty"));
	mWebPageContainer.push_back(new WebPage("Aaron"));

	MERGE_SORT(mWebPageContainer, mWebPageFileComp);

	WebPageContainer::iterator it = mWebPageContainer.begin();
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*it)->filename(), "Aaron");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Betty");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Carla");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "David");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Esther");

	DeleteWebPages(mWebPageContainer);
}

TEST_F(MSortTest, WebPageScrambled_21)
{
	mWebPageContainer.push_back(new WebPage("Betty"));
	mWebPageContainer.push_back(new WebPage("Aaron"));
	mWebPageContainer.push_back(new WebPage("Esther"));
	mWebPageContainer.push_back(new WebPage("David"));
	mWebPageContainer.push_back(new WebPage("Carla"));

	MERGE_SORT(mWebPageContainer, mWebPageFileComp);

	WebPageContainer::iterator it = mWebPageContainer.begin();
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*it)->filename(), "Aaron");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Betty");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Carla");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "David");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Esther");

	DeleteWebPages(mWebPageContainer);
}

TEST_F(MSortTest, WebPageDuplicates_22)
{
	mWebPageContainer.push_back(new WebPage("Betty"));
	mWebPageContainer.push_back(new WebPage("Aaron"));
	mWebPageContainer.push_back(new WebPage("Esther"));
	mWebPageContainer.push_back(new WebPage("Betty"));
	mWebPageContainer.push_back(new WebPage("Aaron"));

	MERGE_SORT(mWebPageContainer, mWebPageFileComp);

	WebPageContainer::iterator it = mWebPageContainer.begin();
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*it)->filename(), "Aaron");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Aaron");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Betty");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Betty");
	ASSERT_FALSE(it == mWebPageContainer.end()); EXPECT_EQ((*(++it))->filename(), "Esther");

	DeleteWebPages(mWebPageContainer);
}

#endif

#if 0

TEST_F(MSortTest, StringDuplicateLess_17)
{
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");
	mStringContainer.push_back("Esther");
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");

	std::less<std::string> comp;
	MERGE_SORT(mStringContainer, comp);

	StringContainer::iterator it = mStringContainer.begin();
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*it, "Aaron");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Aaron");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Esther");
}

TEST_F(MSortTest, StringDuplicateGreater_18)
{
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");
	mStringContainer.push_back("Esther");
	mStringContainer.push_back("Betty");
	mStringContainer.push_back("Aaron");

	std::greater<std::string> comp;
	MERGE_SORT(mStringContainer, comp);

	StringContainer::iterator it = mStringContainer.begin();
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*it, "Esther");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Betty");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Aaron");
	ASSERT_FALSE(it == mStringContainer.end()); EXPECT_EQ(*(++it), "Aaron");
}

#endif