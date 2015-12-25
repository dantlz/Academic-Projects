#include "bst.h"
#include "rbbst.h"
#include <iostream>
#include "string"

using namespace std;

int main(){
	RedBlackTree<double,double> aRedBlackTree;
	aRedBlackTree.insert(make_pair(12, 12));
	aRedBlackTree.insert(make_pair(5, 5));
	aRedBlackTree.insert(make_pair(15, 15));
	aRedBlackTree.insert(make_pair(3, 3));
	aRedBlackTree.insert(make_pair(13, 13));
	aRedBlackTree.insert(make_pair(10, 10));
	aRedBlackTree.insert(make_pair(17, 17));
	aRedBlackTree.insert(make_pair(4, 4));
	aRedBlackTree.insert(make_pair(14, 14));
	aRedBlackTree.insert(make_pair(7, 7));
	aRedBlackTree.insert(make_pair(11, 11));
	aRedBlackTree.insert(make_pair(6, 6));
	aRedBlackTree.insert(make_pair(8, 8));
	aRedBlackTree.insert(make_pair(1, 1));
	aRedBlackTree.insert(make_pair(13.5, 13.5));
	aRedBlackTree.insert(make_pair(14.5, 14.5));
	aRedBlackTree.insert(make_pair(9, 9));
	aRedBlackTree.print();

}