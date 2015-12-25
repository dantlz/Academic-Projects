#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "alistint.h"

const int DEFAULT_CAP = 5;
const int CUSTOM_CAP = 20;

class AListIntTest : public testing::Test
{
	protected:
		AListIntTest() : mCustomAListInt(CUSTOM_CAP) { }
		~AListIntTest() { }
		virtual void SetUp() 
		{

		}
		virtual void TearDown() 
		{ 
			
		}

		AListInt mDefaultAListInt;
		AListInt mCustomAListInt;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(AListIntTest, InitiallyEmpty_01)
{
	EXPECT_TRUE(mDefaultAListInt.empty());
	EXPECT_TRUE(mCustomAListInt.empty());
}

TEST_F(AListIntTest, InitialSizeZero_02)
{
	EXPECT_EQ(mDefaultAListInt.size(), 0);
	EXPECT_EQ(mCustomAListInt.size(), 0);
}

TEST_F(AListIntTest, SingleInsertEmpty_03)
{
	mDefaultAListInt.insert(0, 10);
	mCustomAListInt.insert(0, 10);
	EXPECT_FALSE(mDefaultAListInt.empty());
	EXPECT_FALSE(mCustomAListInt.empty());
}

TEST_F(AListIntTest, SingleInsertSize_04)
{
	mDefaultAListInt.insert(0, 10);
	mCustomAListInt.insert(0, 10);
	EXPECT_EQ(mDefaultAListInt.size(), 1);
	EXPECT_EQ(mCustomAListInt.size(), 1);
}

TEST_F(AListIntTest, SingleInsertGet_05)
{
	mDefaultAListInt.insert(0, 10);
	mCustomAListInt.insert(0, 10);
	EXPECT_EQ(mDefaultAListInt.get(0), 10);
	EXPECT_EQ(mCustomAListInt.get(0), 10);
}

TEST_F(AListIntTest, SingleInsertSetGet_06)
{
	mDefaultAListInt.insert(0, 5);
	mCustomAListInt.insert(0, 5);
	mDefaultAListInt.set(0, 10);
	mCustomAListInt.set(0, 10);
	EXPECT_EQ(mDefaultAListInt.get(0), 10);
	EXPECT_EQ(mCustomAListInt.get(0), 10);
}

TEST_F(AListIntTest, SingleInsertRemoveEmpty_07)
{
	mDefaultAListInt.insert(0, 10);
	mCustomAListInt.insert(0, 10);
	mDefaultAListInt.remove(0);
	mCustomAListInt.remove(0);
	EXPECT_TRUE(mDefaultAListInt.empty());
	EXPECT_TRUE(mCustomAListInt.empty());
}

TEST_F(AListIntTest, SingleInsertRemoveSize_08)
{
	mDefaultAListInt.insert(0, 10);
	mCustomAListInt.insert(0, 10);
	mDefaultAListInt.remove(0);
	mCustomAListInt.remove(0);
	EXPECT_EQ(mDefaultAListInt.size(), 0);
	EXPECT_EQ(mCustomAListInt.size(), 0);
}

TEST_F(AListIntTest, MultipleInsertHeadSize_09)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}
	EXPECT_EQ(mDefaultAListInt.size(), DEFAULT_CAP - 1);
	EXPECT_EQ(mCustomAListInt.size(), CUSTOM_CAP - 1);
}

TEST_F(AListIntTest, MultipleInsertTailSize_10)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size(), i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size(), i);
	}
	EXPECT_EQ(mDefaultAListInt.size(), DEFAULT_CAP - 1);
	EXPECT_EQ(mCustomAListInt.size(), CUSTOM_CAP - 1);
}

TEST_F(AListIntTest, MultipleInsertMiddleSize_11)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size() / 2, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size() / 2, i);
	}
	EXPECT_EQ(mDefaultAListInt.size(), DEFAULT_CAP - 1);
	EXPECT_EQ(mCustomAListInt.size(), CUSTOM_CAP - 1);
}

