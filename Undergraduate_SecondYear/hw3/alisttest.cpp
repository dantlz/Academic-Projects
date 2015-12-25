#include "alistint.h"
#include "gtest/gtest.h"

using namespace std;
class ArrayListTest : public testing::Test { protected: AListInt list; };



TEST_F(ArrayListTest, Constructors_Nominal){
	AListInt list1;
	AListInt list2(200);
	AListInt list3(list);
	EXPECT_EQ(list1.empty(),true);
	EXPECT_EQ(list2.empty(),true);
	EXPECT_EQ(list3.empty(),true);
}



TEST_F(ArrayListTest, Empty_Nomial){
	EXPECT_EQ(list.empty(),true);
	list.insert(0,0);
	EXPECT_EQ(list.empty(),false);
}



TEST_F(ArrayListTest, Operator_Equals_Nominal) {
	list.insert(0,1);
	AListInt list2=list;
	EXPECT_EQ(list[0]==list2[0],true);
}



TEST_F(ArrayListTest, Operator_Plus_Nominal) {
	list.insert(0,1);
	AListInt list2(1);
	list2.insert(0,2);
	list=list2+list;
	EXPECT_EQ(list.get(0),2);
	EXPECT_EQ(list.get(1),1);
} 



TEST_F(ArrayListTest,Size_Nominal){
	EXPECT_EQ(list.size(),0);
	for(int i=0;i<300;i++){
		list.insert(i,i);
	}
	EXPECT_EQ(list.size(),300);
}



TEST_F(ArrayListTest, Insert_Nominal){
	list.insert(0,0);
	EXPECT_EQ(list.get(0),0);
	
}
TEST_F(ArrayListTest, Insert_Boundary){
	list.insert(0,0);
	list.insert(1,1);
	EXPECT_EQ(list.get(1),1);
	
}
TEST_F(ArrayListTest, Insert_Off_Nominal){
	list.insert(10,0);
	EXPECT_EQ(list.size(),0);
}



TEST_F(ArrayListTest, Remove_Nominal) {
	list.insert(0,0);
	list.remove(0);
	EXPECT_EQ(list.size(),0);
}
TEST_F(ArrayListTest, Remove_Boundary) {
	list.insert(0,0);
	list.insert(0,1);
	list.remove(0);
	EXPECT_EQ(list.get(0),0);
}
TEST_F(ArrayListTest, Remove_Off_Nominal) {
	list.insert(0,0);
	list.remove(1);
	EXPECT_EQ(list.size(),1);

}



TEST_F(ArrayListTest, Set_Nominal) {
	list.insert(0,0);
	list.set(0,1);
	EXPECT_EQ(list.get(0),1);
}
TEST_F(ArrayListTest, Set_Boundary) {
	list.insert(0,0);
	list.insert(0,1);
	list.set(1, 2);
	EXPECT_EQ(list.get(1),2);
}
TEST_F(ArrayListTest, Set_Off_Nominal) {
	list.insert(0,0);
	list.set(1,100);
	EXPECT_EQ(list.get(0),0);
}



TEST_F(ArrayListTest, Get_Nominal) {
	list.insert(0,0);
	EXPECT_EQ(list.get(0),0);
}
TEST_F(ArrayListTest, Get_Boundary) {
	list.insert(0,0);
	list.insert(1,1);
	EXPECT_EQ(list.get(1),1);
}
TEST_F(ArrayListTest, Get_Off_Boundary) {
	list.insert(0,0);
	EXPECT_EQ(list.get(1),123454321);
}
 


TEST_F(ArrayListTest, Operator_Brackets_Nominal) {
	list.insert(0,0);
	EXPECT_EQ(list[0],0);
}
TEST_F(ArrayListTest, Operator_Brackets_Boundary) {
	list.insert(0,0);
	list.insert(1,1);
	EXPECT_EQ(list[1],1);
}
TEST_F(ArrayListTest, Operator_Brackets_Off_Nominal) {
	list.insert(0,0);
	EXPECT_EQ(list[100],123454321);
} 
  

