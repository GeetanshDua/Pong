#include<SDL.h>
#include<iostream>

//Window Size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//SDL Window  and Renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

struct Paddle {
	int x, y, w,  h;
	int velY;
};

struct Ball {
	int x, y, w, h;
	int velX, velY;
};

Paddle leftPaddle = {50, WINDOW_HEIGHT / 2 - 50, 15, 100, 15};
Paddle rightPaddle = { WINDOW_WIDTH - 65, WINDOW_HEIGHT / 2 - 50, 15, 100, 0 };
Ball ball = { WINDOW_WIDTH / 2 - 10, WINDOW_HEIGHT / 2 - 10, 20, 20, 5, 5 };

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

	return true;

}

void close() {
	//Destroy SDL Components
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void paddleBoundries() {
	
}

int main(int argc, char* argv[]) {
	if (!init()) {
		std::cerr << "Failed to initialize SDL2!" << std::endl;
		return false;
	}

	bool quit = false;
	SDL_Event event;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT) {
				quit = true;
			}

			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						leftPaddle.y -= leftPaddle.velY;
						break;
					case SDLK_DOWN:
						leftPaddle.y += leftPaddle.velY;
						break;
				}
			}
		}

		ball.x += ball.velX;
		ball.y += ball.velY;

		rightPaddle.y = ball.y;

		if (ball.y >= (WINDOW_HEIGHT - 23) || ball.y <= 0) {
			ball.velY = -ball.velY;
		}

		if (ball.x <= 0 || ball.x >= (WINDOW_WIDTH - 22)){
			ball.velX = -ball.velX;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		
		SDL_Rect leftRect = {leftPaddle.x, leftPaddle.y, leftPaddle.w, leftPaddle.h};
		SDL_Rect rightRect = { rightPaddle.x, rightPaddle.y, rightPaddle.w, rightPaddle.h };
		SDL_Rect ballRect = {ball.x, ball.y, ball.w, ball.h};

		SDL_RenderFillRect(renderer, &leftRect);
		SDL_RenderFillRect(renderer, &rightRect);
		SDL_RenderFillRect(renderer, &ballRect);

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}

	close();
	return 0;
}