#include "Game.h"

__GLOBAL_STATIC_VAR

Game::Game(HINSTANCE* hInstance = nullptr) : QUAD(hInstance) {
}

Game::~Game(){
}
void Game::run(){
	QUAD::exec();
}

