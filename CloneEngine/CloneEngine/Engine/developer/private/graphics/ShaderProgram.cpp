#include "graphics/ShaderProgram.h"
#include "../../dependencies/includes/glew/glew.h"
// give us the ability to convert text file to a string
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram()
	: ProgramID(0)
{
}

ShaderProgram::~ShaderProgram()
{
}

bool ShaderProgram::LoadShaders(const TArray<CEShaderInfo>& Shaders)
{
	//generate an ID for the program
	ProgramID = glCreateProgram();

	// (singular versions of the array item : the array itself)
	// will run for the amount of items in th array
	for (const CEShaderInfo& Shader : Shaders) {
		CEUint ShaderID = CreateShader(Shader.ShaderType, Shader.FilePath);
	}

	return true;
}

void ShaderProgram::Run() const
{
}

CEUint ShaderProgram::CreateShader(CEShaderTypes ShaderType, const CEString& FilePath)
{
	CEString ShaderCode = ConvertShaderFile(FilePath);

	//make sure the file exists
	if (ShaderCode.empty()) {
		CE_MSG_ERR("ShaderProgram", "Failed to read shader file: " << FilePath);
		return 0;
	}

	//find the sdhader type aand get the correct oopengl enum value
	GLenum GLShaderType = GL_INVALID_ENUM;
	switch (ShaderType){
	case VERTEX:
		GLShaderType = GL_VERTEX_SHADER;
		break;
	case FRAGMENT:
		GLShaderType = GL_FRAGMENT_SHADER;
		break;
	default:
		GLShaderType = GL_INVALID_ENUM;
		break;
	}

	//create the relevant shader because theres a fragment and a vertex shader
	//generate the shader ID based on the type of shader(Fragment array and Vertex array)
	CEUint ShaderID = glCreateShader(GLShaderType);

	//convert code into const char* format so glew can readd the text
	const char* ShaderCodeChar = ShaderCode.c_str();

	//creating the opengl version of shader code
	glShaderSource(ShaderID, 1, &ShaderCodeChar, nullptr);
	
	//compile the shader and error if anything is wrong
	//compilling basically means to check for problems
	glCompileShader(ShaderID);

	//error handle any issues with the compile
	int CompileStatus = 0;
	//update our local variable with the compile status
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &CompileStatus);

	//if the compile failed it will return GL_FAlSE
	if (CompileStatus == GL_FALSE) {
		//get the length of the compile error
		//how many characters are in the error
		int InfoLogLength = 0;
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		//create an empty string with the size of the log length
		CEString CompilerMsg(InfoLogLength, ' ');
		//get the message and add it into the above variable
		glGetShaderInfoLog(ShaderID, InfoLogLength, nullptr, &CompilerMsg[0]);

		CE_MSG_ERR("ShaderProgram", "Shader compilation message: \n" << CompilerMsg);
		glDeleteShader(ShaderID);

		return 0;
	}

	return ShaderID;
}

CEString ShaderProgram::ConvertShaderFile(const CEString FilePath)
{
	//ifstream type stores file paths  as actual paths
	std::ifstream ShaderFile(FilePath);

	std::stringstream ShaderStream;
	// read the file in file path and add the text inside the file into a string
	ShaderStream << ShaderFile.rdbuf();

	//convert into a c++ string
	CEString ReadableString(ShaderStream.str());

	return CEString();
}
