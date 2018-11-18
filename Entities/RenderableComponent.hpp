#ifndef KAGAMI_ENTITIES_RENDERABLECOMPONENT_H_
#define KAGAMI_ENTITIES_RENDERABLECOMPONENT_H_

#include <string>
#include <sstream>
#include <cstring>

#include <GL/glew.h>

#include <Component.hpp>

/*
struct Point{
	double x, y, z;
	int intensidade;
	int r, g, b;

	void draw(){
		glPointSize(1.0f);
        glBegin(GL_POINTS);
			glColor3f(r, g, b);
			glVertex3f(x, y, z);	  
        glEnd();
		//cout << r << " " << g << " " << b  << endl;
	}
};
*/

static const GLfloat standard_box[] = {
	-1.0f, -1.0f, -1.0f, // triangle 1 : begin
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f, -1.0f, // triangle 2 : begin
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f, // triangle 2 : end
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

static const GLfloat standard_box_normals[] = {
	-0.3333f, -0.3333f, -0.3333f, // triangle 1 : begin
	-0.3333f, -0.3333f, 0.3333f,
	-0.3333f, 0.3333f, 0.3333f, // triangle 1 : end
	0.3333f, 0.3333f, -0.3333f, // triangle 2 : begin
	-0.3333f, -0.3333f, -0.3333f,
	-0.3333f, 0.3333f, -0.3333f, // triangle 2 : end
	0.3333f, -0.3333f, 0.3333f,
	-0.3333f, -0.3333f, -0.3333f,
	0.3333f, -0.3333f, -0.3333f,
	0.3333f, 0.3333f, -0.3333f,
	0.3333f, -0.3333f, -0.3333f,
	-0.3333f, -0.3333f, -0.3333f,
	-0.3333f, -0.3333f, -0.3333f,
	-0.3333f, 0.3333f, 0.3333f,
	-0.3333f, 0.3333f, -0.3333f,
	0.3333f, -0.3333f, 0.3333f,
	-0.3333f, -0.3333f, 0.3333f,
	-0.3333f, -0.3333f, -0.3333f,
	-0.3333f, 0.3333f, 0.3333f,
	-0.3333f, -0.3333f, 0.3333f,
	0.3333f, -0.3333f, 0.3333f,
	0.3333f, 0.3333f, 0.3333f,
	0.3333f, -0.3333f, -0.3333f,
	0.3333f, 0.3333f, -0.3333f,
	0.3333f, -0.3333f, -0.3333f,
	0.3333f, 0.3333f, 0.3333f,
	0.3333f, -0.3333f, 0.3333f,
	0.3333f, 0.3333f, 0.3333f,
	0.3333f, 0.3333f, -0.3333f,
	-0.3333f, 0.3333f, -0.3333f,
	0.3333f, 0.3333f, 0.3333f,
	-0.3333f, 0.3333f, -0.3333f,
	-0.3333f, 0.3333f, 0.3333f,
	0.3333f, 0.3333f, 0.3333f,
	-0.3333f, 0.3333f, 0.3333f,
	0.3333f, -0.3333f, 0.3333f
};

class RenderableComponent : public Component{
public:
	// At the moment a RenderableComponent have only one model, it can be changed in the future
	ModelProperties* properties;
	glm::mat4 transformMatrix;
	std::string modelPath;


	RenderableComponent() :
		properties(new ModelProperties()),
		transformMatrix(),
		modelPath()
	{}

	bool assignModels(std::string modelPath, glm::mat4 &transf)
	{
		this->transformMatrix = transf;
		this->modelPath = modelPath;

		return true;
	}

	// Function to place an object in the scene
	bool initialize()
	{ 
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

		if(modelPath.find(".obj") != std::string::npos)
		{
			printf("It's a .obj!\n");
			
			printf("Opening the .obj\n");
			bool res = loadOBJ(modelPath.c_str(), vertices, uvs, normals);
			printf(".obj opened.\n");
		}
		else if (modelPath.find(".xyz") != std::string::npos)
		{
			printf("It's a point of a point cloud!\n");

			std::stringstream auxOutput;

			auxOutput << modelPath;
			glm::vec3 auxVert;
			auxOutput >> auxVert.x >> auxVert.y >> auxVert.z;
			//auxVert[0]*= 100;
			//auxVert[1]*= 100;
			//auxVert[2]*= 100;
			vertices.push_back(auxVert);

			printf("Point registered! %lf %lf %lf\n", vertices[0].x, vertices[0].y, vertices[0].z);
			/*
			//Point points;
			fstream reader_file;
		    reader_file.open (modelPath.c_str());
			
			if(reader_file.is_open()){    
				int i = 0, auxInt;
				while(!reader_file.eof()){
					reader_file >> vertices[i][0] >> vertices[i][1] >> vertices[i][2] >> auxInt >> 
						properties.materialColor[2] >> properties.materialColor[1] >> properties.materialColor[0];
					//colorCloud.push_back(points);		

					//cout << points.auxVert" << points.y << " "  << points.z << " "  << points.intensidade << " "  << points.b << " "  << points.g << " "  << points.r << " "  << endl;
								vertices.push_back(auxVert);i++;

				}
			}
			else	
				cout << "Arquivo não encontrado" << endl;	
			reader_file.close();
			*/
		}
		else{

			// A geometric form - as of writting the current standart is a box (fixed size of 36 vertices)
			
			GLfloat *box = new GLfloat[36 * 3];
			std::memcpy(box, standard_box, sizeof(GLfloat) * 36 * 3);

			GLfloat *normal_box = new GLfloat[36 * 3];
			std::memcpy(box, standard_box_normals, sizeof(GLfloat) * 36 * 3);

			for(int i = 0; i < 36 * 3; i)
			{				
				glm::vec3 auxVert, temp_normal;

				auxVert.x = box[i];
				temp_normal.x = normal_box[i++];

				auxVert.y = box[i];
				temp_normal.y = normal_box[i++];

				auxVert.z = box[i];
				temp_normal.z = normal_box[i++];

				vertices.push_back(glm::vec3(auxVert));
				normals.push_back(glm::vec3(temp_normal));
			}
			printf("\n");
			printf("Geometric form registered! (Currently using standard box.)\n");
		}

		properties->vertexSize = vertices.size();
		printf("Vertices size: %d\n", vertices.size());
		printf("Normals size: %d\n", normals.size());

		// Load it into a VBO
		//GLuint vertexbuffer;
		glGenBuffers(1, &properties->vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, properties->vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		/*
		//GLuint uvbuffer;
		glGenBuffers(1, &properties->uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, properties->uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
		*/
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
	/*
	bool initialize(std::string modelPath, glm::mat4 &transf, double x_pos, double y_pos,
					double z_pos, double theta, double width, double height, double length)
	{
		bool init_isOK = assignModels(modelPath, transf);
		init_isOK &= initialize();

		return init_isOK;
	}
	*/
	
	bool desalocate()
	{
		// Cleanup VBO and shader
		glDeleteBuffers(1, &properties->vertexbuffer);
		//glDeleteBuffers(1, &properties->uvbuffer);
		glDeleteBuffers(1, &properties->normalbuffer);
		//glDeleteTextures(1, &Texture);
		glDeleteVertexArrays(1, &properties->vao);
	
		return true;
	}
};

#endif