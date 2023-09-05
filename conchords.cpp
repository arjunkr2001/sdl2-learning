#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

int WIDTH = 800, HEIGHT = 600;
SDL_Rect buttonRect,bgQuad,renderQuad;
SDL_Color buttonColor;
void updateBtn(int play,SDL_Renderer* renderer,SDL_Texture *startSurfaceTexture, SDL_Texture *pauseSurfaceTexture,SDL_Texture *bgTexture, SDL_Texture *imageTexture){
	cout<<"  in update\n";
	SDL_RenderClear(renderer);
	     SDL_RenderCopy(renderer, bgTexture, NULL, &bgQuad);
    SDL_RenderCopy(renderer, imageTexture, NULL, &renderQuad);
	if(play==1){
            	SDL_RenderCopy(renderer, pauseSurfaceTexture, NULL, &buttonRect);
            }
        else{
            	SDL_RenderCopy(renderer, startSurfaceTexture, NULL, &buttonRect);
            }
}
void create_button(){
    //buttonRect = {(WIDTH/2)-((WIDTH/5)/2), (HEIGHT/2)+(HEIGHT/10), (WIDTH/5), (HEIGHT/10)};
    buttonRect = {(WIDTH/2)-50, (HEIGHT/2)-50, 100,100};
    //buttonColor = {255, 50, 90, 255};
    bgQuad = {0,0,WIDTH,HEIGHT};
    //renderQuad = {(WIDTH/2)-((WIDTH/5)/2), (HEIGHT/2)-((WIDTH/5)/2)-50, (WIDTH/5), (WIDTH/5)};
    renderQuad = {10,10,200,60};
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("ConChords", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
  //SDL_SetWindowSize(window, WIDTH, HEIGHT);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Create a button.
  create_button();
  
//       // Load the font.
//   TTF_Init();
//   TTF_Font *font = TTF_OpenFont("arial.ttf", 24);

//   // Create a surface with the text.
//   SDL_Color textColor = { 255, 255, 255, 200 };
//   SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello, world!", textColor);

//   // Create a texture from the surface.
//   SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//   SDL_FreeSurface(textSurface);

//   SDL_Rect renderQuad = { 100, 100, textSurface->w, textSurface->h };

// Load the image.
  SDL_Surface *imageSurface = IMG_Load("./conchords_text.png");
  
  // Create a texture from the image.
  SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
  SDL_FreeSurface(imageSurface);

  // Render the texture to the screen.
  // SDL_Rect renderQuad = { 100, 100, 100, 100};

  SDL_Surface *bg = IMG_Load("./bg2.png");
  SDL_Texture *bgTexture = SDL_CreateTextureFromSurface(renderer,bg);
  SDL_FreeSurface(bg);

  SDL_Surface *startButtonSurface = IMG_Load("./play_icon.png");
  SDL_Texture *startSurfaceTexture = SDL_CreateTextureFromSurface(renderer,startButtonSurface);
  SDL_FreeSurface(startButtonSurface);
  
  SDL_Surface *pauseButtonSurface = IMG_Load("./pause_icon.png");
  SDL_Texture *pauseSurfaceTexture = SDL_CreateTextureFromSurface(renderer,pauseButtonSurface);
  SDL_FreeSurface(pauseButtonSurface);
  
  int play = 0;
     // Clear the screen.
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);
  
     SDL_RenderCopy(renderer, bgTexture, NULL, &bgQuad);
    SDL_RenderCopy(renderer, imageTexture, NULL, &renderQuad);
  //  SDL_RenderCopy(renderer, startSurfaceTexture, NULL, &buttonRect);
  updateBtn(play,renderer,startSurfaceTexture,pauseSurfaceTexture,bgTexture,imageTexture);

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
            cout << "Button pressed!" << " ";
            play==1 ? play=0 : play=1;
            cout<<play<<endl;
            updateBtn(play,renderer,startSurfaceTexture,pauseSurfaceTexture,bgTexture,imageTexture);
          }
          break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
                cout<<WIDTH<<endl;
                create_button();
                break;
            }
      }
    }

    // Clear the screen.
    //SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    //SDL_RenderClear(renderer);


//   // Render the texture to the screen.
 //   SDL_RenderCopy(renderer, bgTexture, NULL, &bgQuad);
   // SDL_RenderCopy(renderer, imageTexture, NULL, &renderQuad);
    //SDL_RenderCopy(renderer, startSurfaceTexture, NULL, &buttonRect);
    //updateBtn(play,renderer,startSurfaceTexture,startSurfaceTexture);
    	//if(play){
            	//SDL_RenderCopy(renderer, pauseSurfaceTexture, NULL, &buttonRect);
            //}
        //else{
          //  	SDL_RenderCopy(renderer, startSurfaceTexture, NULL, &buttonRect);
           // }

    // Draw the button.
    //SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    //SDL_RenderFillRect(renderer, &buttonRect);

    // Update the screen.
    SDL_RenderPresent(renderer);
    //SDL_Delay(1000);
    //SDL_RenderClear(renderer);
  }

  // Cleanup.
  SDL_DestroyTexture(imageTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();

  return 0;
}
