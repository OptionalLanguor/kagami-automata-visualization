// Include standard libraries
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>

// Include pointer management library for shared_prt
#include <memory>

// Include error handling librarie
#include <exception>

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

// Entities
#include "Entities/Entity.hpp"
//#include "Entities/Entity.cpp"
//#include "Entities/Component.hpp"
//#include "Entities/Component.cpp"


/* To generate Diagrams with doxygraph at terminal:
	sudo perl doxygraph/doxygraph /home/aluno/Kagami/xml/index.xml doxyviz/htdocs/graph.dot

*/

// ---------------------------------------------------------- These are from tomdalling
// convenience function that returns a translation matrix
glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z) {
    return glm::translate(glm::mat4(), glm::vec3(x,y,z));
}

// convenience function that returns a scaling matrix
glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z) {
    return glm::scale(glm::mat4(), glm::vec3(x,y,z));
}

class System
{
public:
	// The idea of enum is to identify each systems so they can be processed
	// properly by the Engine class
	enum System_type {
		Renderer
	};
	// All systems must update each game loop
	// = 0 means derived classes must provide an implementation, not that the base class can not provide an implementation.
	virtual void update() = 0;// float dt ) = 0;

	// It's good practice to separate the construction and initialization code.
	virtual bool initialize() = 0;

	virtual bool shutdown() = 0;

	// This recieves any messages sent to the core engine in Engine.cpp
	//virtual void SendMessage( Message *msg ) = 0;

	///All systems need a virtual destructor to have their destructor called 
	virtual ~System( ) {}
};

GLFWwindow* window; //This is horrendous, but for the linking of libraries(control.cpp)
				// to work it's necessary at the moment.

/*
 	Initially EntityManager class was supposed to the creator of Entities and would
 	check for existent Entities or destroy them.
	My idea is to use EntityManager as the initializer for different type of
	predefined Entities (Like the car we want to project that have certain types
	of components.)
*/
class EntityManager
{
private:
	//std::unordered_set<Entity> m_entities;		// C++11 compiler necessary
	static std::shared_ptr < std::vector<Entity*> > m_entities;
	Entity m_next;

public:
	bool assignEntities(std::shared_ptr < std::vector<Entity*> > &entities){
		m_entities = std::shared_ptr < std::vector<Entity*> >(entities);
		return true;
	}

	bool initialize()
	{
		m_entities = NULL;
	}

	bool initialize(std::shared_ptr < std::vector<Entity*> > entities)
	{
		bool init_isOK = initialize();
		init_isOK &= assignEntities(entities);

		return init_isOK;
	}

	bool AddEntity(std::string modelFile, glm::mat4 transformMatrix)//Entity& ent)
	{
		//m_entities->push_back(&ent); //Is this ok? Should I use pointers instead?
		return true;
	}

	/*
	// This was supposed to be for std:unordered_set implementation
	Entity create()
	{
		++m_next.id;
		while (alive(m_next))
			++m_next.id;
		m_entities.insert(m_next);
		
		return m_next;
	}
	
	bool alive(Entity e)
	{
		return m_entities.has(e);
	}

	void destroy(Entity e)
	{
		m_entities.erase(e);
	}
	*/
};



//---------------------------------------------------------------------------------------------------------
/* RendererSystem
	Class RendererSystem is the class that will manage everything graphic related.

	1. There should be only one instance of the class.
	1. It's a System so it should be encapsulated for Engine access.
*/
class RendererSystem : public System {
public:
	std::shared_ptr < std::vector<Entity*> > m_entities;
	GLuint shaders;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint LightID;

	// I would be interesting to try and not assign data on the constructor,
	// in a way that all that would be done on Init(). So we can assign the memory of the Rendering class anywhere
	// without having problem o linking attributes.
	/*
	Rendering(std::shared_ptr < std::vector<ModelInstance*> > engModels) :
		m_models(NULL),
		shaders(LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" )),	//Maybe it's a good ideia to make shaders and texture pointers
		MatrixID(glGetUniformLocation(shaders, "MVP")),
		ViewMatrixID(glGetUniformLocation(shaders, "V")),
		ModelMatrixID(glGetUniformLocation(shaders, "M")),
		LightID(glGetUniformLocation(shaders, "LightPosition_worldspace"))
	{
		assignModels(engModels);
	}
	~Rendering()
	{
		glDeleteProgram(shaders)
	}*/

	bool assignEntities(std::shared_ptr < std::vector<Entity*> > &entities){
		printf("Assigning Entities... ");
		m_entities = std::shared_ptr < std::vector<Entity*> >(entities);
		printf("Entities Assigned!\n");

		return true;
	}

	bool initialize(){
		m_entities = NULL; //Maybe the ideia of this line is not cool for cache coherency
		//Maybe it's a good ideia to make shaders and texture pointers
		this->shaders = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
		this->MatrixID = glGetUniformLocation(shaders, "MVP");
		this->ViewMatrixID = glGetUniformLocation(shaders, "V");
		this->ModelMatrixID = glGetUniformLocation(shaders, "M");
		this->LightID = glGetUniformLocation(shaders, "LightPosition_worldspace");
	
		return true;
	}

	bool initialize(std::shared_ptr < std::vector<Entity*> > entities)
	{
		bool init_isOK = initialize();
		init_isOK &= assignEntities(entities);

		return init_isOK;
	}

	bool shutdown(){
		glDeleteProgram(shaders);
		return true;
	}
	
