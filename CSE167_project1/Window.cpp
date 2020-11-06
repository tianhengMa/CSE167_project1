#include "Window.h"


// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "GLFW Starter Project";

// Objects to Render
Cube * Window::cube;
PointCloud * Window::cubePoints;
PointCloud * Window::bunnyPoints;
PointCloud * Window::sandalPoints;
PointCloud * Window::bearPoints;
PointCloud * Window::lightSphere;

Object* currObj;

// scale factor in scaling triangles
double Window::scaleFactor;

// Cusor Position
bool Window::mousePressed;
double Window::startPosX;
double Window::startPosY;

// Camera Matrices 
// Projection matrix:
glm::mat4 Window::projection; 

// View Matrix:
glm::vec3 Window::eyePos(0, 0, 20);			// Camera position.
glm::vec3 Window::lookAtPoint(0, 0, 0);		// The point we are looking at.
glm::vec3 Window::upVector(0, 1, 0);		// The up direction of the camera.
glm::mat4 Window::view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);

// Shader Program ID
GLuint Window::shaderProgram; 



bool Window::initializeProgram() {
	// Create a shader program with a vertex shader and a fragment shader.
	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");

	// Check the shader program.
	if (!shaderProgram)
	{
		std::cerr << "Failed to initialize shader program" << std::endl;
		return false;
	}

	return true;
}

bool Window::initializeObjects()
{
	// Create a cube of size 5.
	cube = new Cube(5.0f);
    
    // Initialize the point light
    glm::vec3 pos = glm::vec3(10,10,0);
    glm::vec3 color = glm::vec3(0.7, 0.7, 0.2);
    glm::vec3 atten = glm::vec3(10);
    PointLight * pointLight = new PointLight(pos, color, atten);
    
    // Set the material for emerald and bunny
    glm::vec3 ambient = glm::vec3(0.0215, 0.1745, 0.0215);
    glm::vec3 diffuse = glm::vec3(0.50754, 0.50754, 0.50754);
    glm::vec3 specular = glm::vec3(0.633, 0.727811, 0.633);
    float shininess = 1.5;
    Materials * emerald = new Materials(ambient,diffuse,specular,shininess);
    
	// Create a point cloud consisting of cube vertices.
	cubePoints = new PointCloud("/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/bunny.obj", 1, emerald, pointLight);

	// Set cube to be the first to display
	currObj = cube;
    
    bunnyPoints = new PointCloud("/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/bunny.obj",1,emerald, pointLight);
    
    // Set the material for sandal
    ambient = glm::vec3(0.329412, 0.223529, 0.027451);
    diffuse = glm::vec3(0.780392, 0.568627, 0.113725);
    specular = glm::vec3(0);
    shininess = 0.21794872;
    Materials * brass = new Materials(ambient,diffuse,specular,shininess);
    sandalPoints = new PointCloud("/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/SandalF20.obj",1,brass, pointLight);
    
    // Set the material for bear
    ambient = glm::vec3(0.24725, 0.1995, 0.0745);
    diffuse = glm::vec3(0);
    specular = glm::vec3(0.992157, 0.941176, 0.807843);
    shininess = 0.8;
    Materials * gold = new Materials(ambient,diffuse,specular,shininess);
    bearPoints = new PointCloud("/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/bear.obj",1, gold, pointLight);
    
    // Initialize light sphere
    glm::vec3 translation = pointLight->getPos();
    glm::vec3 lightColor = pointLight->getColor();
    
    ambient = lightColor;
    diffuse = glm::vec3(0);
    specular = glm::vec3(0);
    Materials * lightMaterial = new Materials(ambient,diffuse,specular,shininess);
    lightSphere = new PointCloud("/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/sphere.obj",1, lightMaterial, pointLight);
    
    // Adjust the light sphere
    lightSphere->scale(0.5);
    lightSphere->translate(translation);
    lightSphere->toggleModelSwitch();
    
    // Initialize scale factor
    scaleFactor = 1.0;

	return true;
}

void Window::cleanUp()
{
	// Deallcoate the objects.
	delete cube;
	delete cubePoints;

	// Delete the shader program.
	glDeleteProgram(shaderProgram);
}

