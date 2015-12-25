#include <cstdlib>
#include <ctime>
#include "gtest/gtest.h"
#include "split.cpp"

/*struct Node
{
	int value;
	Node *next;
};*/

void PrintList(Node *head)
{
	if(head != NULL)
	{
		std::cout << head->value << std::endl;
		PrintList(head->next);
	}
}

void DeleteList(Node *head)
{
	if(head != NULL)
	{
		Node *temp = head;
		DeleteList(head->next);
		delete temp;
	}
}

class LListIntRecursion : public testing::Test
{
	protected:
		LListIntRecursion() { }
		~LListIntRecursion() { }
		virtual void SetUp() 
		{
			mHead = new Node;
			mSmaller = NULL;
			mLarger = NULL;
		}
		virtual void TearDown() 
		{ 
			DeleteList(mHead);
			DeleteList(mSmaller);
			DeleteList(mLarger);
		}

		Node *mHead;
		Node *mSmaller;
		Node *mLarger;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(LListIntRecursion, EmptyList_01)
{
	delete mHead;
	mHead = NULL;
	mSmaller = NULL;
	mLarger = NULL;
	split(mHead, mSmaller, mLarger, 0);

	EXPECT_TRUE(mHead == NULL);
	EXPECT_TRUE(mSmaller == NULL);
	EXPECT_TRUE(mLarger == NULL);
}

TEST_F(LListIntRecursion, OneElementPivotLess_02)
{
	mHead->value = 10;
	mHead->next = NULL;

	split(mHead, mSmaller, mLarger, 9);

	EXPECT_TRUE(mSmaller == NULL);
	ASSERT_TRUE(mLarger != NULL);
	EXPECT_EQ(mLarger->value, 10);
	EXPECT_TRUE(mHead == NULL);
}

TEST_F(LListIntRecursion, OneElementPivotExact_03)
{
	mHead->value = 10;
	mHead->next = NULL;

	split(mHead, mSmaller, mLarger, 10);

	ASSERT_TRUE(mSmaller != NULL);
	EXPECT_EQ(mSmaller->value, 10);
	EXPECT_TRUE(mLarger == NULL);
	EXPECT_TRUE(mHead == NULL);
}

TEST_F(LListIntRecursion, OneElementPivotGreater_04)
{
	mHead->value = 10;
	mHead->next = NULL;

	split(mHead, mSmaller, mLarger, 11);

	ASSERT_TRUE(mSmaller != NULL);
	EXPECT_EQ(mSmaller->value, 10);
	EXPECT_TRUE(mLarger == NULL);
	EXPECT_TRUE(mHead == NULL);
}

TEST_F(LListIntRecursion, PivotMiddle_05)
{
	mHead->value = 0;
	mHead->next = NULL;

	Node *temp = mHead;
	int numberOfNodes = 20;
	for(int i = 1; i < numberOfNodes; ++i)
	{
		temp->next = new Node;
		temp->next->value = i;
		temp->next->next = NULL;
		temp = temp->next;
	}

	int pivot = 10;
	split(mHead, mSmaller, mLarger, pivot);

	int smaller = 0;
	int larger = 0;
	Node *tempSmaller = mSmaller;
	Node *tempLarger = mLarger;

	while(tempSmaller != NULL)
	{
		EXPECT_LE(tempSmaller->value, pivot);
		tempSmaller = tempSmaller->next;
		++smaller;
	}

	while(tempLarger != NULL)
	{
		EXPECT_GE(tempLarger->value, pivot + 1);
		tempLarger = tempLarger->next;
		++larger;
	}

	EXPECT_EQ(larger + smaller, numberOfNodes);
	EXPECT_TRUE(mHead == NULL);
}

TEST_F(LListIntRecursion, PivotLess_06)
{
	mHead->value = 0;
	mHead->next = NULL;

	Node *temp = mHead;
	int numberOfNodes = 20;
	for(int i = 1; i < numberOfNodes; ++i)
	{
		temp->next = new Node;
		temp->next->value = i;
		temp->next->next = NULL;
		temp = temp->next;
	}

	int pivot = -1;
	split(mHead, mSmaller, mLarger, pivot);

	Node *tempSmaller = mSmaller;
	Node *tempLarger = mLarger;

	int smaller = 0;
	int larger = 0;
	while(tempSmaller != NULL)
	{
		EXPECT_LE(tempSmaller->value, pivot);
		tempSmaller = tempSmaller->next;
		++smaller;
	}

	while(tempLarger != NULL)
	{
		EXPECT_GE(tempLarger->value, pivot + 1);
		tempLarger = tempLarger->next;
		++larger;
	}

	EXPECT_EQ(larger + smaller, numberOfNodes);
	EXPECT_TRUE(mHead == NULL);
}

TEST_F(LListIntRecursion, PivotGreater_07)
{
	mHead->value = 0;
	mHead->next = NULL;

	Node *temp = mHead;
	int numberOfNodes = 20;
	for(int i = 1; i < numberOfNodes; ++i)
	{
		temp->next = new Node;
		temp->next->value = i;
		temp->next->next = NULL;
		temp = temp->next;
	}

	int pivot = 21;
	split(mHead, mSmaller, mLarger, pivot);

	Node *tempSmaller = mSmaller;
	Node *tempLarger = mLarger;

	int smaller = 0;
	int larger = 0;
	while(tempSmaller != NULL)
	{
		EXPECT_LE(tempSmaller->value, pivot);
		tempSmaller = tempSmaller->next;
		++smaller;
	}

	while(tempLarger != NULL)
	{
		EXPECT_GE(tempLarger->value, pivot + 1);
		tempLarger = tempLarger->next;
		++larger;
	}

	EXPECT_EQ(smaller + larger, numberOfNodes);
	EXPECT_TRUE(mHead == NULL);
}

TEST_F(LListIntRecursion, LargeInputRandomPivot_08)
{
	srand(time(NULL));

	const int NUMBER_OF_NODES = 100000;
	const int MAX_VALUE = 10000;
	const int PIVOT = rand() % MAX_VALUE;

	mHead->value = rand() % MAX_VALUE;
	mHead->next = NULL;

	Node *temp = mHead;
	for(int i = 1; i < NUMBER_OF_NODES; ++i)
	{
		temp->next = new Node;
		temp->next->value = rand() % MAX_VALUE;
		temp->next->next = NULL;
		temp = temp->next;
	}

	split(mHead, mSmaller, mLarger, PIVOT);

	Node *tempSmaller = mSmaller;	int smaller = 0;
	Node *tempLarger = mLarger;		int larger = 0;

	while(tempSmaller != NULL)
	{
		EXPECT_LE(tempSmaller->value, PIVOT);
		tempSmaller = tempSmaller->next;
		++smaller;
	}

	while(tempLarger != NULL)
	{
		EXPECT_GE(tempLarger->value, PIVOT + 1);
		tempLarger = tempLarger->next;
		++larger;
	}

	EXPECT_EQ(smaller + larger, NUMBER_OF_NODES);
}