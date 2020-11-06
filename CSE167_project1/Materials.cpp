//
//  Materials.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 11/4/20.
//

#include "Materials.h"

Materials::Materials(glm::vec3 in_ambient, glm::vec3 in_diffuse, glm::vec3 in_specular, float in_shininess){
    this->ambient = in_ambient;
    this->diffuse = in_diffuse;
    this->specular = in_specular;
    this->shininess = in_shininess;
}

void Materials::sendMatToShader(const int shaderID){
    
}
