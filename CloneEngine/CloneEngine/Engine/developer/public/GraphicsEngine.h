#pragma once

typedef void* SDL_GLContext;
struct SDL_Window;
class VertexArrayObject;

class GraphicsEngine {
public:
	GraphicsEngine();
	~GraphicsEngine();

	//initialise all of the required graphics libraries
	bool Initialise();

	//return the opengl renderer context
	SDL_GLContext GetRenderer();

	//return the sdl window
	SDL_Window* GetWindow() const;

	// this will clear the previous frame
	void ClearGraphics();
	//this will draew the new frame
	void DrawGraphics();
	// this will present the new frame to the renderer
	void PresentGraphics();

private:
	SDL_GLContext Renderer;
	SDL_Window* Window;

	//DEBUG VARIABLES
	VertexArrayObject* TriangleVAO;
	VertexArrayObject* PolygonVAO;

};