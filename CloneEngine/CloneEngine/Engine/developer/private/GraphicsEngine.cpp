#include "GraphicsEngine.h"
#include "../../dependencies/includes/SDL2/SDL.h"
#include "../../dependencies/includes/glew/glew.h"
#include "CoreMinimal.h"

//DEBUG VARIABLES
#include "graphics/VertexArrayObject.h"
#include "graphics/ShapeMatrices.h"

GraphicsEngine::GraphicsEngine()
{
	Window = nullptr;
	Renderer = nullptr;
}

GraphicsEngine::~GraphicsEngine()
{
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Renderer);
}

bool GraphicsEngine::Initialise()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		CE_MSG_ERR("Graphics Engine", "SDL failed to initialise: " << SDL_GetError());
		return false;
	}

	//set up opengl for sdl2
	//setting the required attributes for opengl
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);// major version of open gl to use v4
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);// minor version of open gl to use v4.6
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);// allow sdl to use the latest version
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);// transparency
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	//create the sdl flags for the window
	Uint32 WindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	Window = SDL_CreateWindow(
		"Clone Engine | An OpenGL Engine ",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		940,
		480,
		WindowFlags
		);

	//if the window wasnt successfully created then fail
	if (Window == nullptr) {
		CE_MSG_ERR("Graphics Engine", "SDL failed to create window: " << SDL_GetError());
		SDL_Quit();
		return false;
	}

	//create the open gl renderer
	Renderer = SDL_GL_CreateContext(Window);

	// if the renderer failed to create then fail
	if (Renderer == nullptr) {
		CE_MSG_ERR("Graphics Engine", "SDL failed to create opengl context: " << SDL_GetError());
		SDL_DestroyWindow(Window);
		SDL_Quit();
		return false;
	}

	// activates the experimental libraries in glew (which seems to be all of them?)
	glewExperimental = GL_TRUE;

	//initialise gelw and fial if it doesnt succeed
	if (glewInit() != GLEW_OK) {
		CE_MSG_ERR("Graphics Engine", "GLEW failed to initialise: " << glewGetErrorString(glewInit()));
		SDL_GL_DeleteContext(Renderer);
		SDL_DestroyWindow(Window);
		SDL_Quit();
		return false;
	}

	return true;
}

SDL_GLContext GraphicsEngine::GetRenderer()
{
	return Renderer;
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return Window;
}

void GraphicsEngine::ClearGraphics()
{
	//set the background clour when there are no objects over it
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::DrawGraphics()
{
	//TODO draw 3d objects to the screen
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// creating the vao
	TArray<CEVertex> Vertices = CEVertex::ConvertShapeMatrix(cesm::Triangle);
	
	if (TriangleVAO == nullptr) {
		CE_MSG_LOG("GE", "Triangle");
		TArray<CEVertex> Vertices = CEVertex::ConvertShapeMatrix(cesm::Triangle);

		TriangleVAO = new VertexArrayObject (Vertices, cesm::Triangle.Indices);
	}

	if (PolygonVAO == nullptr) {
		CE_MSG_LOG("GE", "Polygon");
		Vertices = CEVertex::ConvertShapeMatrix(cesm::Polygon);
		
		PolygonVAO = new VertexArrayObject(Vertices, cesm::Polygon.Indices);
	}

	//drawing the vao to the screen
	if (TriangleVAO != nullptr) {
		TriangleVAO->Draw();
	}

	if (PolygonVAO != nullptr) {
		PolygonVAO->Draw();
	}
}

void GraphicsEngine::PresentGraphics()
{
	// present the open gl renderer to the window
	SDL_GL_SwapWindow(Window);
}