TEST_F(AListIntTest, MultipleInsertHeadCheckOrder_12)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}
	
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		EXPECT_EQ(mDefaultAListInt.get(DEFAULT_CAP - 2 - i), i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		EXPECT_EQ(mCustomAListInt.get(CUSTOM_CAP - 2 - i), i);
	}
}

TEST_F(AListIntTest, MultipleInsertTailCheckOrder_13)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size(), i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size(), i);
	}
	
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		EXPECT_EQ(mDefaultAListInt.get(i), i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		EXPECT_EQ(mCustomAListInt.get(i), i);
	}
}

TEST_F(AListIntTest, MultipleInsertMiddleCheckOrder_14)
{
	// Inserts elements into the two lists.
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size() / 2, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size() / 2, i);
	}

	// Checks the order of the elements in the default list by
	// checking forward and backward. 
	for(int i = 0; i < (DEFAULT_CAP - 1) / 2; ++i)
	{
		EXPECT_EQ(mDefaultAListInt.get(i), 2 * i + 1);
	}
	int value = 0;
	for(int i = DEFAULT_CAP - 2; i >= (DEFAULT_CAP - 1) / 2; --i)
	{
		EXPECT_EQ(mDefaultAListInt.get(i), value);
		value += 2;
	}

	// Checks the order of the elements in the custom list by
	// checking forward and backward. 
	for(int i = 0; i < (CUSTOM_CAP - 1) / 2; ++i)
	{
		EXPECT_EQ(mCustomAListInt.get(i), 2 * i + 1);
	}
	value = 0;
	for(int i = CUSTOM_CAP - 2; i >= (CUSTOM_CAP - 1) / 2; --i)
	{
		EXPECT_EQ(mCustomAListInt.get(i), value);
		value += 2;
	}
}

TEST_F(AListIntTest, MultipleInsertRemoveUntilEmptyHead_15)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size(), i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size(), i);
	}

	int value = 0;
	while(!mDefaultAListInt.empty())
	{
		EXPECT_EQ(mDefaultAListInt.get(0), value++);
		mDefaultAListInt.remove(0);
	}
	EXPECT_EQ(value, DEFAULT_CAP - 1);
	value = 0;
	while(!mCustomAListInt.empty())
	{
		EXPECT_EQ(mCustomAListInt.get(0), value++);
		mCustomAListInt.remove(0);
	}
	EXPECT_EQ(value, CUSTOM_CAP - 1);
}

TEST_F(AListIntTest, MultipleInsertRemoveUntilEmptyTail_16)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size(), i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size(), i);
	}

	int value = DEFAULT_CAP - 2;
	while(!mDefaultAListInt.empty())
	{
		EXPECT_EQ(mDefaultAListInt.get(mDefaultAListInt.size() - 1), value--);
		mDefaultAListInt.remove(mDefaultAListInt.size() - 1);
	}
	EXPECT_EQ(value, -1);
	value = CUSTOM_CAP - 2;
	while(!mCustomAListInt.empty())
	{
		EXPECT_EQ(mCustomAListInt.get(mCustomAListInt.size() - 1), value--);
		mCustomAListInt.remove(mCustomAListInt.size() - 1);
	}
	EXPECT_EQ(value, -1);
}

TEST_F(AListIntTest, MultipleInsertRemoveUntilEmptyMiddle_17)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size(), i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size(), i);
	}

	int numberOfElementsRemoved = 0;
	while(!mDefaultAListInt.empty())
	{
		++numberOfElementsRemoved;
		mDefaultAListInt.remove(mDefaultAListInt.size() / 2);
	}
	EXPECT_EQ(numberOfElementsRemoved, DEFAULT_CAP - 1);
	EXPECT_TRUE(mDefaultAListInt.empty());

	numberOfElementsRemoved = 0;
	while(!mCustomAListInt.empty())
	{
		++numberOfElementsRemoved;
		mCustomAListInt.remove(mCustomAListInt.size() / 2);
	}
	EXPECT_EQ(numberOfElementsRemoved, CUSTOM_CAP - 1);
	EXPECT_TRUE(mCustomAListInt.empty());
}

