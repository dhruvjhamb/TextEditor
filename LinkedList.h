/*
 * LinkedList.h
 *
 *  Created on: Jun 19, 2018
 *      Author: dhruvjhamb
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>

using namespace std;

class Node {
    friend class LinkedList;
private:
    char value[81];    // Size corresponds to maxLineSize + 1
    Node *prev;
    Node *next;
    int valIndex;
    int tempValIndex;
    int valSize;

public:
    Node(Node *p, Node *n);
    ~Node();
    int getValIndex();
};

class LinkedList {
    friend class Node;
private:
	Node *sentinel;
	Node *currentNode;
	Node *tempNode;

	int tempPos;
	int cursorPos;
	int size;
	int maxLineSize;
	bool shifting;

public:
	LinkedList();
	~LinkedList();

	void addChar(char c);
	void shiftChar(char c);
	void removeChar();

	void addNode(char c, Node *p);
	void addNode();
	void removeNode();

	void printList();
	string toString();

	Node* getCurrentNode();
	int getCursorPos();
	int getSize();
	int getMaxLineSize();

	void decreaseIndex();
	void increaseIndex();
	void decreaseCurrentNode();
	void increaseCurrentNode();
};



#endif /* LINKEDLIST_H_ */
