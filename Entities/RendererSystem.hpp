#ifndef KAGAMI_ENTITIES_RENDERINGSYSTEM_H_
#define KAGAMI_ENTITIES_RENDERINGSYSTEM_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp> // For glm::translate()

#include "System.hpp"
#include "Engine.hpp"
#include "../common/shader.hpp"

#include "../common/controls.hpp" // To use computeMatricesFromInputs()


//#include <iostream>

//---------------------------------------------------------------------------------------------------------
/* RendererSystem
	Class RendererSystem is the class that will manage everything graphic related.

	1. There should be only one instance of the class.
	1. It's a System so it should be encapsulated for Engine access.
*/
class RendererSystem : public System {
public:
	std::shared_ptr < std::vector<Entity*> > m_entities;
	GLFWwindow* window;
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

	bool initialize(GLFWwindow* window, std::shared_ptr < std::vector<Entity*> > entities)
	{
		this->window = window;
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
			for(std::vector<RenderableComponent>::iterator it2 = renderableComponents.begin(); it2 != renderableComponents.end(); it2++){
				drawRenderableComponent(*it2, ProjectionMatrix, ViewMatrix);
			}
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void update(){
		// Conditional to move all the world elements
		if(Engine::isWorldMoving()){
			std::vector<RenderableComponent> renderableComponents;
			for(std::vector<Entity*>::iterator it = m_entities->begin(); it!=m_entities->end(); ++it){
				renderableComponents = (**it).getRenderableComponents();
				for(std::vector<RenderableComponent>::iterator it2 = renderableComponents.begin(); it2 != renderableComponents.end(); it2++){
					if(it2 != renderableComponents.begin()){ // Assuming the first element is the car
						//std::cout << it2->transformMatrix << endl << endl;
						it2->transformMatrix = glm::translate(it2->transformMatrix, Engine::getWorldTransform());
						//std::cout << it2->transformMatrix << endl << endl;
					}
				}
			}
		}
		
		draw();
	}
};

#endif