GLFWwindow* Window::createWindow(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return NULL;
	}

	// 4x antialiasing.
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ 
	// Apple implements its own version of OpenGL and requires special treatments
	// to make it uses modern OpenGL.

	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window.
	GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

	// Check if the window could not be created.
	if (!window)
	{
		std::cerr << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window.
	glfwMakeContextCurrent(window);

#ifndef __APPLE__
	// On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

	// Initialize GLEW.
	if (glewInit())
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}
#endif

	// Set swap interval to 1.
	glfwSwapInterval(0);

	// Call the resize callback to make sure things get drawn immediately.
	Window::resizeCallback(window, width, height);

	return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	// In case your Mac has a retina display.
	glfwGetFramebufferSize(window, &width, &height); 
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size.
	glViewport(0, 0, width, height);

	// Set the projection matrix.
	Window::projection = glm::perspective(glm::radians(60.0), 
								double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
	// Perform any necessary updates here 
	currObj->update();
}

void Window::displayCallback(GLFWwindow* window)
{	
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	// Render the objects
	currObj->draw(view, projection, shaderProgram);
    
    // Render light Sphere with the right scale and translation
    lightSphere->draw(view, projection, shaderProgram);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();

	// Swap buffers.
	glfwSwapBuffers(window);
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        mousePressed = true;
        glfwGetCursorPos(window, &startPosX, &startPosY);
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        mousePressed = false;
    }
        
}
void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!mousePressed){
        return;
    }
    
    glm::vec3 startPoint = trackBallMapping(startPosX, startPosY);
    glm::vec3 nextPoint = trackBallMapping(xpos, ypos);
    
    //cout << "start point is (" << startPosX << ", " << startPosY  << ") " << endl;
    //cout << "next point is (" << xpos << ", " << ypos << ") " << endl;
    //cout << endl;

    glm::vec3 direction = nextPoint - startPoint;
    float velocity = glm::length(direction);
    
    // if cursor movement is very little, do nothing
    if (velocity < 0.001){
        return;
    }
    
    glm::vec3 rotAxis = glm::cross(startPoint, nextPoint);
    float rotAngle = velocity * 1;
    ((PointCloud*)currObj)->ballRotate(rotAxis, rotAngle);
    //((PointCloud*)lightSphere)->ballRotate(rotAxis, rotAngle);
    
    startPosX = xpos;
    startPosY = ypos;
    
}


glm::vec3 Window::trackBallMapping(double pointX, double pointY){
    glm::vec3 vec;
    float d;
    
    vec.x = (2.0*pointX - width) / width;
    vec.y = (height - 2.0*pointY) / height;
    vec.z = 0.0;
    
    d = glm::length(vec);
    d = (d<1.0) ? d:1.0;
    vec.z = sqrtf(1.001 - d*d);
    vec = glm::normalize(vec);
    
    return vec;
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*
	 * TODO: Modify below to add your key callbacks.
	 */
	
	// Check for a key press.
	if (action == GLFW_PRESS)
	{
		switch (key){
            case GLFW_KEY_ESCAPE:
                // Close the window. This causes the program to also terminate.
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;

            // switch between the cube and the cube pointCloud
            case GLFW_KEY_1:
                currObj = cube;
                break;
            case GLFW_KEY_2:
                currObj = cubePoints;
                break;
                    
            // switch between bunny points, sandal points, and bear points
            case GLFW_KEY_F1:{
                currObj = bunnyPoints;
                break;
            }
            case GLFW_KEY_F2:{
                currObj = sandalPoints;
                break;
            }
            case GLFW_KEY_F3:{
                currObj = bearPoints;
                break;
            }
            // adjust point size
            case GLFW_KEY_S:{
                ((PointCloud*)currObj)->decreasePointSize();
                break;
            }
                
            case GLFW_KEY_L:{
                ((PointCloud*)currObj)->increasePointSize();
                break;
            }
                
            case GLFW_KEY_UP :{
                //lightSphere->translate(1.1*translation);
                scaleFactor = scaleFactor + 0.1;
                ((PointCloud*)currObj)->scale(scaleFactor);
                break;
            }
                
            case GLFW_KEY_DOWN :{
                scaleFactor = scaleFactor - 0.1;
                ((PointCloud*)currObj)->scale(scaleFactor);
                break;
            }
                
            case GLFW_KEY_N: {
                ((PointCloud*)currObj)->toggleModelSwitch();
                break;
            }
                
            default:{
                break;
            }
		}
	}
}
