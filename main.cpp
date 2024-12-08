#include<SDL.h>
#include<iostream>

//Window Size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//SDL Window  and Renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL2 could not initialized! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Created the Window
	window = SDL_CreateWindow(
		"PONG",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (!window) {
		std::cerr << "SDL_Window could not Created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Created the Renderer
	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	if (!renderer) {
		std::cerr << "Renderer could not be Created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	return true;

}

void close() {
	//Destroy SDL Components
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	if (!init()) {
		std::cerr << "Failed to initialize SDL2!" << std::endl;
		return false;
	}

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_RenderClear(renderer);



		SDL_RenderPresent(renderer);
	}

	close();
	return 0;
}