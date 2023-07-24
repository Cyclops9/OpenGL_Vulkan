#pragma once
#include <vector>
#include "OpenGL.h"
#include "Vulkan.h"
class Application {
private:
public:
	Application() {
	}
	~Application() {};
	void GLdrawTriangle(float vertices[], unsigned int size)
	{
		OpenGL program;
		program.drawTriangle(vertices,size);
		
	}
	void VKdrawTriangle(vector<Vertex> vertices, unsigned int size)
	{
		Vulkan program;
		program.drawTriangle(vertices, size);
		
	}

	void GLdrawRectangle(float vertices[], unsigned int indices[],unsigned int size, unsigned int sizeOfIndices)
	{
		OpenGL program;
		program.drawRectangle(vertices, indices, size, sizeOfIndices);
	}

	void VKdrawRectangle(vector<Vertex> vertices, vector<unsigned int> indices,unsigned int size)
	{
		Vulkan program;
		program.drawRectangle(vertices, indices, size);
	}

	void GLdrawLine(float vertices[], unsigned int size, unsigned int width)
	{
		OpenGL program;
		program.drawLine(vertices, size,width);
	}
	
	void VKdrawLine(vector<Vertex> vertices, unsigned int size,float width)
	{
		Vulkan program;
		program.drawLine(vertices, size,width);
	}

	void GLdrawText(const char* text)
	{
		OpenGL program;
		program.drawText(text);
	}

	void GLdrawCircle(float xPos, float yPos, float radius, float* color)
	{
		for (int i = 0; i < 4; i++)
		{
			if (color[i] > 1 || color[i] < 0)
			{
				throw std::runtime_error("Color values should be between 1 and 0.");
			}
		}
		OpenGL program;
		program.drawCircle(xPos, yPos, radius, color);
	}

	void VKdrawCircle(float xPos, float yPos, float radius, float* color)
	{
		Vulkan program;
		program.drawCircle(0, 0, 0.5, color);
	}

	void GLdrawText(std::string text, unsigned int length, float xPos, float yPos, float scale,float* color)
	{
		OpenGL program;
		program.drawText(text, length, xPos, yPos,scale,color);
	}
};

