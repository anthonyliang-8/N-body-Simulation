/************************************************************
 *Name: <Anthony Liang>
 *Course name: <COMP.2040>
 *Assignment: <PS2B>
 *Instructor's name: <Dr. James Daly>
 *Date: <02/23/2022>
 *Sources Of Help: <sfml-dev.org, stackoverflow, tutoring, friends>
************************************************************/

#ifndef CELESTIAL_BODY_H 
#define CELESTIAL_BODY_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CelestialBody.h"
#include <math.h>
#include <memory>

class CelestialBody: public sf::Drawable{
public:
    CelestialBody(){
        x = 0;
        y = 0;
        xV = 0;
        yV = 0;
        mass = 0;
        file = "";
    };
    CelestialBody(double rad, double posX, double posY, double xVel, double yVel, double totalMass, std::string fileName);
    friend std::istream& operator>>(std::istream& is, CelestialBody& uniObj);

    void setX(double posX);
    void setY(double posY);
    void setXV(double xVel);
    void setYV(double yVel);
    void setMass(double mass);
    void setRadius(double radius);
    void setNewPosition(double deltaT);
    void setXNetForce(double _xForce);
    void setYNetForce(double _yForce);

    double findDistance(double body1, double body2);
    double findForce(double m1, double m2, double r);
    double findXYForce(double delta, double r, double F);
    double findRadius(double deltaX, double deltaY);

    double getX();
    double getY();
    double getXV();
    double getYV();
    double getMass();
    double getRadius();
    double getXForce(); 
    double getYForce();
    std::string getFile();

    void newPosScale(double deltaT);
private:
    double x;
    double y;
    double xV;
    double yV;
    double mass;
    double radius;
    double xForce;
    double yForce;
    double xAccel;
    double yAccel;
    std::string file;
    sf::Texture texture;
    sf::Sprite sprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states); 
}

CelestialBody::CelestialBody(double rad, double posX, double posY, double xVel, double yVel, double totalMass, std::string fileName){
    x = posX;
    y = posY;
    xV = xVel;
    yV = yVel;
    mass = totalMass;
    file = fileName;
    radius = rad;
}

std::istream& operator>>(std::istream& is, CelestialBody& cbObj){
    
    is >> cbObj.x;
    is >> cbObj.y;
    is >> cbObj.xV;
    is >> cbObj.yV;
    is >> cbObj.mass;
    is >> cbObj.file;

    cbObj.texture.loadFromFile(cbObj.file);
    cbObj.sprite.setTexture(cbObj.texture);

   //window dimensions are 800x800, divide by the universe's radius and multiply by (x,y) position of sprite to set new position of the sprite
    double xWin = 800 / 2;
    double yWin = 800 / 2;

    double xScale = xWin / cbObj.radius;
    double yScale = yWin / cbObj.radius;

    double xPosScale = (cbObj.x * xScale) + xWin;
    double yPosScale = (cbObj.y * yScale) + yWin;
    //std::cout << xPosScale << std::endl;

    // double xWinOrigin = (800/2); //set new x origin
    // double yWinOrigin = (800/2); //set new y origin

    // double xCoords = xWinOrigin / cbObj.radius; //divide x coord origin by the radius of the universe
    // double yCoords = yWinOrigin / cbObj.radius; //divide y coord origin by the radius of the universe

    // double newXScale = xCoords * cbObj.x; //find new position of planet by multiplying new x coordinates with the original x value
    // double newYScale = yCoords * cbObj.y; //find new position of planet by multiplying new y coordinates with the original y value

    // double xScale = newXScale + 400; //readjust x position to proper position by adding back 400
    // double yScale = newYScale + 400; //readjust y position to proper position by adding back 400

    // cbObj.x = xScale; //set equal to x
    // cbObj.y = yScale; //set equal to y

    cbObj.sprite.setPosition(xPosScale, yPosScale); //set new position of sprite with updated x and y values

    return is;
}

void CelestialBody::setX(double posX){
    x = posX;
}
void CelestialBody::setY(double posY){
    y = posY;
}
void CelestialBody::setXV(double xVel){
    xV = xVel;
}
void CelestialBody::setYV(double yVel){
    yV = yVel;
}
void CelestialBody::setMass(double massrhs){
    mass = massrhs;
}
void CelestialBody::setRadius(double radiusrhs){
    radius = radiusrhs;
}

void CelestialBody::setXNetForce(double _xForce){
    xForce = _xForce;
}
void CelestialBody::setYNetForce(double _yForce){
    yForce = _yForce;
}

double CelestialBody::getX(){
    return x;
}
double CelestialBody::getY(){
    return y;
}
double CelestialBody::getXV(){
    return xV;
}
double CelestialBody::getYV(){
    return yV;
}
double CelestialBody::getMass(){
    return mass;
}
double CelestialBody::getRadius(){
    return radius;
}
double CelestialBody::getXForce(){
    return xForce;
}
double CelestialBody::getYForce(){
    return yForce;
}

std::string CelestialBody::getFile(){
    return file;
}

double CelestialBody::findForce(double m1, double m2, double r){
    double G = -6.67e-11;
    return ((G * m1 * m2) / (r * r));
}

double CelestialBody::findXYForce(double delta, double r, double _netF){ //run this twice for xF and yF
    return (_netF * (delta / r));
}

void CelestialBody::newPosScale(double deltaT){

    //half size of window
    double xWin = 800 / 2;
    double yWin = 800 / 2;

    double xScale = xWin / radius;
    double yScale = yWin / radius;

    double xPosScale = (x * xScale) + xWin;
    double yPosScale = (y * yScale) + yWin;

    x += (xV * deltaT); //update new x position of body
    y -= (yV * deltaT); //update new x position of body

    sprite.setPosition(xPosScale, yPosScale); //update new position of body to fit the scaled position of the SFML window
}


#endif