//Authors: Chris Baroni, Jalen Jackson, Nathan Richards
//CPSC 484
//controls.hpp: Implements prototypes to define how second cube moves and scales
#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <glm/glm.hpp>

void computeMatricesFromInputs();
void transformCubeFromInputs(glm::mat4&, int upKey, int leftKey, int downKey, int rightKey, int shrinkKey, int growKey); //Read inputs to move and scale second cube
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif
