//
//  Orbit.cpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#include <math.h>
#include "Orbit.hpp"

Object Orbit::addBodies(long double mass, long double xPos, long double yPos, long double xVel, long double yVel, long double radius){
    Object temp;
    temp.mass = mass;
    temp.pos.x = xPos;
    temp.pos.y = yPos;
    temp.vel.x = xVel;
    temp.vel.y = yVel;
    temp.radius = radius;
    temp.objectCount = objectCount;
    objectList.addObject(temp);
    objectCount++;
    return temp;
}

Object Orbit::addBodiesPolar(long double mass, long double distance, long double posAngle, long double vel, long double velAngle, long double radius){
    Object temp;
    temp.mass = mass;
    temp.pos.x = distance * cos(posAngle);
    temp.pos.y = distance * sin(posAngle);
    temp.vel.x = vel * cos(velAngle);
    temp.vel.y = vel * sin(velAngle);
    temp.radius = radius;
    temp.objectCount = objectCount;
    objectList.addObject(temp);
    objectCount++;
    return temp;
}

void Orbit::addMoon(const Object& planet, long double mass, long double distance, long double vel, long double radius){
    Object temp;
    temp.mass = mass;
    temp.pos.x = planet.pos.x + distance;
    temp.pos.y = planet.pos.y;
    temp.vel.x = planet.vel.x;
    temp.vel.y = planet.vel.y + vel;
    temp.radius = radius;
    temp.objectCount = objectCount;
    objectList.addObject(temp);
    objectCount++;
}

Object Orbit::addBodiesPolarRand(long double mass, long double distance, long double vel, long double radius){
    Object temp;
    double posAngle;
    double velAngle;
    posAngle = double(rand() % 360);
    posAngle = posAngle * 180 / 3.142;
    velAngle = (posAngle - 3.142/2);
    temp.mass = mass;
    temp.pos.x = distance * cos(posAngle);
    temp.pos.y = distance * sin(posAngle);
    temp.vel.x = (vel * cos(velAngle));
    temp.vel.y = (vel * sin(velAngle));
    temp.radius = radius;
    temp.objectCount = objectCount;
    objectList.addObject(temp);
    objectCount++;
    return temp;
}

void Orbit::update(){
    Vector2 temp;
    temp.x = 0;
    temp.y = 0;
    for (int i = 0; i < objectList.objectList.size(); i++){
        while (objectCount > objectList.objectList[i].force.size()){
        objectList.objectList[i].force.push_back(temp);
        }
    }
    for (int i = 0; i < objectList.objectList.size(); i++){
        objectList.objectList[i].objectCount = objectCount;
        objectList.calcForce();
    }
    for (int i = 0; i < objectList.objectList.size(); i++){
        objectList.objectList[i].updatePosition();
    }
}

void Orbit::setTimeStep(int dt){
    for (int i = 0; i < objectList.objectList.size(); ++i){
        objectList.objectList[i].dt = dt;
    }
}

