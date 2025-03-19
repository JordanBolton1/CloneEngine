#pragma once
#include "CoreMinimal.h"

struct ShapeMatrices {

	ShapeMatrices(TArray<float> positions, TArray<CEUint> indices) : Positions(positions), Indices(indices) {}

	TArray<float> Positions;
	TArray<CEUint> Indices;
};

namespace cesm {
	static const ShapeMatrices Triangle(
		{
			//x		//y		//z
			0.0f,	0.5f,	0.0f, // 0 - top of the triangle
		   -0.5f,  -0.5f,	0.0f, // 1 - bottom left
			0.5f,  -0.5f,	0.0f  // 2 - bottom right 
		},
		{
			0, 1, 2  // triangle 1
		}
	);

	static const ShapeMatrices Polygon(
		{
			//x		//y		//z
		   -0.5f,	0.5f,	0.0f, // 0 - top left
		    0.5f,	0.5f,	0.0f, // 1 - top right
		   -0.5f,  -0.5f,	0.0f, // 2 - bottom left
			0.5f,  -0.5f,	0.0f  // 3 - bottom right 
		},
		{
			0, 1, 2, // triangle 1
			1, 2, 3  // triangle 2
		}
		);

}

