//
//  Render.cpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#include <math.h>
#include "Render.hpp"

void Render::clickToDrag(sf::RenderWindow &window){
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(isPressed == false)){
        mousePos = sf::Mouse::getPosition(window);
        isPressed = true;
        mousePosInitial.x = (mousePos.x - windowSize.x/2 );
        mousePosInitial.y = (mousePos.y - windowSize.y/2 );
    }
    else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(isPressed == true)){
        mousePos = sf::Mouse::getPosition(window);
        mousePosFinal.x = (mousePos.x - windowSize.x/2 );
        mousePosFinal.y = (mousePos.y - windowSize.y/2 );
        mouseDistance.x = mousePosFinal.x - mousePosInitial.x;
        mouseDistance.y = mousePosFinal.y - mousePosInitial.y;
        mousePosInitial.x = mousePosFinal.x;
        mousePosInitial.y = mousePosFinal.y;
        center.x += -mouseDistance.x * scale;
        center.y += -mouseDistance.y * scale;
    }
    
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false){
        isPressed = false;
    }
    
}

void Render::setTracking(bool set){
       tracking = set;
   }

void Render::clickToTrack(sf::RenderWindow &window,sf::Vector2i mousePos){
       Vector2 distance;
       double totalDistance;
       for (int i = 0; i < objectList.objectList.size(); i++){
           distance.x = ((mousePos.x - windowSize.x/2) - ((objectList.objectList[i].pos.x - center.x)/scale));
           distance.y = ((mousePos.y - windowSize.y/2) - ((objectList.objectList[i].pos.y - center.y)/scale));
           totalDistance = sqrt(pow(distance.x,2) + pow(distance.y,2));
           if (totalDistance < 50){
               trackedObject = i;
               tracking = true;
               break;
           }
       }
   }

void Render::trackObject(){
       if (tracking == true){
           center.x = (objectList.objectList[trackedObject].pos.x  + (windowSize.x/2));
           center.y = (objectList.objectList[trackedObject].pos.y  + (windowSize.y/2));
       }
}

void Render::setWindowSize(Vector2 tempSize){
     windowSize.x = tempSize.x;
     windowSize.y = tempSize.y;
 }

void Render::changeScale(int distance, Vector2 mousePos){
    if (distance < 0){
        scale *= 1.25;
    }
    else {
        scale *= 0.80;
    }
}

void Render::setCenter(Vector2 point){
    center.x = point.x;
    center.y = point.y;
}

void Render::renderObjects(const Object& object,sf::RenderWindow(&window)){
    int size;
    sf::CircleShape circle;
    size = object.radius / scale;
    if (size < 1){
        size = 1;
    }
    sf::Vector2f circlePosition((object.pos.x / scale + (windowSize.x/2 - size)) - (center.x / scale ),(object.pos.y / scale + (windowSize.y/2 - size)) - (center.y  / scale));
    circle.setPosition(circlePosition);
    circle.setRadius(size);
    window.draw(circle);
    
}
