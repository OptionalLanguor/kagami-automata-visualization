// Include standard hibraries
#include <cstdlib>
#include <cstdio>
#include <vector>

// Include GLEW (OpenGL Extension Wrangler Library). 
// Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>

//Also, glew.h should be added before glfw3, as glfw3 documentation describes

// Include GLFW. To handle the window and the keyboard
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

//Common
#include "common/shader.hpp"
//#include "common/texture.hpp"
#include "common/controls.hpp"
#include "common/objloader.hpp"

//#include <GL/glut.h>
#include <cstring>
#include <string>
#include "Entities/Entity.hpp"

/*
 Represents a point light
 */
struct Light {
    glm::vec3 position;
    glm::vec3 intensities; //a.k.a. the color of the light
    float attenuation;
    float ambientCoefficient;
};


GLFWwindow* window; //This is horrendous, but for the linking of libraries(control.cpp)
					// to work it's necessary at the moment.

Light gLight;

//class Kagami {	
//};

class ModelProperties{ //Kinda of using the idea of tomdalling's code
public:
	static int current_id;
	int id;
	GLuint shaders;
	GLuint texture;
	GLuint vao;
	GLuint vbo;
	GLenum drawType;
	GLfloat shininess;
	glm::vec3 specularColor;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint vertexSize;

	ModelProperties() :
		id(++current_id),
		shaders(0),	//Maybe it's a good ideia to make shaders and texture pointers
		texture(0),
		vao(0),
		vbo(0),
		drawType(GL_TRIANGLES),
		shininess(0.0f),
		specularColor(1.0f, 1.0f, 1.0f),
		vertexbuffer(0),
		uvbuffer(0),
		normalbuffer(0),
		vertexSize(0)
	{}
};

//Initializing statics from ModelProperties
int ModelProperties::current_id;

struct ModelInstance{
	ModelProperties* properties;
	glm::mat4 transformMatrix;
	GLuint MatrixID;

	ModelInstance() :
		properties(NULL),
		transformMatrix(glm::mat4(1.0)),
		MatrixID(0)
	{}
};