TEST_F(AListIntTest, DefaultResize_18)
{
	for(int i = 0; i < DEFAULT_CAP + 1; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size(), i);
	}

	for(int i = 0; i < DEFAULT_CAP + 1; ++i)
	{
		EXPECT_EQ(mDefaultAListInt.get(i), i);
	}
	EXPECT_EQ(mDefaultAListInt.size(), DEFAULT_CAP + 1);
}

TEST_F(AListIntTest, CustomResize_19)
{
	for(int i = 0; i < CUSTOM_CAP + 1; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size(), i);
	}

	for(int i = 0; i < CUSTOM_CAP + 1; ++i)
	{
		EXPECT_EQ(mCustomAListInt.get(i), i);
	}
	EXPECT_EQ(mCustomAListInt.size(), CUSTOM_CAP + 1);
}

TEST_F(AListIntTest, DefaultResizex2_20)
{
	for(int i = 0; i < (DEFAULT_CAP + 1) * 2; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size(), i);
	}

	for(int i = 0; i < (DEFAULT_CAP + 1) * 2; ++i)
	{
		EXPECT_EQ(mDefaultAListInt.get(i), i);
	}
	EXPECT_EQ(mDefaultAListInt.size(), (DEFAULT_CAP + 1) * 2);
}

TEST_F(AListIntTest, CustomResizex2_21)
{
	for(int i = 0; i < (CUSTOM_CAP + 1) * 2; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size(), i);
	}

	for(int i = 0; i < (CUSTOM_CAP + 1) * 2; ++i)
	{
		EXPECT_EQ(mCustomAListInt.get(i), i);
	}
	EXPECT_EQ(mCustomAListInt.size(), (CUSTOM_CAP + 1) * 2);
}

TEST_F(AListIntTest, SingleInsertConstBracketOperator_22)
{
	mDefaultAListInt.insert(0, 10);
	mCustomAListInt.insert(0, 10);
	const int firstItem = mDefaultAListInt[0];
	const int customFirstItem = mCustomAListInt[0];
	EXPECT_EQ(firstItem, 10);
	EXPECT_EQ(customFirstItem, 10);
}

TEST_F(AListIntTest, SingleInsertNonConstBracketOperator_23)
{
	mDefaultAListInt.insert(0, 10);
	mCustomAListInt.insert(0, 10);
	mDefaultAListInt[0] = 15;
	mCustomAListInt[0] = 15;
	EXPECT_EQ(mDefaultAListInt[0], 15);
	EXPECT_EQ(mCustomAListInt[0], 15);
}

TEST_F(AListIntTest, MultipleInsertHeadConstBracketOperatorCheckOrder_24)
{
	// Insert elements without resizing. 
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}
	
	// Check order of elements. 
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		const int value = mDefaultAListInt[DEFAULT_CAP - 2 - i];
		EXPECT_EQ(value, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		const int value = mCustomAListInt[CUSTOM_CAP - 2 - i];
		EXPECT_EQ(value, i);
	}
}

TEST_F(AListIntTest, MultipleInsertHeadNonConstBracketOperatorCheckOrder_25)
{
	// Insert elements without resizing. 
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}
	
	// Multiply all elements by 2 using access with the [] operator, 
	// and then check their value. 
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt[DEFAULT_CAP - 2 - i] *= 2;
		EXPECT_EQ(mDefaultAListInt[DEFAULT_CAP - 2 - i], 2 * i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt[CUSTOM_CAP - 2 - i] *= 2;
		EXPECT_EQ(mCustomAListInt[CUSTOM_CAP - 2 - i], 2 * i);
	}
}

TEST_F(AListIntTest, CopyConstructorWithEmptyListsEmptySize_26)
{
	AListInt defaultCopy(mDefaultAListInt);
	AListInt customCopy(mCustomAListInt);

	EXPECT_TRUE(defaultCopy.empty());
	EXPECT_TRUE(customCopy.empty());
	EXPECT_EQ(defaultCopy.size(), 0);
	EXPECT_EQ(customCopy.size(), 0);
}

