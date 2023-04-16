
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <math.h>
#include <vector>
#include <unistd.h>
#include <ctime>
using namespace std;
class Region;
struct Vector2 {
    long double x;
    long double y;
};



class Object {
private:
    const long double dt = 3000;
    double timeElapsed = 0;
public:
    int numForces = 0;
    long double sumXForce;
    long double sumYForce;
    long double radius;
    int bodyCount;
    long double mass;
    bool polar;
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    vector <Vector2> force;
    void sumForces(){
        sumXForce = 0;
        sumYForce = 0;
        for (int i = 0; i < force.size() ; i++){
            sumXForce += force[i].x;
            sumYForce += force[i].y;
           
        }
    }
    void calculations(){
        
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
    
};
class ObjectList{
public:
    int bodyCount = 0;
    vector <Object> object;
};
class Calculations {
private:
    ObjectList *obj;
public:
    Calculations(ObjectList *obj):obj(obj){}
    long double force;
    long double unitVectorI;
    long double unitVectorJ;
    const long double G = 6.6743E-11;
    //G = 6.6743E-11
    
    
    long double calcDistance(Object object1, Object object2){
        long double distance;
        distance = sqrt((object1.pos.x - object2.pos.x)*(object1.pos.x - object2.pos.x)+(object1.pos.y - object2.pos.y)*(object1.pos.y - object2.pos.y));
        return distance;
    }

    
    void calcForce(){
        for (int i = 0; i < obj->object.size(); i++){
            obj->object[i].numForces = 0;
            for (int j = 0; j < obj->object.size(); j++){
                if (i != j) {
                    long double distance = calcDistance(obj->object[i],obj->object[j]);
                    if (distance <= obj->object[i].radius + obj->object[j].radius){
                        
                    }
                    force =  G * obj->object[i].mass * obj->object[j].mass / pow(distance,2);
                    unitVectorI = (obj->object[i].pos.x - obj->object[j].pos.x)/distance;
                    unitVectorJ = (obj->object[i].pos.y - obj->object[j].pos.y)/distance;
                    obj->object[i].force[obj->object[i].numForces].x = force * unitVectorI;
                    obj->object[i].force[obj->object[i].numForces].y = force * unitVectorJ;
                    obj->object[i].numForces++;
                }
            }
        }
    }
};

class Render {
private:
    long double scale = 3E8;
    Vector2 center;
    Vector2 windowSize;
    Vector2 mouseDistance;
    sf::Vector2i mousePos;
    sf::Vector2i mousePosInitial;
    sf::Vector2i mousePosFinal;
    ObjectList *obj;
    bool isPressed = false;
    bool tracking = false;
    int trackedObject;
public:
    Render(ObjectList *obj):obj(obj){}
    void clickToDrag(sf::RenderWindow &window){
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
    void setTracking(bool set){
           tracking = set;
       }
    void clickToTrack(sf::RenderWindow &window,sf::Vector2i mousePos){
           Vector2 distance;
           double totalDistance;
           for (int i = 0; i < obj->object.size(); i++){
               distance.x = ((mousePos.x - windowSize.x/2) - ((obj->object[i].pos.x - center.x)/scale));
               distance.y = ((mousePos.y - windowSize.y/2) - ((obj->object[i].pos.y - center.y)/scale));
               totalDistance = sqrt(pow(distance.x,2) + pow(distance.y,2));
               if (totalDistance < 50){
                   trackedObject = i;
                   tracking = true;
                   break;
               }
           }
       }
    void trackObject(){
           if (tracking == true){
               center.x = (obj->object[trackedObject].pos.x  + (windowSize.x/2));
               center.y = (obj->object[trackedObject].pos.y  + (windowSize.y/2));
           }
    }
    void setWindowSize(Vector2 tempSize){
         windowSize.x = tempSize.x;
         windowSize.y = tempSize.y;
     }
    void changeScale(int distance, Vector2 mousePos){
        if (distance < 0){
            scale *= 1.25;
        }
        else {
            scale *= 0.80;
        }
    }
    
    void setCenter(Vector2 point){
        center.x = point.x;
        center.y = point.y;
    }
    
    void render(Object object,sf::RenderWindow(&window)){
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
};
class Region: public Calculations, public Render {
private:
    sf::Event event;
    Vector2 mouseDistance;
    Vector2 clickVel;
    sf::Vector2i mousePos;
    sf::CircleShape circle;
    
   
public:
    Region(ObjectList *obj):Calculations(obj),Render(obj),obj(obj){}
    int bodyCount = 0;
    ObjectList *obj;
    
    void addBodies(long double mass, long double xPos, long double yPos, long double xVel, long double yVel, long double radius){
        Object temp;
        temp.mass = mass;
        temp.pos.x = xPos;
        temp.pos.y = yPos;
        temp.vel.x = xVel;
        temp.vel.y = yVel;
        temp.radius = radius;
        temp.bodyCount = bodyCount;
        obj->object.push_back(temp);
        bodyCount++;
    }
    
    void addBodiesPolar(long double mass, long double radius, long double posAngle, long double vel, long double velAngle, long double r){
        Object temp;
        temp.mass = mass;
        temp.pos.x = radius * cos(posAngle);
        temp.pos.y = radius * sin(posAngle);
        temp.vel.x = vel * cos(velAngle);
        temp.vel.y = vel * sin(velAngle);
        temp.radius = r;
        temp.bodyCount = bodyCount;
        obj->object.push_back(temp);
        bodyCount++;
    }
    void addBodiesPolarRand(long double mass, long double radius, long double vel, long double size){
        Object temp;
        double posAngle;
        double velAngle;
        posAngle = double(rand() % 360);
        posAngle = posAngle * 180 / 3.142;
        velAngle = (posAngle - 3.142/2);
        temp.mass = mass;
        temp.pos.x = radius * cos(posAngle);
        temp.pos.y = radius * sin(posAngle);
        temp.vel.x = (vel * cos(velAngle));
        temp.vel.y = (vel * sin(velAngle));
        temp.radius = size;
        temp.bodyCount = bodyCount;
        obj->object.push_back(temp);
        bodyCount++;
    }
    void update(){
        Vector2 temp;
        temp.x = 0;
        temp.y = 0;
        for (int i = 0; i < obj->object.size(); i++){
            while (bodyCount > obj->object[i].force.size()){
            obj->object[i].force.push_back(temp);
            }
        }
        for (int i = 0; i < obj->object.size(); i++){
            obj->object[i].bodyCount = bodyCount;
            calcForce();
        }
        for (int i = 0; i < obj->object.size(); i++){
            obj->object[i].calculations();
        }
    }
};

int main(){
    srand((unsigned) time(NULL));
    ObjectList *obj = new ObjectList;
    Vector2 initialCenter;
    Vector2 size;
    Vector2 mousePos;    sf::Vector2i mousePosition;
    sf::Event event;
    Region region(obj);
    
    size.x = 3480;
    size.y = 2160;
    sf::RenderWindow window(sf::VideoMode(size.x,size.y),"Sim");
    region.setWindowSize(size);
    initialCenter.x = size.x/2;
    initialCenter.y = size.y/2;
    region.setCenter(initialCenter);
    
    
    
    //5.92E24 = mass of earth
    
    //Solar System
    region.addBodies(1.98E30,0,0,0,0,6.96E8); //sun
    region.addBodiesPolarRand(0.33E24,57.9E9,47.87E3,2.44E6); //mercury
    region.addBodiesPolarRand(4.87E24,108.2E9,35.02E3,6.05E6); //venus
    region.addBodiesPolarRand(0.642E24,227.9E9,24.077E3,3.39E6); //mars
    region.addBodiesPolarRand(1898E24,778.6E9,13.07E3,6.69E7); //jupiter
    region.addBodiesPolarRand(565E24,1433.5E9,9.69E3,5.82E7); //saturn
    region.addBodiesPolarRand(86.8E24,2872E9,6.81E3,2.54E7); //uranus
    region.addBodiesPolarRand(102E24,4495E9,5.43E3,2.46E7); //neptune
    region.addBodies(5.97E24,152.1E9,0,0,-29.29E3,6.38E6); //earth
    region.addBodies(7.346E22,152.1E9,.4055E9,.970E3,-29.29E3,1.74E6); //moon
    
    //Other Solar System objects
 /* region.addBodies(9.1E20, 413E9, 0, 0, 17.9E3,1E6); //ceres
    region.addBodies(3.1E21,6.85E12,0,0,4.42E3,1E6);//MakeMake
    region.addBodies(4E21,4.45E12,0,0,4.53E3,1E6);//Haumea
    region.addBodies(1.67E22,10.1E12,0,0,3.43E3,1E6);//Eris*/
    //region.addBodies(1E3,7E12,0,-17E3,0); //voyager1
    //region.addBodies(1E31,0,0,0,0,1);
    
  
    
    
    while(window.isOpen()){
        sf::Vector2u screenSize = window.getSize();
        size.x = screenSize.x;
        size.y = screenSize.y;
        region.setWindowSize(size);
        region.update();
        region.clickToDrag(window);
        region.trackObject();
        while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                        window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed){
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        mousePosition.x = event.mouseButton.x;
                        mousePosition.y = event.mouseButton.y;
                        region.clickToTrack(window,mousePosition);
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        region.setTracking(false);
                    }
                }
                        
                else if (event.type == sf::Event::MouseWheelMoved){
                        mousePos.x = event.mouseMove.x;
                        mousePos.y = event.mouseMove.y;
                        region.changeScale(event.mouseWheel.delta, mousePos);
                }
                else if (event.key.code == sf::Keyboard::Period){
                    mousePos.x = event.mouseMove.x;
                    mousePos.y = event.mouseMove.y;
                    region.changeScale(1, mousePos);
                }
                else if (event.key.code == sf::Keyboard::Comma){
                    mousePos.x = event.mouseMove.x;
                    mousePos.y = event.mouseMove.y;
                    region.changeScale(-1, mousePos);
                }
        }
        window.clear();
        
        for (int i = 0; i < region.bodyCount; i++){
            region.render(region.obj->object[i],window);
        }
        
        window.display();
    }
    
}

