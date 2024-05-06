//
//  Object.hpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp
#include <SFML/Graphics.hpp>
#include <vector>
#include "Vector2.h"
#include "ObjectTrail.h"
class Object {
private:
    double timeElapsed = 0;
    long double sumXForce;
    long double sumYForce;
public:
    Object() = default;
    ObjectTrail trail;
    sf::Color color = sf::Color::White;
    long double dt = 10;
    int numForces = 0;
    long double radius;
    int objectCount;
    long double mass;
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    std::vector<Vector2> force;
    void sumForces();
    void updatePosition();
    void setColor(sf::Color color);
    int index = 0;
};

#endif /* Object_hpp */
