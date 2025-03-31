/*
Práctica 6: Texturizado
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"	
#include "Shader_m.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture dadoTexture;
Texture logofiTexture;

//TEXTURA DEL OCTAEDRO
Texture octaedroTexture;

//TEXTURAS DEL CARRO
Texture cofreTexture;
Texture chasisTexture;
Texture chasis2Texture;
Texture chasis3Texture;
Texture chasis4Texture;
Texture chasis5Texture;
Texture chasis6Texture;
Texture chasis7Texture;
Texture chasis8Texture;
Texture chasis9Texture;
Texture chasis10Texture;
Texture chasis11Texture;
Texture verdeTexture;
Texture negroTexture;


Model Kitt_M;
Model Llanta_M;
Model Dado_M;


//CARRO MODELOS

Model chasis_M;
Model cofre_M;
Model llantaizqtras_M;
Model llantadertras_M;
Model llantaderdel_M;
Model llantaizqdel_M;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_texture.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_texture.frag";


//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}



void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);



	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearDado()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,

		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,

		// right
		4, 5, 6,
		6, 7, 4,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		// POSICION				//COORDENADAS
		//						   TEXTURA

		//x		y		z			S Hor					T Ver			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.483381985754f ,0.3541124208579f ,			0.0f,	0.0f,	-1.0f,	//0  
		0.5f, -0.5f,  0.5f,		0.6752598337103f ,0.3546483925002f ,		0.0f,	0.0f,	-1.0f,	//1 
		0.5f,  0.5f,  0.5f,		0.6741878904255818f ,0.6237061569529214f ,	0.0f,	0.0f,	-1.0f,	//2  
		-0.5f,  0.5f,  0.5f,	0.4838417571448f ,0.6252507473015f ,		0.0f,	0.0f,	-1.0f,	//3	 

		// right 
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	   0.6752598337103f ,0.3546483925002f ,			-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,   0.8639218518125f ,0.3557203357849f ,			-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,   0.8639218518125f ,0.6253140718799f ,			-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	   0.6741878904255818f ,0.6237061569529214f ,	-1.0f,	0.0f,	0.0f,

		// back  
		-0.5f, -0.5f, -0.5f,	0.2940192849387f ,0.3546355243271f ,	0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.104510042698f ,0.3546813349129f  ,	0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.1042929746901f ,0.624070443335f ,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.2937469526142f ,0.625132000197f ,		0.0f,	0.0f,	1.0f,

		// left  
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.2940192849387f ,0.3546355243271f ,	1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.483381985754f ,0.3541124208579f  ,	1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.4838417571448f ,0.6252507473015f ,	1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.2937469526142f ,0.625132000197f ,		1.0f,	0.0f,	0.0f,

		// bottom 
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.483381985754f ,0.3541124208579f ,		    0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.6752598337103f ,0.3546483925002f ,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.6747794980921f ,0.0839183069277f ,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.4837132515993f ,0.0845571224265f ,		0.0f,	1.0f,	0.0f,

		//UP 
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.4838417571448f ,0.6252507473015f ,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.6741878904255818f ,0.6237061569529214f ,	0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.6731586319567f ,0.8942872787897f ,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.4834177497283f ,0.8941158579336f ,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);

}

//Octaedro

void CrearOctaedro()
{
	// Vértices del octaedro
	GLfloat octaedro_vertices[] = {
		// Vértice superior
	0.0f,  1.0f,  0.0f,   0.5f, 1.0f,   0.0f, 1.0f, 0.0f,  // Vértice 0 (superior)

	// Vértice inferior
	0.0f, -1.0f,  0.0f,   0.5f, 0.0f,   0.0f, -1.0f, 0.0f,  // Vértice 1 (inferior)

	// Base (4 vértices alrededor del centro)
	-1.0f,  0.0f,  0.0f,   0.0f, 0.5f,   -1.0f, 0.0f, 0.0f,  // Vértice 2 (izquierda)
	 1.0f,  0.0f,  0.0f,   1.0f, 0.5f,   1.0f, 0.0f, 0.0f,  // Vértice 3 (derecha)
	 0.0f,  0.0f,  1.0f,   0.5f, 0.75f,   0.0f, 0.0f, 1.0f,  // Vértice 4 (frente)
	 0.0f,  0.0f, -1.0f,   0.5f, 0.25f,   0.0f, 0.0f, -1.0f,  // Vértice 5 (atrás)
	};

	// Índices del octaedro
	unsigned int octaedro_indices[] = {

		// Caras superiores (4 triángulos)

		0, 2, 4,   // Cara 1 - Frente Izquierda
		0, 4, 3,   // Cara 2 - Frente Derecha
		0, 3, 5,   // Cara 3 - Atrás Derecha
		0, 5, 2,   // Cara 4 - Atrás Izquierda

		// Caras inferiores (4 triángulos)

		1, 2, 4,   // Cara 5 - Frente Izquierda Inferior
		1, 4, 3,   // Cara 6 - Frente Derecha Inferior
		1, 3, 5,   // Cara 7 - Atrás Derecha Inferior
		1, 5, 2    // Cara 8 - Atrás Izquierda Inferior
	};

	// Crear el mesh para el octaedro
	Mesh* octaedro = new Mesh();
	octaedro->CreateMesh(octaedro_vertices, octaedro_indices, sizeof(octaedro_vertices) / sizeof(GLfloat), sizeof(octaedro_indices) / sizeof(unsigned int));
	meshList.push_back(octaedro);

}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
	CreateShaders();
	CrearOctaedro();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	dadoTexture = Texture("Textures/dado_animales1.png");
	dadoTexture.LoadTextureA();


	//TEXTURA DEL OCTAEDRO 

	octaedroTexture = Texture("Textures/galaxia.tga");
	octaedroTexture.LoadTexture();


	//TEXTURAS DEL CARRO
	cofreTexture = Texture("Textures/escudo_fi_color.tga");
	cofreTexture.LoadTextureA();

	chasisTexture = Texture("Textures/M1.tga");
	chasisTexture.LoadTextureA();

	chasis2Texture = Texture("Textures/bym.tga");
	chasis2Texture.LoadTextureA();

	chasis3Texture = Texture("Textures/J.tga");
	chasis3Texture.LoadTextureA();

	chasis4Texture = Texture("Textures/ML1.tga");
	chasis4Texture.LoadTextureA();

	chasis5Texture = Texture("Textures/red eyes.tga");
	chasis5Texture.LoadTextureA();

	chasis6Texture = Texture("Textures/ML2.tga");
	chasis6Texture.LoadTextureA();

	chasis7Texture = Texture("Textures/ML3.tga");
	chasis7Texture.LoadTextureA();

	chasis8Texture = Texture("Textures/Calcaca.tga");
	chasis8Texture.LoadTextureA();

	chasis9Texture = Texture("Textures/ML4.tga");
	chasis9Texture.LoadTextureA();

	chasis10Texture = Texture("Textures/calavera.tga");
	chasis10Texture.LoadTextureA();

	chasis11Texture = Texture("Textures/ML5.tga");
	chasis11Texture.LoadTextureA();

	verdeTexture = Texture("Textures/verde.tga");
	verdeTexture.LoadTextureA();

	negroTexture = Texture("Textures/negro.tga");
	negroTexture.LoadTextureA();



	//cargar los modelos

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_cofret.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");


	//Ejercicio 2
	Dado_M = Model();
	Dado_M.LoadModel("Models/cubo.obj");


	//CARRO
	chasis_M = Model();
	chasis_M.LoadModel("Models/chasism.obj");

	cofre_M = Model();
	cofre_M.LoadModel("Models/cofrem.obj");

	llantaizqtras_M = Model();
	llantaizqtras_M.LoadModel("Models/llantaizqm.obj");

	llantadertras_M = Model();
	llantadertras_M.LoadModel("Models/llantaderm.obj");

	llantaizqdel_M = Model();
	llantaizqdel_M.LoadModel("Models/llantaizqm.obj");

	llantaderdel_M = Model();
	llantaderdel_M.LoadModel("Models/llantaderm.obj");


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		color = glm::vec3(1.0f, 1.0f, 1.0f);//color blanco, multiplica a la información de color de la textura

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();


		//Dado de Opengl
		//Ejercicio 1: Texturizar su cubo con la imagen dado_animales ya optimizada por ustedes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		//meshList[4]->RenderMesh();

		//Ejercicio 2:Importar el cubo texturizado en el programa de modelado con 
		//la imagen dado_animales ya optimizada por ustedes

		//Dado importado
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, 3.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado_M.RenderModel();
		*/

		//PRACTICA 6 REPORTE

		//OCTAEDRO 

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		octaedroTexture.UseTexture();
		meshList[5]->RenderMesh();
		

		//CHASIS

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(mainWindow.getmueveCarroX(), 0.0f, 0.0f + mainWindow.getmueveCarroZ()));//Movimiento del carro
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		chasis_M.RenderModel();

		//Cofre

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.9f, 0.6f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getcofre()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		cofre_M.RenderModel();

		//Llanta derecha delantera

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.85f, -1.0f, -1.9f));
		model = glm::rotate(model, glm::radians(mainWindow.getllantaderdel()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		llantaderdel_M.RenderModel();


		//Llanta izquierda delantera

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.85f, -1.0f, 1.9f));
		model = glm::rotate(model, glm::radians(mainWindow.getllantadertras()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		llantaizqdel_M.RenderModel();

		//Llanta derecha trasera

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.85f, -1.0f, -1.9f));
		model = glm::rotate(model, glm::radians(mainWindow.getllantaizqdel()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		llantadertras_M.RenderModel();

		//Llanta izquierda trasera 

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.85f, -1.0f, 1.9f));
		model = glm::rotate(model, glm::radians(mainWindow.getllantaizqtras()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		llantaizqtras_M.RenderModel();



		//mas es hacia adelante en x   menos hacia atras 


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
/*
//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		logofiTexture.UseTexture(); //textura con transparencia o traslucidez
		FIGURA A RENDERIZAR de OpenGL, si es modelo importado no se declara UseTexture
		glDisable(GL_BLEND);
*/