	void drawRenderableComponent(const RenderableComponent &instance, const glm::mat4 &ProjectionMatrix, const glm::mat4 &ViewMatrix)
	{
		glBindVertexArray(instance.properties->vao);

		glUseProgram(shaders);

		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * instance.transformMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &instance.transformMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(0,15,0);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);


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

		// Draw the obj!
		glDrawArrays(GL_TRIANGLES, 0, instance.properties->vertexSize);
	}
	
	void draw()
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		
		//printf("%lu objs to draw.\n", m_models->size());
		//Find RenderableComponents in entities
		std::vector<RenderableComponent> renderableComponents;
		for(std::vector<Entity*>::const_iterator it = m_entities->begin(); it!=m_entities->end(); ++it){
			renderableComponents = (**it).getRenderableComponents();
			for(std::vector<RenderableComponent>::iterator it2 = renderableComponents.begin(); it2 != renderableComponents.end(); it2++)
				drawRenderableComponent(*it2, ProjectionMatrix, ViewMatrix);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void update(){
		draw();
	}
};


class Engine
{
private:
	// One should ask self, why thou use pointers? Respond when certain.
	static std::unique_ptr < std::vector<System*> > m_systems;
	static std::shared_ptr < std::vector<Entity*> > m_entities;

public:
	void Run(void)
	{
		printf("Entering Engine::Initialization()...\n");
		Initialization();
		printf("Engine::Initialization() Done.\n");


		printf("Alocatting objs to test...");

		Entity* newEntity = new Entity();
		newEntity->initialize();
		newEntity->addRenderableComponent("golf-cart.obj", translate(0,5,0) * scale(0.05,0.05,0.05));
		AddEnt(newEntity);

		newEntity = new Entity();
		newEntity->initialize();
		newEntity->addRenderableComponent("desert city.obj", translate(0,5,0));
		AddEnt(newEntity);

		newEntity = new Entity();
		newEntity->initialize();
		newEntity->addRenderableComponent("hazelnut.obj", translate(0,25,0));
		AddEnt(newEntity);

		printf(" Done.\n");


		printf("Entering Engine::RunLoop()... \n");
		RunLoop();
		printf("Engine::RunLoop() Done.\n");

		Finalization();
	}

	void Initialization(void)
	{
		printf("Hello, World!\n");

		// Initialize GLFW
		if( !glfwInit() )
		{
			fprintf(stderr, "Failed to initialize GLFW\n" );
			getchar();
			return;
			//return -1;
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
			return;
			//return -1;
		}
		glfwMakeContextCurrent(window);

		//old Initialize GLEW
		// Initialize GLEW
		glewExperimental = GL_TRUE; //For VertexArrayID on the campus Ubuntu and for OSX
			//As of writing this, GLEW has a few issues with the OpenGL core profile we are using. 
			//Setting glewExperimental to true fixes the problem, 
			//but hopefully this won't be necessary in the future.

		GLenum err = glewInit();
		if (err != GLEW_OK) 
		{
			fprintf(stderr, "Failed to initialize GLEW\n");
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			getchar();
			glfwTerminate();
			return;
			//return -1;
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

		// Cull triangles which normal is not towards the camera
		glEnable(GL_CULL_FACE);
		
		// Get a handle for our "MVP" uniform
		//GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		// Getting a handle for the light uniform
		//GLuint LightID = glGetUniformLocation(programID, )

		// Load the texture
		//GLuint Texture = loadDDS("uvmap.DDS");
		
		// Get a handle for our "myTextureSampler" uniform
		//GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
		
		//Rendering *render = new Rendering(m_models);
		//render->assignModels(m_models);
		RendererSystem *auxiliary_pointer =  new RendererSystem();
		
		if(auxiliary_pointer->initialize(m_entities))
			AddSys(auxiliary_pointer);
		else
			printf("RendererSystem couldn't be initialized at Engine\n");
		return;
	}

	void Update()// float dt );
	{
		for(std::vector<System*>::iterator it = m_systems->begin(); it!= m_systems->end(); it++)
			(*it)->update();
	}

	void RunLoop(void)
	{
		printf("In Engine::RunLoop()... \n");
		//FPS counter -------------------------------------------------------------------------
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
		    Update();
			
		} // Check if the ESC key was pressed or the window was closed
		while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			   glfwWindowShouldClose(window) == 0 );
	}

	//Deletion of pointers
	template <typename pointerType>
	void delete_pointed_to(pointerType* const ptr) { delete ptr; }

	bool Finalization(void)
	{
		// Close OpenGL window and terminate GLFW
		glfwTerminate();

		for(std::vector<System*>:: iterator it = m_systems->begin(); it!=m_systems->end(); it++)
			delete_pointed_to(*it);
		for(std::vector<Entity*>:: iterator it = m_entities->begin(); it!=m_entities->end(); it++)
			delete_pointed_to(*it);

		return true;
	}

	void AddSys(System* sys)
	{
		m_systems->push_back(sys);
	}
	
	void AddEnt(Entity* ent)
	{
		m_entities->push_back(ent);
	}
	
};
//Initialization of static attributes
std::unique_ptr < std::vector<System*> > Engine::m_systems = std::unique_ptr < std::vector<System*> >(new std::vector<System*>);
std::shared_ptr < std::vector<Entity*> > Engine::m_entities = std::shared_ptr < std::vector<Entity*> >(new std::vector<Entity*>);

/*
 Represents a point light
 */
struct Light {
    glm::vec3 position;
    glm::vec3 intensities; //a.k.a. the color of the light
    float attenuation;
    float ambientCoefficient;
};
//Light gLight;feed/?trk=


int main(){
	Engine* Kagami = new Engine();
	Kagami->Run();
	
	return 0;
}