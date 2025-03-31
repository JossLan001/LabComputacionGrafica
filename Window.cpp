#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica XX: Nombre de la practica", NULL, NULL);
	
	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//Ejes de carro
	 
	
	//Eje X
	if (key == GLFW_KEY_F) //Carro se mueve hacia atrás con tecla F
	{
		theWindow->mueveCarroX -= 1.0;
			
	}
	if (key == GLFW_KEY_G) //Carro se mueve hacia adelante con tecla G
	{
		theWindow->mueveCarroX += 1.0;
			
	}
	//Eje Z
	if (key == GLFW_KEY_H) //Carro se mueve hacia adelanta con tecla H
	{
		theWindow->mueveCarroZ += 1.0;

	}
	if (key == GLFW_KEY_J) //Carro se mueve hacia atras con tecla j
	{
		theWindow->mueveCarroZ -= 1.0;

	}

	
	if (key == GLFW_KEY_Q)
	{
		if (theWindow->cofre > 40.0)
		{

		}
		else
		{
			theWindow->cofre += 10.0;
		}
	}
	if (key == GLFW_KEY_Z)
	{
		if (theWindow->cofre < 10.0)
		{

		}
		else
		{
			theWindow->cofre -= 10.0;
		}
	}


	if (key == GLFW_KEY_R)
	{
		if (theWindow->llantaderdel > 100.0)
		{

		}
		else
		{
			theWindow->llantaderdel += 10.0;
		}
	}
	if (key == GLFW_KEY_T)
	{
		if (theWindow->llantaderdel < -100.0)
		{

		}
		else
		{
			theWindow->llantaderdel -= 10.0;
		}
	}

	if (key == GLFW_KEY_Y)
	{
		if (theWindow->llantaizqdel > 100.0)
		{

		}
		else
		{
			theWindow->llantaizqdel += 10.0;
		}
	}
	if (key == GLFW_KEY_U)
	{
		if (theWindow->llantaizqdel < -100.0)
		{

		}
		else
		{
			theWindow->llantaizqdel -= 10.0;
		}
	}

	if (key == GLFW_KEY_I)
	{
		if (theWindow->llantaizqtras > 100.0)
		{

		}
		else
		{
			theWindow->llantaizqtras += 10.0;
		}
	}
	if (key == GLFW_KEY_O)
	{
		if (theWindow->llantaizqtras < -100.0)
		{

		}
		else
		{
			theWindow->llantaizqtras -= 10.0;
		}
	}

	if (key == GLFW_KEY_E)
	{
		if (theWindow->llantadertras > 100.0)
		{

		}
		else
		{
			theWindow->llantadertras += 10.0;
		}
	}
	if (key == GLFW_KEY_P)
	{
		if (theWindow->llantadertras < -100.0)
		{

		}
		else
		{
			theWindow->llantadertras -= 10.0;
		}
	}



	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
