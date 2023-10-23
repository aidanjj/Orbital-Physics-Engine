//
//  ObjectList.cpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#include <math.h>
#include "ObjectList.hpp"

int ObjectList::objectCount = 0;

std::vector <Object> ObjectList::objectList = {};

long double ObjectList::calcDistance(const Object& object1, const Object& object2){
    long double distance;
    distance = sqrt((object1.pos.x - object2.pos.x)*(object1.pos.x - object2.pos.x)+(object1.pos.y - object2.pos.y)*(object1.pos.y - object2.pos.y));
    return distance;
}

void ObjectList::calcForce(){
    for (int i = 0; i < objectList.size(); i++){
        objectList[i].numForces = 0;
        for (int j = 0; j < objectList.size(); j++){
            if (i != j) {
                long double distance = calcDistance(objectList[i],objectList[j]);
                force =  G * objectList[i].mass * objectList[j].mass / pow(distance,2);
                unitVectorI = (objectList[i].pos.x - objectList[j].pos.x)/distance;
                unitVectorJ = (objectList[i].pos.y - objectList[j].pos.y)/distance;
                objectList[i].force[objectList[i].numForces].x = force * unitVectorI;
                objectList[i].force[objectList[i].numForces].y = force * unitVectorJ;
                objectList[i].numForces++;
            }
        }
    }
}

void ObjectList::addObject(const Object& newObject){
    objectList.push_back(newObject);
    objectCount++;
}
