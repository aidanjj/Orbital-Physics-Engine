//
//  OrbitLoop.hpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/23/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#ifndef OrbitLoop_hpp
#define OrbitLoop_hpp

#include <SFML/Graphics.hpp>
#include "ObjectManager.hpp"
#include "Object.hpp"
#include "ObjectList.hpp"
#include "Vector2.h"

class Simulation: public ObjectManager {
private:
    Vector2 center;
    Vector2 windowSize;
    Vector2 mousePos;
    ButtonPress buttonPress;
    sf::Vector2i mousePosition;
    sf::Event event;
    ObjectManager orbit;
    ObjectList objectList;
    
    sf::RenderWindow window;
    
public:
    Simulation();
    
    void start();
};

#endif /* OrbitLoop_hpp */
