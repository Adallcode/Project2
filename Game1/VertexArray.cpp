#include "VertexArray.h"

#include "glew.h"


VertexArray::VertexArray(const float * const vertex, unsigned int numOfVertices, const unsigned int * const index,
	unsigned int numOfIndices)
	: mNumOfVertices(numOfVertices),
	  mNumOfIndices(numOfIndices)
{
	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);

	//Vertex
	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, mNumOfVertices * sizeof(float) * 8, vertex, GL_STATIC_DRAW);

	//Indice
	glGenBuffers(1, &mIndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumOfIndices * sizeof(unsigned int), index, GL_STATIC_DRAW);


	//Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	
	//Normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<const void*>(sizeof(float) * 3));

	//Texture attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<const void*>(sizeof(float) * 6));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mIndexBufferId);
	glDeleteBuffers(1, &mVertexBufferId);
	glDeleteVertexArrays(1, &mVertexArrayId);

}

void VertexArray::Active()
{
	glBindVertexArray(mVertexArrayId);
}
