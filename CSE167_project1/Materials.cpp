//
//  Materials.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 11/4/20.
//

#include "Materials.h"
#include <limits>
#include <stdio.h>
#include <float.h>
#include <math.h>

Materials::Materials(glm::vec3 in_ambient, glm::vec3 in_diffuse, glm::vec3 in_specular, float in_shininess){
    this->ambient = in_ambient;
    this->diffuse = in_diffuse;
    this->specular = in_specular;
    this->shininess = in_shininess;
}

void Materials::sendMatToShader(const int shaderID){
    glUniform3fv(glGetUniformLocation(shaderID, "in_ambient"), 1, glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(shaderID, "in_diffuse"), 1, glm::value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(shaderID, "in_specular"), 1, glm::value_ptr(specular));
    glUniform1f(glGetUniformLocation(shaderID, "in_shininess"), shininess);
}
