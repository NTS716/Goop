#if defined(_WIN32)
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#ifndef WINDOW_HPP
#define WINDOW_HPP


namespace Goop
{

	class Window
	{
	private:
		int x, y;
		int width, height;
		unsigned char color[3]; // only 3 this time, Windows don't have alpha
		const char* title;

		bool isFullscreen, isBorderless, isMouseVisible, isVsyncEnabled;

		SDL_Renderer* nested_renderer;


	public:
		SDL_Window * nested_window;
		//Window();
		void create();
		//Window(int width_arg, int height_arg, const char* title_arg);

		void close();

		void clear(); // clear the screen
		void display(); // display changes

		// Setters
		void setPosition(int x_arg, int y_arg);
		void setSize(int width_arg, int height_arg);
		void setColor(unsigned char r_arg, unsigned char g_arg, unsigned char b_arg); // values range from 0 - 255
		void setTitle(const char* title_arg);

		void setFullscreen(bool value_arg);
		void setBorderless(bool value_arg);
		void setMouseVisible(bool value_arg);
		void setVsyncEnabled(bool value_arg);

		// Getters
		int getX() { return x; }
		int getY() { return y; }
		int getWidth() { return width; }
		int getHeight() { return height; }

		//bool* getFlags();
	};
}

#endif