TEST_F(AListIntTest, CopyConstructorWithFullListsEmptySize_27)
{
	for(int i = 0; i < DEFAULT_CAP; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy(mDefaultAListInt);
	AListInt customCopy(mCustomAListInt);

	EXPECT_FALSE(defaultCopy.empty());
	EXPECT_FALSE(customCopy.empty());
	EXPECT_EQ(defaultCopy.size(), DEFAULT_CAP);
	EXPECT_EQ(customCopy.size(), CUSTOM_CAP);
}

TEST_F(AListIntTest, CopyConstructorWithFullListsCheckOrder_28)
{
	for(int i = 0; i < DEFAULT_CAP; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy(mDefaultAListInt);
	AListInt customCopy(mCustomAListInt);

	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		EXPECT_EQ(defaultCopy[i], mDefaultAListInt[i]);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		EXPECT_EQ(customCopy[i], mCustomAListInt[i]);
	}
}

TEST_F(AListIntTest, CopyConstructorPostModifySize_29)
{
	for(int i = 0; i < DEFAULT_CAP; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy(mDefaultAListInt);
	AListInt customCopy(mCustomAListInt);

	defaultCopy.insert(0, -10);
	customCopy.insert(0, -10);

	EXPECT_EQ(defaultCopy.size(), mDefaultAListInt.size() + 1);
	EXPECT_EQ(customCopy.size(), mCustomAListInt.size() + 1);
}

TEST_F(AListIntTest, CopyConstructorPostModifyCheckElements_30)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy(mDefaultAListInt);
	AListInt customCopy(mCustomAListInt);

	for(int i = 0; i < defaultCopy.size(); ++i)
	{
		defaultCopy[i] = -10;
	}
	for(int i = 0; i < customCopy.size(); ++i)
	{
		customCopy[i] = -20;
	}

	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		EXPECT_EQ(mDefaultAListInt.get(DEFAULT_CAP - 2 - i), i);
		EXPECT_EQ(defaultCopy[i], -10);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		EXPECT_EQ(mCustomAListInt.get(CUSTOM_CAP - 2 - i), i);
		EXPECT_EQ(customCopy[i], -20);
	}
}

TEST_F(AListIntTest, AssignmentOperatorWithEmptyListsEmptySize_31)
{
	AListInt defaultCopy;
	defaultCopy = mDefaultAListInt;
	AListInt customCopy;
	customCopy = mCustomAListInt;

	EXPECT_TRUE(defaultCopy.empty());
	EXPECT_TRUE(customCopy.empty());
	EXPECT_EQ(defaultCopy.size(), 0);
	EXPECT_EQ(customCopy.size(), 0);
}

TEST_F(AListIntTest, AssignmentOperatorWithFullListsEmptySize_32)
{
	for(int i = 0; i < DEFAULT_CAP; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy;
	defaultCopy = mDefaultAListInt;
	AListInt customCopy;
	customCopy = mCustomAListInt;

	EXPECT_FALSE(defaultCopy.empty());
	EXPECT_FALSE(customCopy.empty());
	EXPECT_EQ(defaultCopy.size(), DEFAULT_CAP);
	EXPECT_EQ(customCopy.size(), CUSTOM_CAP);
}

TEST_F(AListIntTest, AssignmentOperatorWithFullListsCheckOrder_33)
{
	for(int i = 0; i < DEFAULT_CAP; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy;
	defaultCopy = mDefaultAListInt;
	AListInt customCopy;
	customCopy = mCustomAListInt;

	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		EXPECT_EQ(defaultCopy[i], mDefaultAListInt[i]);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		EXPECT_EQ(customCopy[i], mCustomAListInt[i]);
	}
}

TEST_F(AListIntTest, AssignmentOperatorPostModifySize_34)
{
	for(int i = 0; i < DEFAULT_CAP; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy;
	defaultCopy = mDefaultAListInt;
	AListInt customCopy;
	customCopy = mCustomAListInt;

	defaultCopy.insert(0, -10);
	customCopy.insert(0, -10);

	EXPECT_EQ(defaultCopy.size(), mDefaultAListInt.size() + 1);
	EXPECT_EQ(customCopy.size(), mCustomAListInt.size() + 1);
}

TEST_F(AListIntTest, AssignmentOperatorPostModifyCheckElements_35)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy;
	defaultCopy = mDefaultAListInt;
	AListInt customCopy;
	customCopy = mCustomAListInt;

	for(int i = 0; i < defaultCopy.size(); ++i)
	{
		defaultCopy[i] = -10;
	}
	for(int i = 0; i < customCopy.size(); ++i)
	{
		customCopy[i] = -20;
	}

	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		EXPECT_EQ(mDefaultAListInt.get(DEFAULT_CAP - 2 - i), i);
		EXPECT_EQ(defaultCopy[i], -10);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		EXPECT_EQ(mCustomAListInt.get(CUSTOM_CAP - 2 - i), i);
		EXPECT_EQ(customCopy[i], -20);
	}
}

