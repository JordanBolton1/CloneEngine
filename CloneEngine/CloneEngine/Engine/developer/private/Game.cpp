#include "Game.h"
#include "CoreMinimal.h"
#include "GraphicsEngine.h"

Game* Game::GetGameInstance()
{
	//create a game instace the first time the function runs
	// after the first time since this is static the variable will remain constant
	static Game* GameInstance = new Game();

	return GameInstance;
}

void Game::DestroyGameInstance()
{
	delete GetGameInstance();
}

void Game::Run()
{
	//if initialise succeeds then game is not over
	bIsGameOver = !Initialise();

	//as long as the game is not over run the game loop
	while (!bIsGameOver) {
		
		ProcessInput();

		Update();

		Draw();

	}

	//once the game endss clean up any memory
	CleanupGame();
}

void Game::CloseGame()
{
	bIsGameOver = false;
	Graphics = nullptr;
}

Game::Game()
{

	bIsGameOver = false;

}

Game::~Game()
{
}

bool Game::Initialise()
{
	Graphics = new GraphicsEngine();
	if (!Graphics->Initialise()) {
		return false;
	}

	return true;
}

void Game::ProcessInput()
{
	//TODO process the input of the player
	
}

void Game::Update()
{
	//TODO process the logic of the game
}

void Game::Draw()
{
	// clears the previous frame
	Graphics->ClearGraphics();
	//draws the new frame
	Graphics->DrawGraphics();
	//presents the frame to the window
	Graphics->PresentGraphics();
}

void Game::CleanupGame()
{
	//destroy the graphics engine
	if (Graphics != nullptr) {
		delete Graphics;
	}
}
