//
//  OrbitLoop.cpp
//  Sim
//
//  Created by Aidan Jerdee on 10/23/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#include "Simulation.hpp"

Simulation::Simulation(){
    windowSize.x = sf::VideoMode::getDesktopMode().width;
    windowSize.y = sf::VideoMode::getDesktopMode().height;
    center.x = windowSize.x/2;
    center.y = windowSize.y/2;
    window.create(sf::VideoMode(windowSize.x,windowSize.y),"Sim");
    setCenter(center);
    setWindowSize(windowSize);
}

void Simulation::start(){
    while(window.isOpen()){
        update();
        clickToDrag(window);
        trackObject();
        while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                        window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed){
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        mousePosition.x = event.mouseButton.x;
                        mousePosition.y = event.mouseButton.y;
                        clickToTrack(window,mousePosition);
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        setTracking(false);
                    }
                }
                        
                else if (event.type == sf::Event::MouseWheelMoved){
                        mousePos.x = event.mouseMove.x;
                        mousePos.y = event.mouseMove.y;
                        changeScale(event.mouseWheel.delta, mousePos);
                }
                else if (event.key.code == sf::Keyboard::Period){
                    mousePos.x = event.mouseMove.x;
                    mousePos.y = event.mouseMove.y;
                    changeScale(1, mousePos);
                }
                else if (event.key.code == sf::Keyboard::Comma){
                    mousePos.x = event.mouseMove.x;
                    mousePos.y = event.mouseMove.y;
                    changeScale(-1, mousePos);
                }
        }
        window.clear();
        
        for (int i = 0; i < objectList.objectCount; i++){
            renderObjects(objectList.objectList[i],window);
        }
        
        window.display();
    }
}



