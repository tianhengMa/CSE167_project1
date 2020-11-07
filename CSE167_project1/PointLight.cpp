//
//  PointLight.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 11/5/20.
//

#include "PointLight.h"
#include <limits>
#include <stdio.h>
#include <float.h>
#include <math.h>

PointLight::PointLight(glm::vec3 in_pos, glm::vec3 in_color, glm::vec3 in_atten){
    this->pos = in_pos;
    this->color = in_color;
    this->atten = in_atten;
}

void PointLight::sendLightToShader(const int shaderID){
    glUniform3fv(glGetUniformLocation(shaderID, "in_lightColor"), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shaderID, "lightPos"), 1, glm::value_ptr(pos));
    glUniform3fv(glGetUniformLocation(shaderID, "lightAtten"), 1, glm::value_ptr(atten));
}

glm::vec3 PointLight::getPos(){
    return pos;
}

glm::vec3 PointLight::getColor(){
    return color;
}

void PointLight::setPos(glm::vec3 new_pos){
    pos = new_pos;
}
