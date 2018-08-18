#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "TextEditor.h"
//#include "Input.h"
//#include <curses.h>
//#include <unistd.h>  /* only for sleep() */

using namespace std;

int main()
{
    TextEditor *te = new TextEditor();
    te->clearList();
    sf::RenderWindow window(sf::VideoMode(650,480,32), "SFML Console");
    sf::Event event;
    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");
    sf::Text text ("", font, 24);
    sf::Clock myClock; // starts the clock
    bool showCursor = false;
    string fileName = "Demo.txt";

    while(window.isOpen()) {
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
               window.close();
           }
           if(event.type == sf::Event::TextEntered) {
               /*if(showCursor) {
                   char *c = new char[3];
                   c[0] = (char) event.text.unicode;
                   c[1] = '|';
                   c[2] = '\0';
                   te->type(c);
               } else {*/
               te->type((char) event.text.unicode);
               //}
           } else if (event.key.code == sf::Keyboard::BackSpace) {
               te->backspace();
           } else if (event.type == sf::Event::KeyPressed) {
               if (event.key.code == sf::Keyboard::Left) {
                   te->moveLeft();
               } else if (event.key.code == sf::Keyboard::Right) {
                   te->moveRight();
               } else if (event.key.code == sf::Keyboard::Up) {
                   te->moveUp();
               } else if (event.key.code == sf::Keyboard::Down) {
                   te->moveDown();
               } else if (event.key.code == sf::Keyboard::Return) {
                   te->newLine();
               } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                          && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                   te->save(fileName);
               } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                          && sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                   te->load(fileName);
               } else if (event.key.code == sf::Keyboard::LControl
                          && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                   te->deleteFile(fileName);
               }
           }
           if (myClock.getElapsedTime() >= sf::milliseconds(500)) {
                myClock.restart();
                showCursor = !showCursor;
           }
           text.setString(te->getList()->toString());
           window.clear(sf::Color::Black);
           //sf::Text cursor ("|", font, 24);

           /*
            * Width of character = 5 pixels
            * Height of character = 30 pixels
            */
           /*if (showCursor) {
               int x = te->getList()->getCurrentNode()->getValIndex();
               int y = te->getList()->getCursorPos();
               cout << x << y << endl;
               cursor.setPosition(12 * x, 5 + 30 * (y - 1));
           }*/

            //int x = te->getList()->getCurrentNode()->getValIndex();
            //int y = te->getList()->getCursorPos();
            //cout << x << ", " << y << endl;

           text.setPosition(5, 5);     // top left
            /**
             * For centering text:
             * text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,
                             window.getSize().y/2 - text.getGlobalBounds().height/2);
             */
            window.draw(text);
            //window.draw(cursor);
            window.display();
            cout << te->getList()->toString() << endl;
            //te->getList()->printList();
        }
    }
    return 0;
}