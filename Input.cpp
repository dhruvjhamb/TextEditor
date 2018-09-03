#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "TextEditor.h"

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
               te->type((char) event.text.unicode);
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

           text.setPosition(5, 5);  // top left
           window.draw(text);
           window.display();
        }
    }
    return 0;
}