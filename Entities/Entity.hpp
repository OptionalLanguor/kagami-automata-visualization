#ifndef ENTITY_H
#define ENTITY_H

#include "Component.hpp"
//#include <vector>
//#include <glm/glm.hpp>
//using namespace glm;

class Entity
{
private:
 	static const unsigned int MAX_COMPONENTS = 64;
 	//std::vector<Component> m_components;
 	long long int componentKey;

public:
	RenderableComponent renderableComp;
	GLuint id;

	Entity(){
		componentKey = 0;
	}

	/*
	bool addComponent(const int& comp){
		if(m_components.size() > MAX_COMPONENTS)
			return false;
		else{
			//m_components.push_back();
			componentKey |= comp;
		}
	}
	*/
};

#endif