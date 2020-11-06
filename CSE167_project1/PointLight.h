//
//  PointLight.h
//  CSE167_project1
//
//  Created by Matthew Ma on 11/5/20.
//

#ifndef PointLight_h
#define PointLight_h

#include <stdio.h>
#include "shader.h"
#include "Object.h"

class PointLight{
private:
    // Attenuation vector consists of:
    // atten.x = constant factor
    // atten.y = linear factor
    // atten.z = quadratic factor
    
    //glm::vec3 pos, color, atten;
    
public:
    glm::vec3 pos, color, atten;
    PointLight(glm::vec3 in_pos, glm::vec3 in_color, glm::vec3 atten);
    void sendLightToShader(const int shaderID);
    glm::vec3 getPos();
    glm::vec3 getColor();
};


#endif /* PointLight_h */
