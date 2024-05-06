//
//  Object.cpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#include "Object.hpp"

void Object::sumForces(){
    sumXForce = 0;
    sumYForce = 0;
    for (int i = 0; i < force.size() ; i++){
        sumXForce += force[i].x;
        sumYForce += force[i].y;
       
    }
}

void Object::updatePosition(){
    sumForces();
    acc.x = sumXForce / mass;
    acc.y = sumYForce / mass;
    vel.x = -acc.x * dt + vel.x;
    vel.y = -acc.y * dt + vel.y;
    pos.x = vel.x * dt + pos.x;
    pos.y = vel.y * dt + pos.y;
    numForces = 0;
    timeElapsed += dt;
}

void Object::setColor(sf::Color color) {
    this->color = color;
    trail.setColor(color);
}
