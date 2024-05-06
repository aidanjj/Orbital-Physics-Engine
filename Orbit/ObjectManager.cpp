//
//  Orbit.cpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#include <math.h>
#include <iostream>
#include <string>
#include "ObjectManager.hpp"

ObjectManager::ObjectManager() {
    std::string filename = "clack.wav";
    if (!buffer.loadFromFile(filename)) {
        std::cout << "Could not read clack.wav" << std::endl;
    }
    sound.setBuffer(buffer);
}

Object ObjectManager::addBodies(long double mass, long double xPos, long double yPos, long double xVel, long double yVel, long double radius){
    Object temp;
    temp.mass = mass;
    temp.pos.x = xPos;
    temp.pos.y = yPos;
    temp.vel.x = xVel;
    temp.vel.y = yVel;
    temp.radius = radius;
    temp.objectCount = objectCount;
    temp.index = objectList.objectList.size();
    objectList.addObject(temp);
    objectCount++;
    if (mass == 1) {
        objectList.noGravityList.push_back(temp);
    }
    else {
        objectList.gravityList.push_back(temp);
    }
    return temp;
}

Object ObjectManager::addBodies(long double mass, long double xPos, long double yPos, long double xVel, long double yVel, long double radius, sf::Color color) {
    Object temp;
    temp.setColor(color);
    temp.mass = mass;
    temp.pos.x = xPos;
    temp.pos.y = yPos;
    temp.vel.x = xVel;
    temp.vel.y = yVel;
    temp.radius = radius;
    temp.objectCount = objectCount;
    temp.index = objectList.objectList.size();
    objectList.addObject(temp);
    objectCount++;
    if (mass == 1) {
        objectList.noGravityList.push_back(temp);
    }
    else {
        objectList.gravityList.push_back(temp);
    }
    return temp;
}

Object ObjectManager::addBodiesPolar(long double mass, long double distance, long double posAngle, long double vel, long double velAngle, long double radius){
    Object temp;
    temp.mass = mass;
    temp.pos.x = distance * cos(posAngle);
    temp.pos.y = distance * sin(posAngle);
    temp.vel.x = vel * cos(velAngle);
    temp.vel.y = vel * sin(velAngle);
    temp.radius = radius;
    temp.objectCount = objectCount;
    temp.index = objectList.objectList.size();
    objectList.addObject(temp);
    objectCount++;
    if (mass == 1) {
        objectList.noGravityList.push_back(temp);
    }
    else {
        objectList.gravityList.push_back(temp);
    }
    return temp;
}

Object ObjectManager::addBodiesPolar(long double mass, long double distance, long double posAngle, long double vel, long double velAngle, long double radius, sf::Color color) {
    Object temp;
    temp.mass = mass;
    temp.setColor(color);
    temp.pos.x = distance * cos(posAngle);
    temp.pos.y = distance * sin(posAngle);
    temp.vel.x = vel * cos(velAngle);
    temp.vel.y = vel * sin(velAngle);
    temp.radius = radius;
    temp.objectCount = objectCount;
    temp.index = objectList.objectList.size();
    objectList.addObject(temp);
    if (mass == 1) {
        objectList.noGravityList.push_back(temp);
    }
    else {
        objectList.gravityList.push_back(temp);
    }
    objectCount++;
    return temp;
}

void ObjectManager::addMoon(const Object& planet, long double mass, long double distance, long double vel, long double radius){
    Object temp;
    temp.mass = mass;
    temp.pos.x = planet.pos.x + distance;
    temp.pos.y = planet.pos.y;
    temp.vel.x = planet.vel.x;
    temp.vel.y = planet.vel.y + vel;
    temp.radius = radius;
    temp.objectCount = objectCount;
    temp.index = objectList.objectList.size();
    objectList.addObject(temp);
    if (mass == 1) {
        objectList.noGravityList.push_back(temp);
    }
    else {
        objectList.gravityList.push_back(temp);
    }
    objectCount++;
}

Object ObjectManager::addBodiesPolarRand(long double mass, long double distance, long double vel, long double radius){
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
    temp.index = objectList.objectList.size();
    objectList.addObject(temp);
    objectCount++;
    if (mass == 1) {
        objectList.noGravityList.push_back(temp);
    }
    else {
        objectList.gravityList.push_back(temp);
    }
    return temp;
}

Object ObjectManager::addBodiesPolarRand(long double mass, long double distance, long double vel, long double radius, sf::Color color) {
    Object temp;
    double posAngle;
    double velAngle;
    posAngle = double(rand() % 360);
    posAngle = posAngle * 180 / 3.142;
    velAngle = (posAngle - 3.142 / 2);
    temp.mass = mass;
    temp.setColor(color);
    temp.pos.x = distance * cos(posAngle);
    temp.pos.y = distance * sin(posAngle);
    temp.vel.x = (vel * cos(velAngle));
    temp.vel.y = (vel * sin(velAngle));
    temp.radius = radius;
    temp.objectCount = objectCount;
    temp.index = objectList.objectList.size();
    objectList.addObject(temp);
    objectCount++;
    if (mass == 1) {
        objectList.noGravityList.push_back(temp);
    }
    else {
        objectList.gravityList.push_back(temp);
    }
    return temp;
}

