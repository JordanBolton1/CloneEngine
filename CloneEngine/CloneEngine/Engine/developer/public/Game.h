#pragma once

class GraphicsEngine;

class Game {
public:
	//create a game intsance or retyurn the one we already created
	static Game* GetGameInstance();

	//destroy the game instance
	static void DestroyGameInstance();

	//start/ run the application/ game loop
	void Run();

	//close the whole app
	void CloseGame();

private:
	Game();
	~Game();

	//when the app first loads we will initialise all the dependancies
	bool Initialise();

	//;isten and detect for input
	void ProcessInput();

	//handle the games logic
	void Update();

	//Render graphics to the screen
	void Draw();

	//uninitialise and delete all memory
	void CleanupGame();

private:
	bool bIsGameOver;

	//hold the graphics engine
	GraphicsEngine* Graphics;

};