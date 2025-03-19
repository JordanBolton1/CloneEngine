#pragma once
#include "CoreMinimal.h"

enum CEShaderTypes : CEUint {
	VERTEX = 0,
	FRAGMENT
};

struct CEShaderInfo {
	CEShaderInfo(CEShaderTypes InType, CEString InPath) 
		: ShaderType(InType), FilePath(InPath) {}

	CEShaderTypes ShaderType;
	CEString FilePath;
};

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	// initialise the shader files
	bool LoadShaders( const TArray<CEShaderInfo>& Shaders);

	//activate the shader as the current shader program for opengl
	void Run() const;

	//returns the opengl ID for the shader
	CEUint GetID() const { return ProgramID; }

private:
	//creeates the individual shaders based on thier type
	// vertex and frag shadders will be assigned separatly
	// returns 0 when it fails
	CEUint CreateShader(CEShaderTypes ShaderType, const CEString& FilePath);

	//read the GLSL  format and convert it into a string for opengl
	CEString ConvertShaderFile(const CEString FilePath);

private:
	CEUint ProgramID;
	TArray<CEUint> ShaderIDs;
	 	
};