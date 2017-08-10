// Include standard hibraries
#include <cstdlib>
#include <cstdio>

// Include GLEW (OpenGL Extension Wrangler Library). 
// Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>

//Also, glew.h should be added before glfw3, as glfw3 documentation describes

// Include GLFW. To handle the window and the keyboard
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

//#include <GL/glut.h>
#include <cstring>
#include <string>
#include "Entities/Entity.hpp"

//---------------------------------------------------------------------------------------
bool loadOBJ(const char *path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(path, "r");
	if( file == NULL ){
	    printf("Impossible to open the file !\n");
	    return false;
	}
	
	while( 1 ){
	    char lineHeader[128];
	    // read the first word of the line
	    int res = fscanf(file, "%s", lineHeader);
	    if (res == EOF)
	        break; // EOF = End Of File. Quit the loop.

	    else{
	    	if ( strcmp( lineHeader, "v" ) == 0 ){
			    glm::vec3 vertex;
			    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			    temp_vertices.push_back(vertex);
			}
			else if ( strcmp( lineHeader, "vt" ) == 0 ){
			    glm::vec2 uv;
			    fscanf(file, "%f %f\n", &uv.x, &uv.y );
			    temp_uvs.push_back(uv);
			}
			else if ( strcmp( lineHeader, "vn" ) == 0 ){
			    glm::vec3 normal;
			    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			    temp_normals.push_back(normal);
			}
			else if ( strcmp( lineHeader, "f" ) == 0 ){
			    std::string vertex1, vertex2, vertex3;
			    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			    if (matches != 9){
			        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
			        return false;
			    }
			    vertexIndices.push_back(vertexIndex[0]);
			    vertexIndices.push_back(vertexIndex[1]);
			    vertexIndices.push_back(vertexIndex[2]);
			    uvIndices    .push_back(uvIndex[0]);
			    uvIndices    .push_back(uvIndex[1]);
			    uvIndices    .push_back(uvIndex[2]);
			    normalIndices.push_back(normalIndex[0]);
			    normalIndices.push_back(normalIndex[1]);
			    normalIndices.push_back(normalIndex[2]);
			}
		}
    }
    //Indexing
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
    	unsigned int vertexIndex = vertexIndices[i];
    	glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
    	out_vertices.push_back(vertex);
    }
}


//---------------------------------------------------------------------------------------

//class Kagami {	
//};

int main(){
	printf("Hello, World!\n");

	Entity ent;
	ent.hello();	

	//	Opening an .obj  ------------------------------------------------------------

	std::string path = "sportsCar.obj";

	//bool res = loadOBJ(path.c_str(), vertices, uvs, normals);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// Load it into a VBO ---------------------------------------------------------------------
	/*GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}*/
	//---------------------------------------------------------------------

	return 0;
}
/*
class Object{
	virtual Object() {};
	virtual ~Object() {};
	virtual int id;
};

class Visible : public virtual Object{

};

class Car : public Visible{

};
*/