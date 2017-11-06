#ifndef KAGAMI_ENTITIES_COMPONENT_H_
#define KAGAMI_ENTITIES_COMPONENT_H_

#include <GL/glew.h>
#include "../common/objloader.hpp" // I'd like to change that but I don't know how at the moment


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

class ModelProperties{
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

#endif