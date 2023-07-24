#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include "application.h"

// screen height ve width için global constant
using namespace std;
float vertexData[] = {
	// first triangle positions
	 0.0f,    0.5f, 0.0f, 1.0f,
	 0.5f, -0.366f, 0.0f, 1.0f,
	-0.8f, -0.5f, 0.0f, 1.0f,

	//second triangle positions
	0.0f,    0.5f, 0.0f, 1.0f,
	 0.5f, 0.7f, 0.0f, 1.0f,
	-0.8f, 0.6f, 0.0f, 1.0f,

	//first triangle colors
	1.0f,    0.0f, 0.0f, 1.0f,
	 1.0f,    1.0f, 0.0f, 1.0f,
	 1.0f,    0.0f, 0.0f, 1.0f,
	
	 //second triangle colors
	 1.0f,    0.0f, 0.0f, 1.0f,
	 1.0f,    1.0f, 0.0f, 1.0f,
	 1.0f,    0.0f, 1.0f, 1.0f,
};

std::vector<Vertex> vertices = {
	//first triangle positions , colors
	{{-0.5f,-0.5f,0,1},{1.0f,0.0f,0.0f,1}},
	{{1.0f,-0.5f,0,1},{1.0f,1.0f,1.0f,1}},
	{{0.5f,0.3f,0,1},{0.0f,0.0f,1.0f,1}},
	//second triangle positions , colors
	{{-0.5f,-0.5f,0,1},{1.0f,0.0f,0.0f,1}},
	{{1.0f,-0.5f,0,1},{1.0f,1.0f,1.0f,1}},
	{{0.8f,0.3f,0,1},{1.0f,0.0f,1.0f,1}},
};

float positions[] = {
	-0.5f,-0.5f, 0, 1,
	0.5f,-0.5f, 0, 1,
	0.5f,0.5f, 0, 1,
	-0.5f,0.5f, 0, 1,

	1.0f,    0.0f, 0.0f, 1.0f,
	 1.0f,    1.0f, 0.0f, 1.0f,
	 1.0f,    1.0f, 0.0f, 1.0f,
	 1.0f,    0.0f, 0.0f, 1.0f,
};
unsigned int indices[] = { 0,1,2,2,3,0 };
std::vector<Vertex> vertices2 = {
	{{-0.5f,-0.5f,0,1},{1.0f,0.0f,0.0f,1}},
	{{0.5f,-0.5f,0,1},{1.0f,1.0f,1.0f,1}},
	{{0.5f,0.5f,0,1},{0.0f,0.0f,1.0f,1}},
	{{-0.7f,0.5f,0,1},{0.0f,0.0f,1.0f,1}},
};
vector<unsigned int> indices2 = { 0,1,2,2,3,0 };



float linePositions[] = {
	-0.5f,-0.5f, 0, 1,
	0.5f,0.5f, 0, 1,

	1.0f,    0.0f, 1.0f, 1.0f,
	 1.0f,    1.0f, 0.0f, 1.0f,
	
	 
};
const std::vector<Vertex> lineVertices = {
	{{-0.5f,-0.5f,0,1},{1.0f,0.0f,0.0f,1}},
	{{0.5f,0.5f,0,1},{1.0f,1.0f,1.0f,1}},
};


int main() {

	try {
		Application app;
		//OpenGl drawTriangle(floatArray, arraySize)
		//app.GLdrawTriangle(vertexData, sizeof(vertexData)/sizeof(float));
		
		//OpenGL drawRectangle
		//app.GLdrawRectangle(positions, indices, 32,6);
		
		//OpenGL drawLine
		//app.GLdrawLine(linePositions, sizeof(linePositions) / sizeof(float),5);

		//Vulkan drawTriangle(VertexArray, arraySize)
		//app.VKdrawTriangle(vertices, vertices.size());
		
		// Vulkan drawRectangle
		// app.VKdrawRectangle(vertices2, indices2, vertices2.size());
		
		// Vulkan drawLine
		//app.VKdrawLine(lineVertices, lineVertices.size(),5);
		

		float color[4] = { 1,0.5,0,1 };
		// Opengl drawCircle
		//app.GLdrawCircle(0, 0, 0.5f, color);
		
		// Vulkan drawCircle
		//app.VKdrawCircle(0, 0, 0.5, color);

		//OpenGL drawText
		std::string s = "This is a sample text.";
		//app.GLdrawText(s, s.size(),200,300,0.5, color);
		//Vulkan drawText

	}	
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}