#include "Engine.hpp"
// Include pointer management library for shared_prt

#include <memory>
#include <vector>
#include <fstream>
#include <string>

#include "System.hpp"
#include "Entity.hpp"
#include "RendererSystem.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>


GLFWwindow* window; //This is horrendous, but for the linking of libraries(control.cpp)
				// to work it's necessary at the moment.

//Initialization of static attributes
std::unique_ptr < std::vector<System*> > Engine::m_systems = std::unique_ptr < std::vector<System*> >(new std::vector<System*>);
std::shared_ptr < std::vector<Entity*> > Engine::m_entities = std::shared_ptr < std::vector<Entity*> >(new std::vector<Entity*>);
//std::shared_ptr < GLFWwindow*>  Engine::window;

bool Engine::worldMoving;
glm::vec3 Engine::worldTransform;

glm::mat4 Engine::translate(GLfloat x, GLfloat y, GLfloat z) {
	    return glm::translate(glm::mat4(), glm::vec3(x,y,z));
}

	// convenience function that returns a scaling matrix
glm::mat4 Engine::scale(GLfloat x, GLfloat y, GLfloat z) {
    return glm::scale(glm::mat4(), glm::vec3(x,y,z));
}

bool Engine::isWorldMoving(){
	return worldMoving;
}

glm::vec3 Engine::getWorldTransform(){
	return worldTransform;
}

/*GLFWwindow* Engine:: getWindow()
{
	return *window;
}*/

void Engine::loadObjectsFile(std::string filepath)
{
	std::ifstream inputHandle(filepath);

	if (inputHandle.is_open())
	{
		// read path to .obj, values to tranlate and values to scale
		std::string objPath = "empty";
		unsigned int semantic_class;
		double x_centroid, y_centroid, z_centroid, theta, width, height, lenght;

		while(inputHandle >> x_centroid >> y_centroid >> z_centroid >> theta >> width >> height >> lenght >> semantic_class)
		{
			// Respective model for semantic_class
			// void
			if (semantic_class == 0)
				objPath = "hazelnut.obj";
			// car
			else if (semantic_class == 1)
				objPath = "nope"; // "golf-cart.obj";
			// street
			else if (semantic_class == 2)
				objPath = "nope"; // "hazelnut.obj";
			// tree
			else if (semantic_class == 3)
				objPath = "hazelnut.obj";
			// sky
			else if (semantic_class == 4)
				objPath = "hazelnut.obj";
			// sidewalk
			else if (semantic_class == 5)
				objPath = "hazelnut.obj";
			// house
			else if (semantic_class == 6)
				objPath = "hazelnut.obj";
			else
				fprintf(stderr, "Semantic class invalid.\n");

			double street_plane_offset = 0.0674;
			double distance_scale = 10;

			Entity *newEntity;
			newEntity = new Entity();
			newEntity->initialize();
			newEntity->addRenderableComponent(objPath, 
							translate(distance_scale * (x_centroid * -1), distance_scale * (y_centroid), distance_scale * (z_centroid)) 
							* scale(distance_scale * width, distance_scale * height, distance_scale * lenght));
							//translate(x_centroid * -10, (y_centroid - street_plane_offset) * -10, z_centroid * 10) 
							//* scale(width, height, lenght));
			AddEnt(newEntity);
		}
		inputHandle.close();

	}
	else fprintf (stderr, "Failed to open file with objects.\n" );

	return;
}

void Engine::Run(void)
{
	printf("Entering Engine::Initialization()...\n");
	Initialization();
	printf("Engine::Initialization() Done.\n");

	printf("Alocatting objs to test...");

	// loadObjectsFile("obj1.txt");
	// loadObjectsFile("obj-car.txt");
	loadObjectsFile("input_3d-environment.txt");

	Entity* newEntity;

	/*
	newEntity = new Entity();
	newEntity->initialize();
	newEntity->addRenderableComponent("golf-cart.obj", translate(0,5,0) * scale(0.05,0.05,0.05));
	AddEnt(newEntity);
	*/

	newEntity = new Entity();
	newEntity->initialize();
	newEntity->addRenderableComponent("desert city.obj", translate(0,0,0));
	AddEnt(newEntity);
	/*
	newEntity = new Entity();
	newEntity->initialize();
	newEntity->addRenderableComponent("hazelnut.obj", translate(0,25,0));
	AddEnt(newEntity);
	*/
		/*
		//Point points;
		std::fstream reader_file;
	    reader_file.open ("color_cloud.xyz");
		printf("Aberta color_cloud\n");

		std::vector<std::string> inputPoint(3);
		glm::vec3 inputColor;

		newEntity = new Entity();
		newEntity->initialize();

		if(reader_file.is_open()){
			int i = 0, auxInt;
			while(!reader_file.eof()){

				reader_file >> inputPoint[0] >> inputPoint[1] >> inputPoint[2] >> auxInt >>
					inputColor[2] >> inputColor[1] >> inputColor[0];

				std::string auxStr = std::string(inputPoint[0] + " " + inputPoint[1] + " " + inputPoint[2]);

				newEntity->addRenderableComponent(inputPoint[0] + " " + inputPoint[1] + " " + inputPoint[2],
						translate(0, 0, 0), inputColor);

				//colorCloud.push_back(points);
				//cout << points.x << " " << points.y << " "  << points.z << " "  << points.intensidade << " "  << points.b << " "  << points.g << " "  << points.r << " "  << endl;
				i++;
			}
		}
		else	printf("Arquivo não encontrado\n");
		reader_file.close();


		printf("Number of renderableComponentes: %d\n", newEntity->sizeComponents());
		AddEnt(newEntity);
		*/

	printf(" Done.\n");


	printf("Entering Engine::RunLoop()... \n");
	RunLoop();
	printf("Engine::RunLoop() Done.\n");

	Finalization();
}

void Engine::Initialization(void)
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
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version.\n" );
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

	if(auxiliary_pointer->initialize(window, m_entities))
		AddSys(auxiliary_pointer);
	else
		printf("RendererSystem couldn't be initialized at Engine\n");
	return;

	//worldMoving = false;

	//For test purpose, world is moving.
	//MoveWorld(glm::vec3(0,1,5));
}

void Engine::Update()
{
	for(std::vector<System*>::iterator it = m_systems->begin(); it!= m_systems->end(); it++)
		(*it)->update();
}

void Engine::RunLoop(void)
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

// Deletion of pointers
template <typename pointerType>
void Engine::delete_pointed_to(pointerType* const ptr) { delete ptr; }

bool Engine::Finalization(void)
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	for(std::vector<System*>:: iterator it = m_systems->begin(); it!=m_systems->end(); it++)
		delete_pointed_to(*it);
	for(std::vector<Entity*>:: iterator it = m_entities->begin(); it!=m_entities->end(); it++)
		delete_pointed_to(*it);

	return true;
}

void Engine::AddSys(System* sys) {	m_systems->push_back(sys);}
void Engine::AddEnt(Entity* ent) {	Engine::m_entities->push_back(ent);}

void Engine::MoveWorld(glm::vec3 transform)
{
	this->worldMoving = true;
	worldTransform = transform;
}
