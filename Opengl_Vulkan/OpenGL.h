#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>
#include<string>
#include <unordered_map>
#include <math.h>
#include <GL/freeglut.h>
#include<map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include FT_FREETYPE_H
#include <fstream>
#include <sstream>
#include <iostream>

constexpr auto PI = 3.1415926;
using namespace std;
string vs =
"#version 330 core\n"
"\n"
"layout(location = 0) in vec4 position;\n"
"layout (location = 1) in vec4 color;"
"smooth out vec4 theColor;"
"\n"
"void main()\n"
"{\n"
"	gl_Position = position;"
"	theColor = color;"
"}\n";
string fs =
"#version 330 core\n"
"\n"
" in vec4 theColor;"
"out vec4 outputColor;"
"\n"
"void main()\n"
"{\n"
"	outputColor = theColor;\n"
"}\n";


class Shader
{
public:
	unsigned int ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// activate the shader
	// ------------------------------------------------------------------------
	void use()
	{
		glUseProgram(ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec4 color);

// settings


/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
unsigned int VAO, VBO;


void Circle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);
class OpenGL {
	
public:
	OpenGL();
	~OpenGL();
	void drawTriangle(float[], unsigned int);
	void drawRectangle(float[], unsigned int[], unsigned int, unsigned int);
	void drawLine(float[], unsigned int, float);
	void drawText(const char*){}
	void drawCircle(float xPos, float yPos, float radius, float* color);
	void drawText(std::string, unsigned int length, float xPos, float yPos, float scale,float* color);
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
};

OpenGL::OpenGL() {

}
OpenGL::~OpenGL() {

}

void OpenGL::drawTriangle(float vertices[], unsigned int size) {
	
	glfwInit();
	GLFWwindow* window;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	const char* vs1 = vs.c_str();
	const char* fs1 = fs.c_str();

	unsigned int vsid = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fsid = glCreateShader(GL_FRAGMENT_SHADER);
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glShaderSource(vsid, 1, &vs1, nullptr);
	glCompileShader(vsid);
	glShaderSource(fsid, 1, &fs1, nullptr);
	glCompileShader(fsid);


	unsigned int program = glCreateProgram();
	glAttachShader(program, vsid);
	glAttachShader(program, fsid);
	glLinkProgram(program);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(size*sizeof(float)/2));
	


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glUseProgram(program);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, size / 8);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
}


void OpenGL::drawRectangle(float vertices[], unsigned int indices[], unsigned int size, unsigned int sizeOfIndices)
{
	int newSize = (size / 2 - 4) * 4;
	float *positions = new float[newSize];
	unsigned int indices2[] = { 0,1,2,2,3,0 };

	unordered_map<unsigned int, float*> mp;
	for (int i = 0; i < sizeOfIndices; i++)
	{
		if (!mp.count(indices[i]))
		{
			float* temp = new float[4];
			temp[0] =  vertices[size / 2 + indices[i] * 4];
			temp[1] =  vertices[size / 2 + indices[i] * 4 + 1];
			temp[2] =  vertices[size / 2 + indices[i] *  4 + 2];
			temp[3] =  vertices[size / 2 + indices[i] *   4+ 3];
			mp[indices[i]] = temp;
		}
		else {
			continue;
		}
	}
	int x = 0;
	for (int i = 0; i < sizeOfIndices; i++)
	{
		positions[x] =	   vertices[indices[i] * 4]; x++;
		positions[x] = vertices[indices[i] * 4 + 1]; x++;
		positions[x] = vertices[indices[i] * 4 + 2]; x++;
		positions[x] = vertices[indices[i] * 4 + 3]; x++;
	}

	for (int i = 0; i < sizeOfIndices; i++)
	{
		positions[x] =     vertices[size / 2 + indices[i] * 4]; x++;
		positions[x] = vertices[size / 2 + indices[i] * 4 + 1]; x++;
		positions[x] = vertices[size / 2 + indices[i] * 4 + 2]; x++;
		positions[x] = vertices[size / 2 + indices[i] * 4 + 3]; x++;
	}

	glfwInit();
	GLFWwindow* window;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	const char* vs1 = vs.c_str();
	const char* fs1 = fs.c_str();

	unsigned int vsid = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fsid = glCreateShader(GL_FRAGMENT_SHADER);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glShaderSource(vsid, 1, &vs1, nullptr);
	glCompileShader(vsid);
	glShaderSource(fsid, 1, &fs1, nullptr);
	glCompileShader(fsid);


	unsigned int program = glCreateProgram();
	glAttachShader(program, vsid);
	glAttachShader(program, fsid);
	glLinkProgram(program);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * newSize, positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(6 * 4 * 4));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glUseProgram(program);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, newSize / 8);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
}


