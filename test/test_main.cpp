#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_mixer.h>
#undef main

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Joystick* gamepad;
SDL_Haptic* gamepadHaptic;

SDL_Rect myRect;
SDL_Rect myRect2;

int linex1, linex2, liney1, liney2;

bool running;

void draw_circle(SDL_Point center, int radius, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int w = 0; w < radius * 2; w+=1)
	{
		for (int h = 0; h < radius * 2 ; h+=1)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx*dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawLine(renderer, center.x + dx, center.y + dy, center.x + dx + 100, center.y + dy + 100);
			}
		}
	}
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	running = true;

	if (SDL_NumJoysticks() < 1)
	{
		std::cout << "No Joysticks Detected." << std::endl;
	}
	else
	{
		gamepad = SDL_JoystickOpen(0);
	}

	gamepadHaptic = SDL_HapticOpenFromJoystick(gamepad);

	if (gamepadHaptic == NULL) {
		std::cout << "error initalizing haptic pad" << std::endl;
	}

	SDL_HapticRumbleInit(gamepadHaptic);

	myRect.x = 100; myRect.y = 100;
	myRect.w = 30; myRect.h = 30;

	myRect2.x = 200; myRect2.y = 100;
	myRect2.w = 30; myRect2.h = 30;

	// audio

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) > 0)
		std::cout << "Audio Error" << std::endl;

	Mix_Music* music = Mix_LoadMUS("music.mp3");
	Mix_Chunk* effect = Mix_LoadWAV("snare.wav");
	Mix_Chunk* tom = Mix_LoadWAV("tom.wav");
	Mix_Chunk* kick = Mix_LoadWAV("kick.wav");

	// cricle
	bool drawPoint = false;

	while (running)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
					break;

				case SDL_KEYDOWN:

					if (event.key.keysym.sym == SDLK_5)
						drawPoint = true;
					break;

				default:
					break;
			}
		}

		if (SDL_JoystickGetButton(gamepad, 0)) {
			if (SDL_HapticRumblePlay(gamepadHaptic, 10, 50) != 0)
			{
				std::cout << "Error playing rumble" << std::endl;
			}

		}
		else if (SDL_JoystickGetButton(gamepad, 1))
		{
			if (!Mix_PlayingMusic())
			{
				Mix_PlayMusic(music, 1);
			}
			else if (Mix_PausedMusic())
			{
				Mix_ResumeMusic();
			}
			else
			{
				Mix_PauseMusic();
			}
		}

		else if (SDL_JoystickGetButton(gamepad, 2))
		{
			Mix_HaltMusic();
		}

		else if (SDL_JoystickGetButton(gamepad, 3))
		{
			Mix_PlayChannel(-1, effect, 0);
		}

		else if (SDL_JoystickGetButton(gamepad, 5))
		{
			Mix_PlayChannel(-1, tom, 0);
		}

		else if (SDL_JoystickGetButton(gamepad, 4))
		{
			Mix_PlayChannel(-1, kick, 0);
		}


		if (std::abs(SDL_JoystickGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTX)) > 5000)
			myRect.x += (SDL_JoystickGetAxis(gamepad, 0) / 3000);
		if (std::abs(SDL_JoystickGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTY)) > 5000)
			myRect.y += (SDL_JoystickGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTY) / 3000);

		if (std::abs(SDL_JoystickGetAxis(gamepad, 3)) > 5000)
			myRect2.x += (SDL_JoystickGetAxis(gamepad, 3) / 3000);
		if (std::abs(SDL_JoystickGetAxis(gamepad, 4)) > 5000)
			myRect2.y += (SDL_JoystickGetAxis(gamepad, 4) / 3000);

		///

		linex1 = myRect.x + 15;
		liney1 = myRect.y + 15;
		linex2 = myRect2.x + 15;
		liney2 = myRect2.y + 15;

		///


		SDL_SetRenderDrawColor(renderer, 0, 255, 128, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer, linex1, liney1, linex2, liney2);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &myRect);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &myRect2);

		if (drawPoint) {
			draw_circle({ 300, 300 }, 100, { 255,0,255,255 });
		}

		SDL_RenderPresent(renderer);
	}

	Mix_FreeChunk(kick);
	Mix_FreeChunk(tom);
	Mix_FreeChunk(effect);
	Mix_FreeMusic(music);
	SDL_HapticClose(gamepadHaptic);
	SDL_JoystickClose(gamepad);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}