TEST_F(AListIntTest, AssignmentOperatorSmallerToLargerSize_36)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy;
	AListInt customCopy;

	for(int i = 0; i < DEFAULT_CAP * 2; ++i)
	{
		defaultCopy.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP * 2; ++i)
	{
		customCopy.insert(0, i);
	}

	defaultCopy = mDefaultAListInt;
	customCopy = mCustomAListInt;

	EXPECT_EQ(defaultCopy.size(), mDefaultAListInt.size());
	EXPECT_EQ(customCopy.size(), mCustomAListInt.size());
}

TEST_F(AListIntTest, AssignmentOperatorLargerToSmallerCheckElements_37)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy;
	AListInt customCopy;

	for(int i = 0; i < DEFAULT_CAP / 2; ++i)
	{
		defaultCopy.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP / 2; ++i)
	{
		customCopy.insert(0, i);
	}

	defaultCopy = mDefaultAListInt;
	customCopy = mCustomAListInt;

	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		EXPECT_EQ(defaultCopy[i], mDefaultAListInt[i]);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		EXPECT_EQ(customCopy[i], mCustomAListInt[i]);
	}
}

TEST_F(AListIntTest, AssignmentOperatorSmallerToLargerCheckElements_38)
{
	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		mDefaultAListInt.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		mCustomAListInt.insert(0, i);
	}

	AListInt defaultCopy;
	AListInt customCopy;

	for(int i = 0; i < DEFAULT_CAP * 2; ++i)
	{
		defaultCopy.insert(0, i);
	}
	for(int i = 0; i < CUSTOM_CAP * 2; ++i)
	{
		customCopy.insert(0, i);
	}

	defaultCopy = mDefaultAListInt;
	customCopy = mCustomAListInt;

	for(int i = 0; i < DEFAULT_CAP - 1; ++i)
	{
		EXPECT_EQ(defaultCopy[i], mDefaultAListInt[i]);
	}
	for(int i = 0; i < CUSTOM_CAP - 1; ++i)
	{
		EXPECT_EQ(customCopy[i], mCustomAListInt[i]);
	}
}

TEST_F(AListIntTest, ConcatenateOperatorEmptyListsSizeEmpty_39)
{
	AListInt concatenatedList = mDefaultAListInt + mCustomAListInt;
	EXPECT_EQ(concatenatedList.size(), mDefaultAListInt.size() + mCustomAListInt.size());
	EXPECT_TRUE(concatenatedList.empty());
}

TEST_F(AListIntTest, ConcatenateOperatorCheckOrder_40)
{
	for(int i = 0; i < DEFAULT_CAP; ++i)
	{
		mDefaultAListInt.insert(mDefaultAListInt.size(), i);
	}
	for(int i = 0; i < CUSTOM_CAP; ++i)
	{
		mCustomAListInt.insert(mCustomAListInt.size(), i + DEFAULT_CAP);
	}

	AListInt concatenatedList = mDefaultAListInt + mCustomAListInt;

	EXPECT_EQ(concatenatedList.size(), mDefaultAListInt.size() + mCustomAListInt.size());

	for(int i = 0; i < concatenatedList.size(); ++i)
	{
		EXPECT_EQ(concatenatedList[i], i);
		if(i < DEFAULT_CAP)
		{
			EXPECT_EQ(mDefaultAListInt[i], i);
		}
		else
		{
			EXPECT_EQ(mCustomAListInt[i - DEFAULT_CAP], i);
		}
	}
}
