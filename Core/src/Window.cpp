#include "../headers/Window.hpp"

//Window::Window() {};

namespace Goop
{

	void Window::create()
	{
		if (x == NULL)
			x = SDL_WINDOWPOS_CENTERED;
		if (y == NULL)
			y = SDL_WINDOWPOS_CENTERED;
		nested_window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
		if (nested_window == nullptr) {
			throw("SDL_CreateWindowError:", SDL_GetError());
		}
		else {
			nested_renderer = SDL_CreateRenderer(nested_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (nested_renderer == nullptr) {
				throw("SDL_CreateRendererError:", SDL_GetError());
			}
		}
	}

	void Window::close()
	{
		SDL_DestroyRenderer(nested_renderer);
		SDL_DestroyWindow(nested_window);
	}

	void Window::setPosition(int x_arg, int y_arg)
	{
		x = x_arg;
		y = y_arg;

		if (nested_window != nullptr)
			SDL_SetWindowPosition(nested_window, x, y);
	}

	void Window::setSize(int width_arg, int height_arg)
	{
		width = width_arg;
		height = height_arg;

		if (nested_window != nullptr)
			SDL_SetWindowSize(nested_window, width_arg, height_arg);
	}

	void Window::setColor(unsigned char r_arg, unsigned char g_arg, unsigned char b_arg)
	{
		color[0] = r_arg;
		color[1] = g_arg;
		color[2] = b_arg;
	}

	void Window::setTitle(const char* title_arg)
	{
		title = title_arg;

		if (nested_window != nullptr)
			SDL_SetWindowTitle(nested_window, title_arg);
	}

	void Window::clear()
	{
		SDL_SetRenderDrawColor(nested_renderer, color[0], color[1], color[2], 255);
		SDL_RenderClear(nested_renderer);
	}

	void Window::display()
	{
		SDL_RenderPresent(nested_renderer);
	}

}