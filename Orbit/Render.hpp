//
//  Render.hpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#ifndef Render_hpp
#define Render_hpp

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "ObjectList.hpp"
#include "ButtonPress.h"

class Render {
private:
    long double scale = 5E8;
    Vector2 center;
    Vector2 windowSize;
    ButtonPress buttonPress;
    Vector2 mouseDistance;
    sf::Vector2i mousePos;
    sf::Vector2i mousePosInitial;
    sf::Vector2i mousePosFinal;
    ObjectList objectList;
    bool isPressed = false;
    bool tracking = false;
    int trackedObject;
    int minObjectSize = 1;
public:
    Render() = default;
    
    void clickToDrag(sf::RenderWindow &window);
    
    void setTracking(bool set);
    
    void clickToTrack(sf::RenderWindow &window,sf::Vector2i mousePos);
    
    void trackObject();
    
    void setWindowSize(Vector2 tempSize);
    
    void changeScale(int distance, Vector2 mousePos);
    
    void setCenter(Vector2 point);
    
    void setMinObjectSize(int newSize);
    
    void renderObjects(Object& object,sf::RenderWindow(&window));

    void renderTrails(Object& object, sf::RenderWindow(&window));
};

#endif /* Render_hpp */