// Function to place an object in the scene
void initializerModelInstance(ModelInstance &instance)
{
	instance.properties = new ModelProperties(); 
	instance.properties->shaders = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
	instance.properties->drawType = GL_TRIANGLES;
	instance.properties->shininess = 80.0; //Value used by tomdalling


	// Get a handle to our "MVP" uniform
	//instance.MatrixID = glGetUniformLocation(instance.properties->shaders, "MVP");

	// Binding arrays
	glGenVertexArrays(instance.properties->id, &instance.properties->vao);
	printf("%d\n", instance.properties->id);
	glGenBuffers(instance.properties->id, &instance.properties->vbo);

	// bind the VAO
    glBindVertexArray(instance.properties->vao);

    // bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, instance.properties->vbo);

    // Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	printf("Opening the .obj\n");
	//bool res = loadOBJ("desert city.obj", vertices, uvs, normals);
	bool res = loadOBJ("sportsCar.obj", vertices, uvs, normals);
	printf(".obj opened.\n");
	
	instance.properties->vertexSize = vertices.size();

	// Load it into a VBO
	//GLuint vertexbuffer;
	glGenBuffers(instance.properties->id, &instance.properties->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, instance.properties->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//GLuint uvbuffer;
	glGenBuffers(instance.properties->id, &instance.properties->uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, instance.properties->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	//GLuint normalbuffer;
	glGenBuffers(instance.properties->id, &instance.properties->normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, instance.properties->normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void desalocateModelInstance(ModelInstance &instance)
{
	// Cleanup VBO and shader
	glDeleteBuffers(instance.properties->id, &instance.properties->vertexbuffer);
	glDeleteBuffers(instance.properties->id, &instance.properties->uvbuffer);
	glDeleteBuffers(instance.properties->id, &instance.properties->normalbuffer);
	glDeleteProgram(instance.properties->shaders);
	//glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &instance.properties->vao);
}

void updateModelInstance(ModelInstance &instance, glm::mat4 &V, glm::mat4 &P)
{
	instance.MatrixID = glGetUniformLocation(instance.properties->shaders, "MVP");
	glm::mat4 MVP = P * V * instance.transformMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(instance.MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

void update(ModelInstance* instances)
{
	// Compute the MVP matrix from keyboard and mouse input
	computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	
	//We could loop this to work on more models
	for(int i = 0; i<1; i++)
		updateModelInstance(instances[i], ViewMatrix, ProjectionMatrix);
}

void drawModelInstance(const ModelInstance &instance)
{
	
	glBindVertexArray(instance.properties->id);
	
	// Bind our texture in Texture Unit 0
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	//glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0); // Enabling the var at vertexshader with layout=0
	glBindBuffer(GL_ARRAY_BUFFER, instance.properties->vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute - Selecting the var at vertexshader with layout=0
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, instance.properties->uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3nd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instance.properties->normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the obj !
	glBindVertexArray(instance.properties->vao);
	glDrawArrays(GL_TRIANGLES, 0, instance.properties->vertexSize);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//glBindVertexArray(0);

}

void draw(ModelInstance* instances)
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i = 0; i<2; i++)
		drawModelInstance(instances[i]);

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// ---------------------------------------------------------- These are from tomdalling
// convenience function that returns a translation matrix
glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z) {
    return glm::translate(glm::mat4(), glm::vec3(x,y,z));
}


// convenience function that returns a scaling matrix
glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z) {
    return glm::scale(glm::mat4(), glm::vec3(x,y,z));
}

int main(){
	printf("Hello, World!\n");

	//Initialize the ids of ModelProperties to use in VertexAttribArrays (VAO)
	
	Entity ent;
	ent.hello();	


	// Code from the tutorial -------------------------------------------------------

		// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Kagami - Automata Visualization", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE; //For VertexArrayID on the campus Ubuntu and for OSX
	//As of writing this, GLEW has a few issues with the OpenGL core profile we are using. 
	//Setting glewExperimental to true fixes the problem, 
	//but hopefully this won't be necessary in the future.
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	printf("GLEW initialized.\n");

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	printf("Before depth test.\n");
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	printf("After depth test.\n");

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	printf("After DepthFunc.\n");


	// Initializing the ModelInstance class for the .obj

	


	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
	
	/*
	GLuint VertexArrayID; //Creating the VAO
	glGenVertexArrays(1, &VertexArrayID); 
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
	*/

	// Get a handle for our "MVP" uniform
	//GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Getting a handle for the light uniform
	//GLuint LightID = glGetUniformLocation(programID, )

	// Load the texture
	//GLuint Texture = loadDDS("uvmap.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	//GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	/*
	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	printf("Opening the .obj\n");
	//bool res = loadOBJ("desert city.obj", vertices, uvs, normals);
	bool res = loadOBJ("sportsCar.obj", vertices, uvs, normals);
	printf(".obj opened.\n");
	
	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec2), &normals[0], GL_STATIC_DRAW);
	*/

	//while(true){};

	//std::vector <ModelInstance> instances;
	//std::vector<ModelInstance>::iterator it;

	//instances.push_back(ModelInstance());
	//instances.push_back(ModelInstance());
	//it = instances.begin();
	
	ModelInstance instances[2];
	initializerModelInstance(instances[0]);
	initializerModelInstance(instances[1]);
	instances[0].transformMatrix = translate(0,5,0);

	//it++;
	//initializerModelInstance(*it);
	//it->transformMatrix = translate(0,-4,0) * scale(1,2,1);
	
	glUseProgram(instances[0].properties->shaders);

	// FPS counter -------------------------------------------------------------------------
	double lastTime = glfwGetTime();
 	int nbFrames = 0;
	do{
		// Measure speed
	    double currentTime = glfwGetTime();
	    nbFrames++;
	    if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
	        // printf and reset timer
	        printf("%f ms/frame\n", 1000.0/double(nbFrames));
	        nbFrames = 0;
	        lastTime += 1.0;	//60fps = 16.6666ms; 30fps = 33.3333ms.
	    }
	    //end

		update(instances);
		draw(instances);

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
	
	//desalocateModelInstance(*sportsCar1);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
/*
class Object{
	virtual Object() {};
	virtual ~Object() {};
	virtual int id;
};

class Visible : public virtual Object{

};

class Car : public Visible{

};
*/