void ObjectManager::update(){
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
    /*double boxSize = 5E11;
    for (int i = 0; i < objectList.objectList.size(); ++i) {
        if (objectList.objectList[i].pos.x < -boxSize) {
            objectList.objectList[i].vel.x = -objectList.objectList[i].vel.x;
        }
        else if (objectList.objectList[i].pos.x > boxSize) {
            objectList.objectList[i].vel.x = -objectList.objectList[i].vel.x;
        }
        if (objectList.objectList[i].pos.y < -boxSize) {
            objectList.objectList[i].vel.y = -objectList.objectList[i].vel.y;
        }
        else if (objectList.objectList[i].pos.y > boxSize) {
            objectList.objectList[i].vel.y = -objectList.objectList[i].vel.y;
        }
        objectList.objectList[i].updatePosition();
    }*/
    for (int i = 0; i < objectList.objectList.size(); ++i) {
        for (int j = i + 1; j < objectList.objectList.size(); ++j) {
            if (i != j) {
                double distance = sqrt(pow(objectList.objectList[i].pos.x - objectList.objectList[j].pos.x, 2) + pow(objectList.objectList[i].pos.y - objectList.objectList[j].pos.y, 2));
                if (distance < objectList.objectList[i].radius + objectList.objectList[j].radius) {
                    sound.play();
                    double massI = objectList.objectList[i].mass;
                    double massJ = objectList.objectList[j].mass;
                    double velIX = objectList.objectList[i].vel.x;
                    double velIY = objectList.objectList[i].vel.y;
                    double velJX = objectList.objectList[j].vel.x;
                    double velJY = objectList.objectList[j].vel.y;
                    double totalVelI = sqrt(velIX * velIX + velIY * velIY);
                    double totalVelJ = sqrt(velJX * velJX + velJY * velJY);
                    double dirIX = (objectList.objectList[i].pos.x - objectList.objectList[j].pos.x) / distance;
                    double dirIY = (objectList.objectList[i].pos.y - objectList.objectList[j].pos.y) / distance;
                    double dirJX = (objectList.objectList[j].pos.x - objectList.objectList[i].pos.x) / distance;
                    double dirJY = (objectList.objectList[j].pos.y - objectList.objectList[i].pos.y) / distance;
                    double perpNormalIX = (velIX / totalVelI * dirIX + velIY / totalVelI * dirIY) * dirIX;
                    double perpNormalIY = (velIX / totalVelI * dirIX + velIY / totalVelI * dirIY) * dirIY;
                    double perpNormalJX = (velJX / totalVelJ * dirJX + velJY / totalVelJ * dirJY) * dirJX;
                    double perpNormalJY = (velJX / totalVelJ * dirJX + velJY / totalVelJ * dirJY) * dirJY;
                    double paraNormalIX = (velIX / totalVelI * dirIY + velIY / totalVelI * -dirIX) * dirIY;
                    double paraNormalIY = (velIX / totalVelI * dirIY + velIY / totalVelI * -dirIX) * -dirIX;
                    double paraNormalJX = (velJX / totalVelJ * dirJY + velJY / totalVelJ * -dirJX) * dirJY;
                    double paraNormalJY = (velJX / totalVelJ * dirJY + velJY / totalVelJ * -dirJX) * -dirJX;
                  

                    double rotatePerpIX = perpNormalIX * (totalVelI);
                    double rotatePerpIY = perpNormalIY * (totalVelI);
                    double rotatePerpJX = perpNormalJX * (totalVelJ);
                    double rotatePerpJY = perpNormalJY * (totalVelJ);


                    double perpIX = rotatePerpIX * (massI - massJ) / (massI + massJ) + rotatePerpJX * 2 * massJ / (massI + massJ);
                    double perpIY = rotatePerpIY * (massI - massJ) / (massI + massJ) + rotatePerpJY * 2 * massJ / (massI + massJ);
                    double perpJX = rotatePerpIX * 2 * massI / (massI + massJ) - rotatePerpJX * (massI - massJ) / (massI + massJ);
                    double perpJY = rotatePerpIY * 2 * massI / (massI + massJ) - rotatePerpJY * (massI - massJ) / (massI + massJ);
                    double collisionI = sqrt(perpIX * perpIX + perpIY * perpIY);
                    double collisionJ = sqrt(perpJX * perpJX + perpJY * perpJY);

                    double newVelIX = (paraNormalIX) * (totalVelI) + perpIX;
                    double newVelIY = (paraNormalIY) * (totalVelI) + perpIY;
                    double newVelJX = (paraNormalJX) * (totalVelJ) + perpJX;
                    double newVelJY = (paraNormalJY) * (totalVelJ) + perpJY;

                    double tempPosIX = objectList.objectList[i].pos.x;
                    double tempPosIY = objectList.objectList[i].pos.y;


                    objectList.objectList[i].vel.x = newVelIX;
                    objectList.objectList[i].vel.y = newVelIY;
                    objectList.objectList[j].vel.x = newVelJX;
                    objectList.objectList[j].vel.y = newVelJY;
                    objectList.objectList[i].pos.x = objectList.objectList[j].pos.x + dirIX * (objectList.objectList[i].radius + objectList.objectList[j].radius);
                    objectList.objectList[i].pos.y = objectList.objectList[j].pos.y + dirIY * (objectList.objectList[i].radius + objectList.objectList[j].radius);
                    objectList.objectList[j].pos.x = tempPosIX + dirJX * (objectList.objectList[i].radius + objectList.objectList[j].radius);
                    objectList.objectList[j].pos.y = tempPosIY + dirJY * (objectList.objectList[i].radius + objectList.objectList[j].radius);
                    
                    objectList.objectList[i].updatePosition();
                    objectList.objectList[j].updatePosition();
                    
                }
            }
        }
    }

}

void ObjectManager::setTimeStep(double dt){
    for (int i = 0; i < objectList.objectList.size(); ++i){
        objectList.objectList[i].dt = dt;
    }
}

