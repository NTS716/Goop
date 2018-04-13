#include "../headers/Game.hpp"

namespace Goop
{

	void Game::init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			throw("SDL_Init Error:", SDL_GetError());
		}
		else {
			window = new Window();
			this->conf();
			try {
				window->create();
			}
			catch (...) {
				window->close();
				SDL_Quit();
			}

			isRunning = true;
		}
	}

	void Game::quit()
	{
		window->close();
		SDL_Quit();
	}

	void Game::handleEvents()
	{	
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			default:
				break;
			}
		}
	}

	void Game::run()
	{
		while (isRunning)
		{
			this->handleEvents();

			// Load Content
			this->load();

			// Update Game Logic
			this->update();

			// Draw Stuff
			this->render();
		}
		
		this->quit();
	}

	void Game::render()
	{
		window->clear();

		this->draw();

		window->display();
	}

	// Default Settings
	void Game::conf()
	{
		window->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		window->setSize(800, 600);
		window->setTitle("Goop");
		window->setColor(0, 255, 128);
	}

	void Game::load() {}
	void Game::update() {}
	void Game::draw() {}

}
