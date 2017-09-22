#ifndef ENTITY_H
#define ENTITY_H

#include "Component.hpp"
#include <map>
#include <string>
//#include <vector>
//#include <glm/glm.hpp>
//using namespace glm;

class Entity
{
private:
 	static const unsigned int MAX_COMPONENTS = 64;
 	//std::vector<Component> m_components;
 	//long long int componentKey;

public:
 	std::map <std::string, std::vector<Component> > m_components;
	//RenderableComponent renderableComp;
	GLuint id;

	bool initializer()
	{
		//componentKey = 0;
		return true;
	}

	bool initializer(std::string &modelPath, Component& comp)
	{
		bool init_isOK = initializer();
		init_isOK &= addComponent(modelPath, comp);

		return init_isOK;
	}

	bool addComponent(std::string &modelPath, Component& comp){
		if(m_components.size() > MAX_COMPONENTS)
			return false;
		else if (m_components.find(modelPath) == m_components.end())
			return false;
		else{
			//m_components.push_back();
			//componentKey |= comp;
			m_components[modelPath] = comp;

			return true;
		}
	}
};

#endif