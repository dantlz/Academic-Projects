/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */
#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType> {
	
protected:
	Color color;
public:;
	RedBlackNode(KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p) : Node<KeyType, ValueType> (k, v, p){ 
		color = red; 
	}

	virtual ~RedBlackNode(){}

	Color getColor()const{ 
		return color; 
	}

	void setColor(Color c){ 
		color = c; 
	}

	virtual RedBlackNode<KeyType, ValueType> *getParent () const { 
		return (RedBlackNode<KeyType,ValueType>*) this->_parent; 
	}

	virtual RedBlackNode<KeyType, ValueType> *getLeft () const{ 
		return (RedBlackNode<KeyType,ValueType>*) this->_left; 
	}

	virtual RedBlackNode<KeyType, ValueType> *getRight () const{ 
		return (RedBlackNode<KeyType,ValueType>*) this->_right; 
	}
	RedBlackNode<KeyType, ValueType>* getUncle() {
		RedBlackNode<KeyType, ValueType>* grandpa = this->getParent()->getParent();
		if(grandpa){
			if(grandpa->isFull()){
				if(grandpa->getLeft() == this->getParent())
					return grandpa->getRight();
				else
					return this->getParent()->getParent()->getLeft();
			}
			else{
				return NULL;
			}
		}
		else{
			return NULL;
		}
	}

	bool leftFree(){
		if(this->getLeft()){
			return false;
		}
		return true;
	}

	bool rightFree(){
		if(this->getRight()){
			return false;
		}
		return true;
	}

	bool isFull(){
		return (this->leftFree() + this->rightFree() == 0);
	}
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType> {
public:

	void undoZigZag(RedBlackNode<KeyType, ValueType>* node){
		RedBlackNode<KeyType, ValueType>* parent = node->getParent();
		RedBlackNode<KeyType, ValueType>* grandParent = parent->getParent();
		bool parentOnLeft = false;
		if(grandParent){
			if(grandParent->getLeft() == parent)
				parentOnLeft = true;
		}
		bool isLeftChild = false;
		if(parent->getLeft() == node)
			isLeftChild = true;

		node->setParent(grandParent);
		if(grandParent){
			if(parentOnLeft)
				grandParent->setLeft(node);
			else{
				grandParent->setRight(node);
			}
		}
		parent->setParent(node);

		if(!isLeftChild){
			parent->setRight(node->getLeft());
			if(node->getLeft())
				node->getLeft()->setParent(parent);
			node->setLeft(parent);
		}
		else{
			parent->setLeft(node->getRight());
			if(node->getRight())
				node->getRight()->setParent(parent);
			node->setRight(parent);
		}


		rotate(parent);
	}

	void rotate(RedBlackNode<KeyType, ValueType>* node){
		RedBlackNode<KeyType, ValueType>* parent = node->getParent();
		RedBlackNode<KeyType, ValueType>* grandParent = parent->getParent();
		bool parentOnLeft = false;
		if(grandParent->getLeft() == parent)
			parentOnLeft = true;
		bool isLeftChild = false;
		if(parent->getLeft() == node)
			isLeftChild = true;
		bool zigZag = false;
		if( parentOnLeft + isLeftChild == 1)
			zigZag = true;

		if(zigZag){
			undoZigZag(node);
			return;
		}

		if(this->root == grandParent)
			this->root = parent;
		//Change colors
		grandParent->setColor(red);
		parent->setColor(black);

		//Change parents
		parent->setParent(grandParent->getParent());

		if(grandParent->getParent()){
			RedBlackNode<KeyType, ValueType>* greatGrandParent = grandParent->getParent();
			if(greatGrandParent->getLeft() == grandParent)
				greatGrandParent->setLeft(parent);
			else
				greatGrandParent->setRight(parent);
		}
		grandParent->setParent(parent);

		//There is a sibling that needs to be adopted by the grandparent
		if(parent->isFull()){
			RedBlackNode<KeyType, ValueType>* transfer;
			//This is the left node
			if(!isLeftChild){
				transfer = parent->getLeft();
				parent->setLeft(grandParent);
			}
			//This is the right node
			else{
				transfer = parent->getRight();
				parent->setRight(grandParent);
			}

			if(parentOnLeft)
				grandParent->setLeft(transfer);
			else
				grandParent->setRight(transfer);
			transfer->setParent(grandParent);

		}
		//There is no sibling, connect parent's free side to grandParent
		else{
			//This is the left node
			if(parent->rightFree()){
				parent->setRight(grandParent);
			}
			else{
				parent->setLeft(grandParent);
			}

			if(parentOnLeft)
				grandParent->setLeft(NULL);
			else
				grandParent->setRight(NULL);
		}
		//isValid(parent);
	}

	void recolor(RedBlackNode<KeyType, ValueType>* node){
		node->getParent()->setColor(black);
		node->getUncle()->setColor(black);
		if(node->getParent()->getParent() != this->root){
			node->getParent()->getParent()->setColor(red);
		}
		isValid((node->getParent())->getParent());
	}

	void isValid(RedBlackNode<KeyType, ValueType>* node){
		if(node->getColor() == black){
			return;
		}

		if(node->getParent()==NULL){
			return;
		}

		if(node->getParent()->getColor() == black){
			return;
		}

		//Parent is red
		RedBlackNode<KeyType, ValueType>* uncle = (RedBlackNode<KeyType, ValueType>*)node->getUncle();
		if(uncle){
			//Red Uncle: Recolor
			if(uncle->getColor() == red){
				recolor(node);
			}
			//Black Uncle: Rotate
			else{
				rotate(node);
			}
		}
		//No Uncle: Rotate
		else{
			rotate(node);
		}
	}

	void insert (const std::pair<const KeyType, ValueType>& new_item){
		RedBlackNode<KeyType, ValueType>* newNode = new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, NULL);
		//Empty tree
		if(this->root == NULL){
			//Create the new node with the parent being NULL
			newNode->setColor(black);
			this->root = newNode;
			return;
		}
		//Key already exists
		RedBlackNode<KeyType, ValueType>* result = (RedBlackNode<KeyType, ValueType>*)(this->internalFind(new_item.first));
		if(result){
			result->setValue(new_item.second);
			delete newNode;
			return;
		}
		RedBlackNode<KeyType, ValueType>* current = (RedBlackNode<KeyType, ValueType>*) (this->root);
		while(true){
			if(current->getKey() < newNode->getKey()){
				if(current->getRight()){
					current = current->getRight();
				}
				else{
					current->setRight(newNode);
					newNode->setParent(current);
					isValid(newNode);
					return;
				}
			}
			else{
				if(current->getLeft()){
					current = current->getLeft();
				}
				else{
					current->setLeft(newNode);
					newNode->setParent(current);
					isValid(newNode);
					return;
				}
			}
		}
	}
};

#endif
