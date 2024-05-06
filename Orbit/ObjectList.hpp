//
//  ObjectList.hpp
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#ifndef ObjectList_hpp
#define ObjectList_hpp

#include <vector>
#include "Object.hpp"

class ObjectList{
private:
    long double force;
    long double unitVectorI;
    long double unitVectorJ;
    const long double G = 6.6743E-11;
public:
    ObjectList() = default;
    
    static std::vector <Object> objectList;
    
    static std::vector <Object> gravityList;

    static std::vector <Object> noGravityList;

    static int objectCount;
    
    long double calcDistance(const Object& object1, const Object& object2);
    
    void calcForce();
    
    void addObject(const Object& newObject);
};


#endif /* ObjectList_hpp */
