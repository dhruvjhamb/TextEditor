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

/**
 * TextEditor constructor.
 */
TextEditor::TextEditor() {
    list = new LinkedList();
}

/**
 * Moves the cursor up a line.
 */
void TextEditor::moveUp() {
    list->decreaseCurrentNode();
}

/**
 * Moves the cursor down a line.
 */
void TextEditor::moveDown() {
    list->increaseCurrentNode();
}

/**
 * Moves the cursor left one space.
 */
void TextEditor::moveLeft() {
    list->decreaseIndex();
}

/**
 * Moves the cursor right one space.
 */
void TextEditor::moveRight() {
    list->increaseIndex();
}

/**
 * Saves the contents of list to a text file titled name.
 * @param name
 */
void TextEditor::save(string name) {
    string fileContents = list->toString();
    ofstream saveFile (name);
    saveFile << fileContents;
    saveFile.close();
    cout << name << " successfully saved" << endl;
    cout << endl;
}

/**
 * Prints the contents of the text file name and loads the file's contents into list.
 * @param name
 */
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

/**
 * Deletes text file name.
 * @param name
 */
void TextEditor::deleteFile(string name) {
    const char * str = name.c_str();
    if (remove(str) != 0 ) {
        perror("Error deleting file");
    }
    else {
        cout << name << " successfully deleted" << endl;
    }
}

/**
 * Types characters.
 * @param characters
 */
void TextEditor::type(char characters[]) {
    for (int i = 0; characters[i] != '\0'; i++) {
        list->addChar(characters[i]);
    }
}

/**
 * Deletes the last entered character.
 */
void TextEditor::backspace() {
    list->removeChar();
}

/**
 * Creates a new line.
 */
void TextEditor::newLine() {
    list->addNode();
}

/**
 * Returns the list.
 * @return
 */
LinkedList* TextEditor::getList() {
    return list;
}

int main() {
    TextEditor *a = new TextEditor();
    a->type("Hello World!");
    a->save("HelloWorld.txt");
    a->load("HelloWorld.txt");
}