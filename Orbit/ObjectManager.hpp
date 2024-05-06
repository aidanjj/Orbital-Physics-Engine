//
//  Orbit.hpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#ifndef Orbit_hpp
#define Orbit_hpp

#include <SFML/Audio.hpp>
#include "ObjectManager.hpp"
#include "Render.hpp"
#include "ButtonPress.h"
#include "ObjectList.hpp"

class ObjectManager: public Render {
private:
    ObjectList objectList;
    sf::Event event;
    Vector2 mouseDistance;
    Vector2 clickVel;
    sf::Vector2i mousePos;
    ButtonPress buttonPress;
    sf::CircleShape circle;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    int objectCount = 0;
public:
    ObjectManager();
    
    Object addBodies(long double mass, long double xPos, long double yPos, long double xVel, long double yVel, long double radius);

    Object addBodies(long double mass, long double xPos, long double yPos, long double xVel, long double yVel, long double radius, sf::Color color);
    
    Object addBodiesPolar(long double mass, long double distance, long double posAngle, long double vel, long double velAngle, long double radius);

    Object addBodiesPolar(long double mass, long double distance, long double posAngle, long double vel, long double velAngle, long double radius, sf::Color color);
    
    void addMoon(const Object& planet, long double mass, long double distance, long double vel, long double radius);
    
    Object addBodiesPolarRand(long double mass, long double distance, long double vel, long double radius);

    Object addBodiesPolarRand(long double mass, long double distance, long double vel, long double radius, sf::Color color);
    
    void setTimeStep(double dt);
    
    void update();
};


#endif /* Orbit_hpp */
