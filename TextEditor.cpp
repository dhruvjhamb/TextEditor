//============================================================================
// Name        : TextEditor.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>

#include "LinkedList.h"
#include "TextEditor.h"

using namespace std;

TextEditor::TextEditor() {
    list = new LinkedList();
}

void TextEditor::moveUp() {
    list->decreaseCurrentNode();
}

void TextEditor::moveDown() {
    list->increaseCurrentNode();
}

void TextEditor::moveLeft() {
    list->decreaseIndex();
}

void TextEditor::moveRight() {
    list->increaseIndex();
}

void TextEditor::save(string name) {
    string fileContents = list->toString();
    ofstream saveFile (name);
    saveFile << fileContents;
    saveFile.close();
    cout << name << " successfully saved" << endl;
    cout << endl;
}

void TextEditor::load(string name) {
    list = new LinkedList();
    ifstream loadFile;
    loadFile.open (name, ifstream::in);
    if (loadFile.is_open()) {
        cout << "Loading " << name << endl;
        cout << endl;
        while (!loadFile.eof()) {
            char nextCharacter = (char) loadFile.get();
            cout << nextCharacter;
            list->addChar(nextCharacter);
        }
        backspace();     // Gets rid of EOF token
        cout << endl;
        loadFile.close();
    } else {
        perror("No such file exists");
    }
}

void TextEditor::deleteFile(string name) {
    const char * str = name.c_str();
    if (remove(str) != 0 ) {
        perror("Error deleting file");
    }
    else {
        cout << name << " successfully deleted" << endl;
    }
}

void TextEditor::type(char characters[]) {
    for (int i = 0; characters[i] != '\0'; i++) {
        list->addChar(characters[i]);
    }
    /**
     * For testing purposes
    list->printList();
    cout << endl;
     */
}

void TextEditor::backspace() {
    list->removeChar();
}

void TextEditor::newLine() {
    list->addNode();
}

LinkedList* TextEditor::getList() {
    return list;
}

int main() {
    TextEditor *a = new TextEditor();
    a->deleteFile("Save.txt");
    a->type("abcd");
    a->save("Save.txt");
    a->load("Save.txt");
    a->newLine();
    a->type("hello");
    a->save("Save.txt");
    a->load("Save.txt");
}