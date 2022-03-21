/************************************************************
 *Name: <Anthony Liang>
 *Course name: <COMP.2040>
 *Assignment: <PS2B>
 *Instructor's name: <Dr. James Daly>
 *Date: <02/23/2022>
 *Sources Of Help: <sfml-dev.org, stackoverflow, tutoring, friends>
************************************************************/

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CelestialBody.h"
#include "Universe.h"

int main(int argc, char* argv[]){

    sf::RenderWindow window(sf::VideoMode(800, 800), "My Universe");
    Universe uni;

    double maxTime = std::stod(argv[1]);
    double deltaT = std::stod(argv[2]);
    int timePassed = 0;

    std::cin >> uni; //read into Universe for planets and radius first

    //BACKGROUND INFO---------------------------------------------------------------------
    sf::Texture texture;
    sf::Vector2u textureSize;
    sf::Sprite background;
    texture.loadFromFile("starfield.jpg");
    background.setTexture(texture); 

    textureSize = texture.getSize(); //get dimensions of the image
    double xScale = (double) 800 / textureSize.x; //resize horizontal coordinates
    double yScale = (double) 800 / textureSize.y; //resize vertical coordinates

    background.setScale(xScale, yScale); //set background image to newly resized dimensions
    //-------------------------------------------------------------------------------------

    sf::Clock clock;
    sf::Text text;
    sf::Font font;
    std::string timer;

    if(!font.loadFromFile("Roboto-Black.ttf"));
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Red);

    while (window.isOpen() && (timePassed < maxTime)){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time time = clock.getElapsedTime();
        timer = std::to_string(time.asSeconds());

        window.clear();
        window.draw(background);
        uni.step(deltaT);
        window.draw(uni);
        text.setString(timer);
        window.draw(text); //draw run time of simulation
        window.display();
        timePassed += deltaT;
    }
    std::cout << "Time Passed: " << timePassed << std::endl;
    std::cout << "Total time: " << maxTime << std::endl;
    std::cout << uni.getPlanets() << std::endl;
    std::cout << uni.getRadius() << std::endl;

    for(int i = 0; i < uni.getPlanets(); i++){
        std::cout << uni.bodies[i]->getX() << " " << uni.bodies[i]->getY() << " " << uni.bodies[i]->getXV() << " " << uni.bodies[i]->getYV() << " " << uni.bodies[i]->getMass() << " " << uni.bodies[i]->getFile() << std::endl;
    }
    return 0;
}

