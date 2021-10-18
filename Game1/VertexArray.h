#pragma once

#include "glew.h"

class VertexArray
{
public:
	VertexArray(const float * const vertex, unsigned int numOfVertices, const unsigned int * const index, unsigned int numOfIndices);
	~VertexArray();

	void Active();


	//Get
	unsigned int NumOfVertices()const { return mNumOfVertices; }
	unsigned int NumOfIndices()const { return mNumOfIndices; }

private:
	//ID
	GLuint mVertexArrayId;
	GLuint mVertexBufferId;
	GLuint mIndexBufferId;

	//Sizes of buffers
	unsigned int mNumOfVertices;
	unsigned int mNumOfIndices;


};

