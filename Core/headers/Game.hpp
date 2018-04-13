#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"

namespace Goop
{

	class Game
	{
	private:
		bool isRunning;

		void quit();
		void handleEvents();
		void render();

	public:
		void init();
		void run();

	protected:

		Window* window;


		virtual void conf();
		virtual void load();
		virtual void update();
		virtual void draw();
	};

}

#endif