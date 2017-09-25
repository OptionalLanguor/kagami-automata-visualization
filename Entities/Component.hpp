//#ifndef KAGAMI_ENTITIES_COMPONENT_H_
//#define KAGAMI_ENTITIES_COMPONENT_H_

//#include "Entity.hpp"
#include <GL/glew.h>
#include <string>
#include "../common/objloader.hpp"

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


class ModelProperties{ //Kinda of using the idea of tomdalling's code
public:
	// There is no member shader (only at RendererSystem) at moment but it 
	// could be a good idea when the program have more than one.
	GLuint texture;
	GLuint vao;
	GLuint vbo;
	GLenum drawType;
	GLfloat shininess;
	glm::vec3 specularColor;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint vertexSize;

	ModelProperties() :
		texture(0),
		vao(0),
		vbo(0),
		drawType(GL_TRIANGLES),
		shininess(0.0f),
		specularColor(1.0f, 1.0f, 1.0f),
		vertexbuffer(0),
		uvbuffer(0),
		normalbuffer(0),
		vertexSize(0)
	{}
};

class RenderableComponent : public Component{
public:
	// At the moment a RenderableComponent have only one model, it can be changed in the future
	ModelProperties* properties;
	glm::mat4 transformMatrix;
	std::string modelPath;

	RenderableComponent() :
		properties(NULL),
		transformMatrix(),
		modelPath()
	{}
	/*
	RenderableComponent(std::string modelPath, glm::mat4 &transf) :
		properties(NULL),
		transformMatrix(transf),
		modelPath(modelPath)
	{
		//transformMatrix = transf;
	}
	*/

	bool assignModels(std::string modelPath, glm::mat4 &transf)
	{
		this->transformMatrix = transf;
		this->modelPath = modelPath;

		return true;
	}

	// Function to place an object in the scene
	bool initialize()
	{
		properties = new ModelProperties(); 
		properties->shininess = 80.0; //Value used by tomdalling

		// Binding arrays
		glGenVertexArrays(1, &properties->vao);
		glGenBuffers(1, &properties->vbo);

		// bind the VAO
	    glBindVertexArray(properties->vao);

	    // bind the VBO
	    glBindBuffer(GL_ARRAY_BUFFER, properties->vbo);

	    // Read our .obj file
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals; // Won't be used at the moment.
		printf("Opening the .obj\n");
		//bool res = loadOBJ("desert city.obj", vertices, uvs, normals);
		bool res = loadOBJ(modelPath.c_str(), vertices, uvs, normals);
		printf(".obj opened.\n");
		
		properties->vertexSize = vertices.size();

		// Load it into a VBO
		//GLuint vertexbuffer;
		glGenBuffers(1, &properties->vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, properties->vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		//GLuint uvbuffer;
		glGenBuffers(1, &properties->uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, properties->uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

		//GLuint normalbuffer;
		glGenBuffers(1, &properties->normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, properties->normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

		//glBindVertexArray(0);

		return true;
	}

	bool initialize(std::string modelPath, glm::mat4 &transf)
	{
		bool init_isOK = assignModels(modelPath, transf);
		init_isOK &= initialize();

		return init_isOK;
	}

	bool desalocate()
	{
		// Cleanup VBO and shader
		glDeleteBuffers(1, &properties->vertexbuffer);
		glDeleteBuffers(1, &properties->uvbuffer);
		glDeleteBuffers(1, &properties->normalbuffer);
		//glDeleteTextures(1, &Texture);
		glDeleteVertexArrays(1, &properties->vao);
	
		return true;
	}
};

//#endif