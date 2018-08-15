#ifndef KAGAMI_COMMON_CONTROLS_H_
#define KAGAMI_COMMON_CONTROLS_H_

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif
