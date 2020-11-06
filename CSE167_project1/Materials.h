//
//  Materials.h
//  CSE167_project1
//
//  Created by Matthew Ma on 11/4/20.
//

#ifndef Materials_h
#define Materials_h
#include "main.h"
#include "shader.h"
#include "Object.h"
#include "Cube.h"
#include "PointCloud.h"

class Materials{
private:
    //glm::vec3 ambient, diffuse, specular;
    //float shininess;
   
public:
    glm::vec3 ambient, diffuse, specular;
    float shininess;
    Materials(glm::vec3 in_ambient, glm::vec3 in_diffuse, glm::vec3 in_specular, float in_shininess);
    void sendMatToShader(const int shaderID);
};

#endif /* Materials_h */
