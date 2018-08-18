/*
 * LinkedList.cpp
 *
 *  Created on: Jun 19, 2018
 *      Author: dhruvjhamb
 */

#include "LinkedList.h"
#include <iostream>

using namespace std;

/**
 * Node constructor.
 * @param p
 * @param n
 */
Node::Node(Node *p, Node *n) {
    for (int i = 0; i < 80; i++) {
        value[i] = '\0';
    }
    prev = p;
    next = n;
    valIndex = 0;
    tempValIndex = 0;
    valSize = 0;
}

int Node::getValIndex() {
    return valIndex;
}

/**
 * LinkedList constructor.
 */
LinkedList::LinkedList() {
    /*
     * Sets up first node
     */
	sentinel = new Node(0, 0);
    Node *x = new Node(sentinel, sentinel);
    sentinel->prev = x;
    sentinel->next = x;
    currentNode = x;

    maxLineSize = 80;
    tempPos = 1;
    cursorPos = 1;
    size = 1;
	shifting = false;
}

/**
 * Adds char c to the currentNode's value array and increments currentNode's valIndex.
 * If shifting over elements of value array, calls shiftChar().
 * If currentNode's value array is full, then adds a new Node to the LinkedList.
 * @param c
 */
void LinkedList::addChar(char c) {
    if (currentNode->valIndex >= maxLineSize) {
        if (cursorPos == size) {
            cursorPos++;
            addNode(c, currentNode);
        } else {
            cursorPos++;
            currentNode = currentNode->next;
            currentNode->valIndex = 0;
            addChar(c);
        }
    } else {
        char d = currentNode->value[currentNode->valIndex];
        if (d != '\0') {
            shifting = true;
        }
        currentNode->value[currentNode->valIndex] = c;
        currentNode->valIndex++;
        currentNode->valSize++;
        if (shifting) {
            tempNode = currentNode;
            tempNode->tempValIndex = currentNode->valIndex;
            tempPos = cursorPos;
            shiftChar(d);
        }
    }
}

/**
 * Replaces char d at tempValIndex in tempNode's value array with char c.
 * Recursively calls itself with char d as parameter.
 * If tempNode's value array is full, adds a new Node.
 * @param c
 */
void LinkedList::shiftChar(char c) {
    if (tempNode->tempValIndex >= maxLineSize) {
        if (tempPos == size) {
            if (c == '\0') {
                shifting = false;
            } else {
                tempPos++;
                addNode(c, tempNode);
            }
        } else {
            tempNode = tempNode->next;
            tempPos++;
            tempNode->tempValIndex = 0;
            shiftChar(c);
        }
    } else {
        char d = tempNode->value[tempNode->tempValIndex];
        tempNode->value[tempNode->tempValIndex] = c;
        tempNode->tempValIndex++;
        shiftChar(d);
    }
}

/**
 * Adds a Node to the LinkedList and then adds char to the value array of the new Node.
 * @param c
 * @param p
 */
void LinkedList::addNode(char c, Node *p) {
    p->value[maxLineSize] = '\n';
    Node *x = new Node(p, sentinel);
    sentinel->prev = x;
    p->next = x;
    size++;
    if (shifting) {
        tempNode = x;
        shiftChar(c);
    } else {
        currentNode = x;
        addChar(c);
    }
}

/**
 * Adds a Node.
 */
void LinkedList::addNode() {
    Node *x = new Node(currentNode, currentNode->next);
    currentNode->next->prev = x;
    currentNode->next = x;
    //currentNode->value[maxLineSize] = '\n';
    currentNode = x;
    cursorPos++;
    size++;
}

/**
 * Removes the last char from the currentNode's value array and decrements currentNode's valIndex.
 * If currentNode's value array is empty, then removes the last Node.
 */
void LinkedList::removeChar() {
    if (currentNode->valIndex != 0) {
        currentNode->valIndex--;
        currentNode->valSize--;
        currentNode->value[currentNode->valIndex] = '\0';
    } else {
        if (size != 1) {
            removeNode();
        }
    }
}

