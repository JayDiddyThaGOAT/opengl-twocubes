// Include GLFW
//Authors: Chris Baroni, Jalen Jackson, Nathan Richards
//CPSC 484
//controls.cpp: Edits control header file to move and scale second cube
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

// Initial position : on +Z
glm::vec3 camPosition = glm::vec3( 0.0f, 0.0f, 10.0f );
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

float camYaw = -90.0f;
float camPitch = 0.0f;

// Target position
glm::vec3 camTarget = glm::vec3(0, 0, 0);

float camSpeed = 0.0f;

// Initial Field of View
float FoV = 45.0f;

float deltaTime = 0.0f; // Time between current frame & last frame
float lastTime = 0.0f; // Time of last frame

float lastX = 1024.0f / 2.0f;
float lastY = 768.0f / 2.0f;

float mouseSensitivity = 0.015f;

bool rightMouseButtonPressed;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	rightMouseButtonPressed = button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS;
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (!rightMouseButtonPressed)
	{
		lastX = xpos;
		lastY = ypos;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	camYaw = glm::mod(camYaw + xoffset, 360.0f);
	camPitch = glm::clamp(camPitch + yoffset, -90.0f, 90.0f);

	glm::vec3 front;
	front.x = cos(glm::radians(camYaw)) * cos(glm::radians(camPitch));
	front.y = sin(glm::radians(camPitch));
	front.z = sin(glm::radians(camYaw)) * cos(glm::radians(camPitch));
	camFront = glm::normalize(front);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	FoV = glm::clamp(FoV - float(yoffset), 1.0f, 45.0f);
}

void computeMatricesFromInputs(){

	float currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;

	camSpeed = 3.0f * deltaTime;
	
	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP) == GLFW_PRESS){
		camPosition += camSpeed * camFront;
	}
		// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		camPosition -= camSpeed * camFront;
	}
		// Strafe right
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		camPosition -= camSpeed * glm::normalize(glm::cross(camFront, camUp));
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		camPosition += camSpeed * glm::normalize(glm::cross(camFront, camUp));
	}

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
									camPosition,
									camPosition + camFront,
									camUp
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void transformCubeFromInputs(glm::mat4& ModelMatrix, int upKey, int leftKey, int downKey, int rightKey, int shrinkKey, int growKey)
{
	// Move up (increase Y-coordinate)
	if (glfwGetKey( window, upKey ) == GLFW_PRESS){
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, camSpeed, 0.0f));
	}

	// Move left (decrease X-coordinate)
	if (glfwGetKey( window, leftKey ) == GLFW_PRESS){
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-camSpeed, 0.0f, 0.0f));
	}
	// Move down (decrease Y-coordinate)
	if (glfwGetKey( window, downKey ) == GLFW_PRESS){
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -camSpeed, 0.0f));
	}
	// Move right (increase X-coordinate)
	if (glfwGetKey( window, rightKey ) == GLFW_PRESS){
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(camSpeed, 0.0f, 0.0f));
	}

	// Shrink (scale down 10%)
	if (glfwGetKey( window, shrinkKey ) == GLFW_PRESS){
		ModelMatrix = glm::scale(ModelMatrix,glm::vec3(.9,.9,.9)); //Down by 10%
	}

	// Grow (scale up 10%)
	if (glfwGetKey( window, growKey ) == GLFW_PRESS){
		ModelMatrix = glm::scale(ModelMatrix,glm::vec3(1.1,1.1,1.1)); //Up by 10%

	}
}