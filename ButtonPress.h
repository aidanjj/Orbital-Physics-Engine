//
//  ButtonPress.h
//  Orbit Sim
//
//  Created by Aidan Jerdee on 10/22/23.
//  Copyright © 2023 Aidan Jerdee. All rights reserved.
//

#ifndef ButtonPress_h
#define ButtonPress_h

#include <chrono>

class ButtonPress {
private:
    std::chrono::steady_clock::time_point begin;
    bool isPressed;
public:
    int KeyPress(){
        std::chrono::steady_clock::time_point end;
        if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)&&(isPressed == false)){
          
            isPressed = true;
            begin = std::chrono::steady_clock::now();
            
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false){
            isPressed = false;
            
        }
        else {
            end = std::chrono::steady_clock::now();
            int time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
            return time;
        }
        return 0;
    }
};

#endif /* ButtonPress_h */
