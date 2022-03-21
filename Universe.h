/************************************************************
 *Name: <Anthony Liang>
 *Course name: <COMP.2040>
 *Assignment: <PS2B>
 *Instructor's name: <Dr. James Daly>
 *Date: <02/23/2022>
 *Sources Of Help: <sfml-dev.org, stackoverflow, tutoring, friends>
************************************************************/

#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Universe.h"
#include "CelestialBody.h"
#include <iostream>

class Universe: public sf::Drawable{
public:
    Universe(){};
    friend std::istream& operator>>(std::istream& is, Universe& uniObj);
    std::vector<std::shared_ptr<CelestialBody>>bodies;
    void step(double seconds);

    int getPlanets(){return planets;}
    double getRadius(){return radius;}

private:
    int planets;
    double radius;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

std::istream& operator>>(std::istream& is, Universe& uniObj){
    //double x, y, xv, yv, mass;
    std::string file;
    is >> uniObj.planets; //read into planets
    is >> uniObj.radius; //read into radius
    
    for(int i = 0; i < uniObj.planets; i++){
        std::shared_ptr<CelestialBody>temp;
        temp = std::make_shared<CelestialBody>();
        uniObj.bodies.push_back(std::move(temp)); //push selected vector that's being pointed at forward
        (*(uniObj.bodies[i])).setRadius(uniObj.radius); //access vector element and sets radius read from Universe into CelestialBody so it's applicable to setting the sprite position
        is >> *(uniObj.bodies[i]); //have stream read into the specific vector element which represent the specific planet with updated variables
    }
    return is;
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Universe uni;
    for(int i = 0; i < planets; i++){
        target.draw(*(bodies[i])); //draw out element of vector
    }
}

void Universe::step(double deltaT){ //argv[2]
    CelestialBody c;
    double netForce;
    double distance = 0;

    for(int i = 0; i < planets; i++){
        double deltaX = 0;
        double deltaY = 0;
        double xNetForce = 0;
        double yNetForce = 0;
        for(int j = 0; j < planets; j++){ //nested in order to compare pairs
            if(i != j){ //exclude body being compared with itself
                //find delta X and delta Y
                deltaX = (*(bodies[i])).getX() - (*(bodies[j])).getX(); //find deltaX values between the planet and the planets being used to compared
                deltaY = (*(bodies[i])).getY() - (*(bodies[j])).getY(); //find deltaY values between the planet and the planets being used to compared

                distance =  sqrt((deltaX * deltaX) + (deltaY * deltaY)); //find distance between the two planets

                //find total net force
                netForce = c.findForce((*(bodies[i])).getMass(), (*(bodies[j])).getMass(), distance);
                xNetForce += c.findXYForce(deltaX, distance, netForce); //find x netForce for compared planet
                yNetForce += c.findXYForce(deltaY, distance, netForce); //find y netForce for compared planet
            }
        }
        bodies[i]->setXNetForce(xNetForce); //set the X net force to the main planet
        bodies[i]->setYNetForce(yNetForce); //set the Y net force to the main planet

    }
    //begin calculations after finding the total net force of all planets
    for(int i = 0; i < planets; i++){
        double xAccel = bodies[i]->getXForce() / (*(bodies[i])).getMass();  //get the X acceleration of the main planet being used
        double yAccel = bodies[i]->getYForce() / (*(bodies[i])).getMass();  //get the Y acceleration of the main planet being used

        double xNewVel = (*(bodies[i])).getXV() + (deltaT * xAccel);    //get the new X velocity of the main planet being used 
        double yNewvel = (*(bodies[i])).getYV() - (deltaT * yAccel);    //get the new Y velocity of the main planet being used 

        (*(bodies[i])).setXV(xNewVel);  //set new X velocity to planet
        (*(bodies[i])).setYV(yNewvel);  //set new Y velocity to planet

        (*(bodies[i])).newPosScale(deltaT); //set new universe X and Y values to the SFML window accordingly
    }
}

#endif