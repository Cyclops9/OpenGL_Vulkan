#pragma once
#include <vector>
#include "OpenGL.h"
#include "Vulkan.h"

OpenGL GLprogram;
Vulkan VKprogram;

class Application {
private:	
public:
	Application(unsigned int ScreenWidth, unsigned int ScreenHeight ) {
		GLprogram.SCR_HEIGHT = ScreenHeight;
		GLprogram.SCR_WIDTH = ScreenWidth;
		VKprogram.height = ScreenHeight;
		VKprogram.width = ScreenWidth;
	}
	~Application() {};
	void GLdrawTriangle(float vertices[], unsigned int size)
	{
		if (size % 3 != 0)
			throw std::runtime_error("Invalid vertex data. Size must be dividable by 3!");
		GLprogram.drawTriangle(vertices,size);
	}
	void VKdrawTriangle(vector<Vertex> vertices, unsigned int size)
	{
		if (size % 3 != 0)
			throw std::runtime_error("Invalid vertex data. Size must be dividable by 3!");
		VKprogram.drawTriangle(vertices, size);
	}

	void GLdrawRectangle(float vertices[], unsigned int indices[],unsigned int size, unsigned int sizeOfIndices)
	{
		if (size % 4 != 0)
			throw std::runtime_error("Invalid vertex data. Size must be dividable by 4!");
		else if (sizeOfIndices % 6 != 0)
			throw std::runtime_error("Invalid indices size!");
		GLprogram.drawRectangle(vertices, indices, size, sizeOfIndices);
	}

	void VKdrawRectangle(vector<Vertex> vertices, vector<unsigned int> indices,unsigned int size)
	{
		if (size % 4 != 0)
			throw std::runtime_error("Invalid vertex data. Size must be dividable by 4!");
		else if (indices.size() % 6 != 0)
			throw std::runtime_error("Invalid indices size!");
		VKprogram.drawRectangle(vertices, indices, size);
	}

	void GLdrawLine(float vertices[], unsigned int size, float width)
	{
		if (size % 2 != 0)
			throw std::runtime_error("Invalid line vertex data.");
		GLprogram.drawLine(vertices, size,width);
	}
	
	void VKdrawLine(vector<Vertex> vertices, unsigned int size,float width)
	{
		if (size % 2 != 0)
			throw std::runtime_error("Invalid line vertex data.");
		VKprogram.drawLine(vertices, size,width);
	}

	void GLdrawText(const char* text)
	{
		GLprogram.drawText(text);
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
		GLprogram.drawCircle(xPos, yPos, radius, color);
	}

	void VKdrawCircle(float xPos, float yPos, float radius, float* color)
	{
		VKprogram.drawCircle(0, 0, 0.5, color);
	}

	void GLdrawText(std::string text, unsigned int length, float xPos, float yPos, float scale,float* color)
	{
		GLprogram.drawText(text, length, xPos, yPos,scale,color);
	}
};

