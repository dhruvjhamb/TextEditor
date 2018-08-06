//
// Created by Dhruv Jhamb on 7/24/18.
//

#include "LinkedList.h"
#include <iostream>

using namespace std;

#ifndef TEXTEDITOR_TEXTEDITOR_H
#define TEXTEDITOR_TEXTEDITOR_H

#endif //TEXTEDITOR_TEXTEDITOR_H

class TextEditor {
private:
    LinkedList *list;

public:
    TextEditor();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void save(string name);
    void load(string name);
    void deleteFile(string name);
    void type(char characters[]);
    void backspace();
    void newLine();
    LinkedList* getList();
};
