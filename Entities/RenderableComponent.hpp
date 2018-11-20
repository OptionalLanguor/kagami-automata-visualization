#ifndef KAGAMI_ENTITIES_RENDERABLECOMPONENT_H_
#define KAGAMI_ENTITIES_RENDERABLECOMPONENT_H_

#include <string>
#include <sstream>
#include <cstring>
#include <fstream>

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
	-0.5f, -0.5f, -0.5f, // triangle 1 : begin
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f, // triangle 1 : end
	0.5f, 0.5f, -0.5f, // triangle 2 : begin
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f, // triangle 2 : end
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f
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
		std::vector<glm::vec2> uvs; // Won't be used at the moment.
		std::vector<glm::vec3> normals;

		if(modelPath.find(".obj") != std::string::npos)
		{
			printf("It's a .obj!\n");
			
			printf("Opening the .obj\n");
			bool res = loadOBJ(modelPath.c_str(), vertices, uvs, normals);
			printf(".obj opened.\n");
		}
		else if (modelPath.find(".xyz") != std::string::npos)
		{
			printf("It's a point cloud!\n");

			std::ifstream aux_handler(modelPath);

			glm::vec3 standard_normal1 = glm::vec3(0.3333f, 0.3333f, 0.3333f);
			glm::vec3 standard_normal2 = glm::vec3(0.3333f, 0.3333f, -0.3333f);
			glm::vec3 standard_normal3 = glm::vec3(0.3333f, -0.3333f, 0.3333f);
			glm::vec3 standard_normal4 = glm::vec3(0.3333f, -0.3333f, -0.3333f);
			glm::vec3 standard_normal5 = glm::vec3(-0.3333f, 0.3333f, 0.3333f);
			glm::vec3 standard_normal6 = glm::vec3(-0.3333f, 0.3333f, -0.3333f);
			glm::vec3 standard_normal7 = glm::vec3(-0.3333f, -0.3333f, 0.3333f);
			glm::vec3 standard_normal8 = glm::vec3(-0.3333f, -0.3333f, -0.3333f);

			if (aux_handler.is_open())
			{
				double x_aux, y_aux, z_aux;
				int gray_intensity, blue_aux, green_aux, red_aux;
				int scale = 1; 

				while (aux_handler >> x_aux >> y_aux >> z_aux >> gray_intensity >> blue_aux >> green_aux >> red_aux)
				{

					x_aux *= scale;
					y_aux *= -scale;
					z_aux *= -scale;

					//for(int i = 0; i < 3; i++){

						

						vertices.push_back(glm::vec3(x_aux, y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal1));

						vertices.push_back(glm::vec3(x_aux - (0.0005), y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal1));

						vertices.push_back(glm::vec3(x_aux, y_aux - (0.0005), z_aux));
						normals.push_back(glm::vec3(standard_normal1));
		

						vertices.push_back(glm::vec3(x_aux, y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal2));

						vertices.push_back(glm::vec3(x_aux - (0.0005), y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal2));

						vertices.push_back(glm::vec3(x_aux, y_aux - (0.0005), z_aux));
						normals.push_back(glm::vec3(standard_normal2));
		

						vertices.push_back(glm::vec3(x_aux, y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal3));

						vertices.push_back(glm::vec3(x_aux - (0.0005), y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal3));

						vertices.push_back(glm::vec3(x_aux, y_aux - (0.0005), z_aux));
						normals.push_back(glm::vec3(standard_normal3));
		

						vertices.push_back(glm::vec3(x_aux, y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal4));

						vertices.push_back(glm::vec3(x_aux - (0.0005), y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal4));

						vertices.push_back(glm::vec3(x_aux, y_aux - (0.0005), z_aux));
						normals.push_back(glm::vec3(standard_normal4));
		

						vertices.push_back(glm::vec3(x_aux, y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal5));

						vertices.push_back(glm::vec3(x_aux - (0.0005), y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal5));

						vertices.push_back(glm::vec3(x_aux, y_aux - (0.0005), z_aux));
						normals.push_back(glm::vec3(standard_normal5));
		

						vertices.push_back(glm::vec3(x_aux, y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal6));

						vertices.push_back(glm::vec3(x_aux - (0.0005), y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal6));

						vertices.push_back(glm::vec3(x_aux, y_aux - (0.0005), z_aux));
						normals.push_back(glm::vec3(standard_normal6));
								

						vertices.push_back(glm::vec3(x_aux, y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal7));

						vertices.push_back(glm::vec3(x_aux - (0.0005), y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal7));

						vertices.push_back(glm::vec3(x_aux, y_aux - (0.0005), z_aux));
						normals.push_back(glm::vec3(standard_normal7));
								

						vertices.push_back(glm::vec3(x_aux, y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal8));

						vertices.push_back(glm::vec3(x_aux - (0.0005), y_aux, z_aux));
						normals.push_back(glm::vec3(standard_normal8));

						vertices.push_back(glm::vec3(x_aux, y_aux - (0.0005), z_aux));
						normals.push_back(glm::vec3(standard_normal8));
						//}
				}
				aux_handler.close();
			}

			/*
			std::stringstream aux_handler;

			aux_handler << modelPath;
			glm::vec3 auxVert;
			aux_handler >> auxVert.x >> auxVert.y >> auxVert.z;
			//auxVert[0]*= 100;
			//auxVert[1]*= 100;
			//auxVert[2]*= 100;
			vertices.push_back(auxVert);

			printf("Point registered! %lf %lf %lf\n", vertices[0].x, vertices[0].y, vertices[0].z);
			*/

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
			// A geometric form - as of writting the current standard is a box (36 vertices)
			
			GLfloat *box = new GLfloat[36 * 3];
			std::memcpy(box, standard_box, sizeof(GLfloat) * 36 * 3);

			GLfloat *normal_box = new GLfloat[36 * 3];
			std::memcpy(box, standard_box_normals, sizeof(GLfloat) * 36 * 3);

			for(int i = 0; i < 36 * 3; i)
			{				
				glm::vec3 temp_vert, temp_normal;

				temp_vert.x = box[i];
				temp_normal.x = normal_box[i++];

				temp_vert.y = box[i];
				temp_normal.y = normal_box[i++];

				temp_vert.z = box[i];
				temp_normal.z = normal_box[i++];

				vertices.push_back(glm::vec3(temp_vert));
				normals.push_back(glm::vec3(temp_normal));
			}
			//printf("Geometric form registered! (Currently using standard box.)\n");
		}

		properties->vertexSize = vertices.size();
		//printf("Vertices size: %d\n", vertices.size());
		//printf("Normals size: %d\n", normals.size());

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