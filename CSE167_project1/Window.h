#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "main.h"
#include "shader.h"
#include "Object.h"
#include "Cube.h"
#include "PointCloud.h"

class Window
{
public:

	// Window Properties
	static int width;
	static int height;
	static const char* windowTitle;

	// Objects to Render
	static Cube* cube;
    static PointCloud* bunnyPoints;
	static PointCloud * cubePoints;
    static PointCloud * bearPoints;
    static PointCloud * sandalPoints;
    static PointCloud * lightSphere;
    
	// Camera Matrices
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::vec3 eyePos, lookAtPoint, upVector;

	// Shader Program ID
	static GLuint shaderProgram;

	// Constructors and Destructors
	static bool initializeProgram();
	static bool initializeObjects();
	static void cleanUp();

	// Window functions
	static GLFWwindow* createWindow(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);

	// Draw and Update functions
	static void idleCallback();
	static void displayCallback(GLFWwindow*);

	// Callbacks
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    // Scale factor
    static double scaleFactor;
    static float lightScale;
    
    // Track Ball
    static glm::vec3 trackBallMapping(double pointX, double pointY);
    
    // Cursor Position when mouse is pressed
    static bool mousePressed;
    static double startPosX;
    static double startPosY;
    
    // light position modes
    static int lightPosMode;
    static PointLight* pointLight;
};

#endif
