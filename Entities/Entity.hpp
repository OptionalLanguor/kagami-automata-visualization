#ifndef ENTITY_H
#define ENTITY_H

#include "Component.hpp"
#include <vector>

class Entity
{
private:
	std::vector <Component> listComponents;
	//uint numComponents;

public:
	void hello();
};

#endif