#ifndef _POINT_CLOUD_H_
#define _POINT_CLOUD_H_

#include "Object.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class PointCloud : public Object
{
private:
	std::vector<glm::vec3> points;
    std::vector<glm::ivec3> triangles;
    std::vector<glm::vec3> rgbs;
    //Materials * materials;
        
	GLuint VAO, VBO, EBO;
    GLuint nVBO;
	GLfloat pointSize;

public:
	PointCloud(std::string objFilename, GLfloat pointSize);
    //PointCloud(std::string objFilename, GLfloat pointSize, Materials* in_materials);
	~PointCloud();
	
	void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
	void update();

	void updatePointSize(GLfloat size);
	void spin(float deg);
    void increasePointSize();
    void decreasePointSize();
    void scale(double scale);
    void ballRotate(glm::vec3 rotAxis, float rotAngle);
};

#endif
