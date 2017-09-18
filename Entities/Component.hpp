#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entity.hpp"

class Component
{
	
	static GLuint current_id;

public:
	GLuint id;

	enum class Component_name{
		Renderable = (1 << 0)
	};
	
	Component() :
		id(current_id++)
	{}
};
//Initializing Component static attributes
GLuint Component::current_id;

#endif