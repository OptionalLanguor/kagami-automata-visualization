//define name: <PROJECT>_<PATH>_<FILE>_H_

#ifndef KAGAMI_ENTITIES_ENTITY_H_
#define KAGAMI_ENTITIES_ENTITY_H_

#include "Component.hpp"
#include <map>
#include <string>

class Entity
{
private:
 	static const unsigned int MAX_COMPONENTS = 64;
 	static GLuint current_id;

public:

	const GLuint id;
	std::vector<RenderableComponent> renderableComponents;
	
	Entity(): id(current_id++) {}
	bool initialize()
	{
		//componentKey = 0;
		return true;
	}

	bool addRenderableComponent(RenderableComponent& comp)
	{
		if(sizeComponents() > MAX_COMPONENTS)
			return false;
		else{
			renderableComponents.push_back(comp);
			return true;
		}
	}

	bool addRenderableComponent(std::string modelPath, glm::mat4 transf)
	{
		if(sizeComponents() > MAX_COMPONENTS)
			return false;
		else{
			RenderableComponent* rComp = new RenderableComponent();
			rComp->initialize(modelPath, transf);
			renderableComponents.push_back(*rComp);
			return true;
		}
	}

	unsigned int sizeComponents()
	{
		return renderableComponents.size();
	}

	std::vector<RenderableComponent> getRenderableComponents() {return renderableComponents;}

};

#endif