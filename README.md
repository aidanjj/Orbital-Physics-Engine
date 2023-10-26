
An Interactable Orbital Physics Engine written in C++ and the SFML library.

Features the ability to click and drag to move around, zoom in and out using the scroll wheel, and snap to objects by clicking on them.

## Basic Usage:
The standard method to add orbiting bodies is `Simulation::addBodies(double mass, double xPos, double yPos, double xVel, double yVel, double radius)`. 
Mass, position, velocity, and radius use the units kilograms, meters, m/s, and meters, respectively.
Here is an example of the earth and the sun.
```AGS Script
#include "Simulation.hpp"

int main(){
  Simulation sim;
  sim.addBodies(1.98E30,0,0,0,0,6.96E8); //sun
  sim.addBodies(5.97E24,1.521E11,0,0,-2.929E4,6.38E6); //earth
  sim.start();
}
```
