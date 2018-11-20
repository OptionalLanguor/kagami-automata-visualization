#pragma once

#ifndef KAGAMI_ENTITIES_ENGINE_H_
#define KAGAMI_ENTITIES_ENGINE_H_

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "System.hpp"
#include "Entity.hpp"

class Engine
{
private:
	// One should ask self, why thou use pointers? Respond when certain.
	static std::unique_ptr < std::vector<System*> > m_systems;
	static std::shared_ptr < std::vector<Entity*> > m_entities;
	//static std::shared_ptr <GLFWwindow*> window;

	static bool worldMoving;
	static glm::vec3 worldTransform;

	// ----- These are from tomdalling
	// Convenience function that returns a translation matrix
	static glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z);

	// onvenience function that returns a scaling matrix
	static glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z);

public:
	//static GLFWwindow* getWindow();
	
	void loadObjectsFile(std::string);

	void loadPointCloud(std::string);

	void Run(void);

	void Initialization(void);

	void Update();

	void RunLoop(void);

	//Deletion of pointers
	template <typename pointerType>
	void delete_pointed_to(pointerType* const ptr);

	bool Finalization(void);

	void AddSys(System* sys);

	void AddEnt(Entity* ent);

	void MoveWorld(glm::vec3 transform);

	static bool isWorldMoving();

	static glm::vec3 getWorldTransform();
};

#endif