/**
 * Removes the last Node from the LinkedList and then removes the last char from the value array
 * of the new last Node.
 */
void LinkedList::removeNode() {
    currentNode = currentNode->prev;
    currentNode->next = sentinel;
    sentinel->prev = currentNode;
    size--;
    //removeChar();
}

/**
 * Prints each Node's value array.
 */
void LinkedList::printList() {
    Node *ptr = sentinel->next;
    int i = 0;
    while (i < size) {
        for (int k = 0; k < maxLineSize; k++) {
            cout << ptr->value[k];
        }
        cout << endl;
        ptr = ptr->next;
        i++;
    }
}

/**
 * Converts contents of LinkedList to a string.
 * @return
 */
std::string LinkedList::toString() {
    Node *ptr = sentinel->next;
    int i = 0;
    string s = "";
    while (i < size) {
        for (int k = 0; k < maxLineSize + 1; k++) {
            if (ptr->value[k] == '\0') {
                if (i != size - 1) {
                    s += "";
                }
            } else {
                s += ptr->value[k];
            }
        }
        ptr = ptr->next;
        i++;
    }
    return s;
}

/**
 * Returns the size (the number of nodes) of the LinkedList.
 * @return
 */
int LinkedList::getSize() {
    return size;
}

/**
 * Returns the currentNode.
 * @return
 */
Node* LinkedList::getCurrentNode() {
    return currentNode;
}

/**
 * Returns the cursorPos (which is the index of the currentNode).
 * @return
 */
int LinkedList::getCursorPos() {
    return cursorPos;
}

/**
 * Returns capacity of a Node's value array.
 * @return
 */
int LinkedList::getMaxLineSize() {
    return maxLineSize;
}

/**
 * Increases currentNode's valIndex and tempValIndex.
 * If indices reach the end of the value array, currentNode changes to the next Node
 * and indices are set to 0.
 */
void LinkedList::increaseIndex() {
    if (currentNode->valIndex == maxLineSize - 1) {
        if (cursorPos != size) {
            currentNode = currentNode->next;
            cursorPos++;
            currentNode->valIndex = 0;
            currentNode->tempValIndex = 0;
        } else {
            currentNode = currentNode->next->next;  // to avoid the sentinel
            cursorPos = 1;
            currentNode->valIndex = 0;
            currentNode->tempValIndex = 0;
        }
    } else {
        currentNode->valIndex++;
        currentNode->tempValIndex++;
    }
}

/**
 * Decreases currentNode's valIndex and tempValIndex.
 * If indices reach 0, currentNode changes to the previous Node
 * and indices are set to maxLineSize.
 */
void LinkedList::decreaseIndex() {
    if (currentNode->valIndex == 0) {
        if (cursorPos != 1) {
            currentNode = currentNode->prev;
            cursorPos--;
            currentNode->valIndex = maxLineSize - 1;
            currentNode->tempValIndex = maxLineSize - 1;
        } else {
            currentNode = currentNode->prev->prev;  // to avoid the sentinel
            cursorPos = size;
            currentNode->valIndex = maxLineSize - 1;
            currentNode->tempValIndex = maxLineSize - 1;
        }
    } else {
        currentNode->valIndex--;
        currentNode->tempValIndex--;
    }
}

/**
 * Sets currentNode to the next Node.
 */
void LinkedList::increaseCurrentNode() {
    if (cursorPos != size) {
        currentNode = currentNode->next;
        cursorPos++;
    } else {
        currentNode = currentNode->next->next;
        cursorPos = 1;
    }
}

/**
 * Sets currentNode to the previous Node.
 */
void LinkedList::decreaseCurrentNode() {
    if (cursorPos != 0) {
        currentNode = currentNode->prev;
        cursorPos--;
    } else {
        currentNode = currentNode->prev->prev;
        cursorPos = size;
    }
}
