// SDL and standard IO
#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Start up SDL and create window
bool init();

// Load media
bool loadMedia();

// Free media and shut down SDL
void close();

// Window we'll render to
SDL_Window* gWindow = NULL;

// Window surface
SDL_Surface* gScreenSurface = NULL;

// Image loaded and displayed on the screen
SDL_Surface* gXOut = NULL;

bool init() {
	// Init flag
	bool success = true;

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not init! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Create window
		gWindow = SDL_CreateWindow("SDL Tutorial - Images", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	// Loading success flag
	bool success = true;

	// Load image!
	gXOut = SDL_LoadBMP("x.bmp");
	if (gXOut == NULL) {
		printf("Unable to load image %s! SDL_Error: %s\n", "image.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close() {
	// Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL; // revert pointers to NULL when not pointing

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[]) {
	// Fire up SDL, create our window
	if (!init()) {
		printf("Failed to init!\n");
	}
	else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;

			// Main loop
			while (!quit) {
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) quit = true;
					printf("%d\n", e.key);
				}
			// Apply image
			SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

			// Update the surface to draw image
			SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}