void OpenGL::drawLine(float vertices[], unsigned int size, float lineWidth) {

	glfwInit();
	GLFWwindow* window;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	const char* vs1 = vs.c_str();
	const char* fs1 = fs.c_str();

	unsigned int vsid = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fsid = glCreateShader(GL_FRAGMENT_SHADER);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glShaderSource(vsid, 1, &vs1, nullptr);
	glCompileShader(vsid);
	glShaderSource(fsid, 1, &fs1, nullptr);
	glCompileShader(fsid);


	unsigned int program = glCreateProgram();
	glAttachShader(program, vsid);
	glAttachShader(program, fsid);
	glLinkProgram(program);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(size * sizeof(float) / 2));



	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glUseProgram(program);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(lineWidth);
		glDrawArrays(GL_LINES, 0, size / 8);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
}

//void OpenGL::drawCircle(float xPos, float yPos, float radius, float* color)
//{
//	glfwInit();
//	GLFWwindow* window;
//	window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
//	glfwMakeContextCurrent(window);
//	glewInit();
//	
//	const int steps = 500;
//	const float angle = PI * 2.0f / steps;
//
//	while(!glfwWindowShouldClose(window)) {
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		float prevX = xPos;
//		float prevY = yPos - radius;
//		for (int i = 0; i <= steps; i++)
//		{
//			float newX = radius * sin(angle * i);
//			float newY = -radius * cos(angle * i);
//			
//			glBegin(GL_TRIANGLE_FAN);
//			glColor4f(color[0], color[1], color[2],color[3]);
//			glVertex3f(0.0f, 0.0f, 0.0f);
//			glVertex3f(prevX, prevY, 0);
//			glVertex3f(newX, newY, 0);
//			glEnd();
//
//			prevX = newX;
//			prevY = newY;
//		}
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	}
//	glfwTerminate();
//}

void OpenGL::drawCircle(float xPos, float yPos, float radius, float* color)
{
	GLFWwindow* window;

	// Initialize the library
	glfwInit();

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);


	// Make the window's context current
	glfwMakeContextCurrent(window);
	

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// render OpenGL here
		glColor4f(color[0], color[1], color[2], color[3]);
		Circle(xPos, yPos, 0, radius, 50);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
}


void Circle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides)
{
	int numberOfVertices = numberOfSides + 2;

	GLfloat twicePi = 2.0f * 3.1415;

	GLfloat* circleVerticesX = new GLfloat[300];
	GLfloat* circleVerticesY = new GLfloat[300];
	GLfloat* circleVerticesZ = new GLfloat[300];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
		circleVerticesZ[i] = z;
	}

	GLfloat* allCircleVertices = new GLfloat[(300) * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);
}



void OpenGL::drawText(std::string text, unsigned int length, float x, float y, float scale,float* color)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	glewInit();

	// OpenGL state
	// ------------
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// compile and setup the shader
	// ----------------------------
	Shader shader("res/ShadersGL/text.vs", "res/ShadersGL/text.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// FreeType
	// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		
	}

	// find path to font
	std::string font_name = "fonts/arial.ttf";
	if (font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;

	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderText(shader, text, x, y, scale, glm::vec4(color[0], color[1], color[2],color[3]));


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// render line of text
// -------------------
void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec4 color)
{
	// activate corresponding render state	
	shader.use();
	glUniform4f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z,color.w);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
