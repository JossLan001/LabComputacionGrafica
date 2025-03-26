#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat getangulocola() { return angulocola; }
	GLfloat getpataizqdel() { return pataizqdel; }
	GLfloat getpataderdel() { return pataderdel; }
	GLfloat getpataizqtras() { return pataizqtras; }
	GLfloat getpatadertras() { return patadertras; }

	GLfloat getcofre() { return cofre; }
	GLfloat getllantaizqdel() { return llantaizqdel; }
	GLfloat getllantaderdel() { return llantaderdel; }
	GLfloat getllantaizqtras() { return llantaizqtras; }
	GLfloat getllantadertras() { return llantadertras; }

	
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat angulocola = 0.0f;
	GLfloat pataizqdel = 0.0f;
	GLfloat pataderdel = 0.0f;
	GLfloat pataizqtras = 0.0f;
	GLfloat patadertras = 0.0f;

	GLfloat cofre = 0.0f;
	GLfloat llantaizqdel = 0.0f;
	GLfloat llantaderdel = 0.0f;
	GLfloat llantaizqtras = 0.0f;
	GLfloat llantadertras = 0.0f;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};

