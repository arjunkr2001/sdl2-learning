#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main() {
  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << endl;
    return 1;
  }

  // Create a window.
  SDL_Window* window = SDL_CreateWindow("SDL2 Button", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
    return 1;
  }

  // Create a renderer for the window.
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
    return 1;
  }

  // Create a button.
  SDL_Rect buttonRect = {100, 100, 200, 50};
  SDL_Color buttonColor = {255, 0, 0, 255};
  

  // Event loop.
  bool quit = false;
  while (!quit) {
    // Handle events.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= buttonRect.x && event.button.x <= buttonRect.x + buttonRect.w && event.button.y >= buttonRect.y && event.button.y <= buttonRect.y + buttonRect.h) {
            cout << "Button pressed!" << endl;
          }
          break;
      }
    }

    // Clear the screen.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the button.
    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &buttonRect);

    // Update the screen.
    SDL_RenderPresent(renderer);
  }

  // Cleanup.
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
