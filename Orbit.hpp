//
//  Orbit.hpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#ifndef Orbit_hpp
#define Orbit_hpp

#include "Orbit.hpp"
#include "Render.hpp"
#include "ButtonPress.h"
#include "ObjectList.hpp"

class Orbit: public Render {
private:
    ObjectList objectList;
    sf::Event event;
    Vector2 mouseDistance;
    Vector2 clickVel;
    sf::Vector2i mousePos;
    ButtonPress buttonPress;
    sf::CircleShape circle;
    int objectCount = 0;
public:
    Orbit() = default;
    
    Object addBodies(long double mass, long double xPos, long double yPos, long double xVel, long double yVel, long double radius);
    
    Object addBodiesPolar(long double mass, long double radius, long double posAngle, long double vel, long double velAngle, long double r);
    
    void addMoon(const Object& planet, long double mass, long double distance, long double vel, long double radius);
    
    Object addBodiesPolarRand(long double mass, long double radius, long double vel, long double size);
    
    void setTimeStep(int dt);
    
    void update();
};


#endif /* Orbit_hpp */
