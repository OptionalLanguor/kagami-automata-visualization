/*
Use standard order for readability and to avoid hidden dependencies: 
	Related header, C library, C++ library, other libraries' .h, your project's .h.
*/

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

// Our libs
#include "Entities/Engine.hpp"


/* To generate Diagrams with doxygraph at terminal:
	sudo perl doxygraph/doxygraph /home/aluno/Kagami/xml/index.xml doxyviz/htdocs/graph.dot

*/

//GLFWwindow* window; //This is horrendous, but for the linking of libraries(control.cpp)
				// to work it's necessary at the moment.

/*
 	Initially EntityManager class was supposed to the creator of Entities and would
 	check for existent Entities or destroy them.
	My idea is to use EntityManager as the initializer for different type of
	predefined Entities (Like the car we want to project that have certain types
	of components.)
*/
/*
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
};

/*
 Represents a point light
 
struct Light {
    glm::vec3 position;
    glm::vec3 intensities; //a.k.a. the color of the light
    float attenuation;
    float ambientCoefficient;
};
//Light gLight;feed/?trk=
*/

int main(){
	printf("Hey\n");
	Engine* Kagami = new Engine();
	Kagami->Run();
	
	return 0;
}