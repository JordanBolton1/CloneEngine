#pragma once
#include "CoreMinimal.h"
#include "../../dependencies/includes/glm/glm.hpp"

struct ShapeMatrices;

struct CEVertex {

	//we sign a position to the class vareiable on the initialisation
	CEVertex(glm::vec3 inposition) : position(inposition){}

	glm::vec3 position; //x ,y, z position in the world space of the vertex

	static TArray<CEVertex> ConvertShapeMatrix(ShapeMatrices Shape);
};

class VertexArrayObject {
public:
	VertexArrayObject(const TArray<CEVertex>& vertexData, const TArray<CEUint>& indexData);
	~VertexArrayObject();

	// save the vertex data into a format that id readable by opengl shaders, that format is called an attribute pointer
	// @param 1 - index to assign this attribute pointer in the open gl attribute pointer array
	// @param 2 - how many numbers in this pointer [eg. 3 for a vertex position]
	// @param 3 - the data type that will be read for these numbers [eg. flaot, int , ect..]
	// @param 4 - siz of each row of number in bits [eg. sizeof(datatype)* numbers in each row]
	// @param 5 - amount of number to skip to get t0o the row that is in the vertex matrix [eg. (void*)(sizeof(datatype)* number of elements)]
	void SetAttributePointer(CEUint index, CEUint size, CEUint type, int stride, const void* pointer);

	//activate this VAO in opengl
	void Bind();

	//deactivate this VAO
	void Unbind();

	//set up the IDs for this VAO
	void GenerateAndSetBuffers();

	//run every frame to draw it to the screen
	void Draw();

private:
	TArray<CEVertex> VertexData;
	TArray<CEUint> IndexData;

	//VAO ID - vertex matrix ID - Index matrix ID
	CEUint VaoID, VboID, EabID;
 };