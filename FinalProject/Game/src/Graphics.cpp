#include "Graphics.h"

#include "Constants.h"
#include <algorithm>

template<>
Graphics* Singleton<Graphics>::s_Obj = NULL;

Graphics::Graphics() {
	gWindow = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_PIXELS, SCREEN_HEIGHT_PIXELS, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		gRenderer = NULL;
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else {
		//Create renderer for window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else {
			//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
		}
	}

    // init the text libraries
    if (TTF_Init() < 0) {
        printf("Text library TTF could not be Initialized correctly.\n");
    }

    // Load in the font
    sans = TTF_OpenFont("Game/fonts/abelregular.ttf", 36);
    if (!sans) { printf("TTF_OpenFont: %s\n", TTF_GetError()); }
}

Graphics::~Graphics() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
}

void Graphics::render() {
    SDL_RenderPresent(gRenderer);
}

void Graphics::resetFrame() {
    drawBG();
    drawUI();
}

void Graphics::drawPlayer(Gunner* gunner) {
  drawEnemy(gunner);
  Vec2 m_pos = gunner->getPosition();
  int size = gunner->getSize();
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 255);
  switch(gunner->getDirection()) {
    case 'l':
      drawRect((m_pos.x - size) * PIXELS_PER_METER, m_pos.y * PIXELS_PER_METER, GUN_LENGTH, GUN_WIDTH, 1);
      break;
    case 'r':
      drawRect((m_pos.x + size/4.f) * PIXELS_PER_METER, m_pos.y * PIXELS_PER_METER, GUN_LENGTH, GUN_WIDTH, 1);
      break;
    case 'u':
      drawRect(m_pos.x * PIXELS_PER_METER, (m_pos.y - size) * PIXELS_PER_METER, GUN_LENGTH, GUN_WIDTH, 0);
      break;
    case 'd':
      drawRect(m_pos.x* PIXELS_PER_METER, (m_pos.y + size/4.f) * PIXELS_PER_METER, GUN_LENGTH, GUN_WIDTH, 0);
      break;
    default:
      break;
  }
}

void Graphics::drawEnemy(Entity* enemy) {

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 1);

	float centerX = enemy->getPosition().x * PIXELS_PER_METER;
	float centerY = enemy->getPosition().y * PIXELS_PER_METER;
	float squareSize = enemy->getSize() * 20.0f;

	drawSquare(centerX, centerY, squareSize);
}

void Graphics::drawCovers(Cover* cover) {
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 1);

    drawRect(cover->getPosition().x * PIXELS_PER_METER,
             cover->getPosition().y * PIXELS_PER_METER,
             COVER_WIDTH,
             COVER_HEIGHT,
             cover->getType());
}

void Graphics::drawSquare(float centerX, float centerY, float size) {
    // Draws a square at the given pixel coorinate
    SDL_Rect rect = {
        (int)(centerX - (size / 2.f)),
        (int)(centerY - (size / 2.f)),
        (int)(size),
        (int)(size)
    };
    SDL_RenderFillRect(gRenderer, &rect);
}

void Graphics::drawRect(float centerX, float centerY, float width, float height, int type) {
  // Draws a square at the given pixel coorinate with type: 0 -> horizontal and 1 -> vertical cover
  SDL_Rect rect;
  // if the cover is horizontal
  if(type) {
    rect = {
            (int)(centerX - COVER_WIDTH / 2.f),
            (int)(centerY - COVER_HEIGHT / 2.f),
            (int)(width * PIXELS_PER_METER),
            (int)(height * PIXELS_PER_METER)
            };
  // if the cover is vertical
  } else {
    rect = {
            (int)(centerX - COVER_WIDTH / 2.f),
            (int)(centerY - COVER_HEIGHT / 2.f),
            (int)(height * PIXELS_PER_METER),
            (int)(width * PIXELS_PER_METER)
           };
  }
  SDL_RenderFillRect(gRenderer, &rect);
}

void Graphics::drawText(const char* textToDraw, SDL_Rect messageRect, SDL_Color color) {
    // Draws the given text in a box with the specified position and dimention

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, textToDraw, color);
    if (!surfaceMessage) { printf("TTF_OpenFont: %s\n", TTF_GetError()); }
    SDL_Texture* message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
    if (!message) { printf("Error 2\n"); }
    SDL_RenderCopy(gRenderer, message, NULL, &messageRect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void Graphics::drawGrid() {
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    // Draw Vert lines
    for (int xIndex = 0; xIndex < GAME_GRID_WIDTH + 1; xIndex++) {
        int xIndexPix = xIndex * PIXELS_PER_METER;
        SDL_RenderDrawLine(gRenderer,
            xIndexPix, 0,
            xIndexPix, SCREEN_HEIGHT_PIXELS);
    }

    // Draw Horiz lines
    for (int yIndex = 0; yIndex < GAME_GRID_HEIGHT; yIndex++) {
        int yIndexPix = yIndex * PIXELS_PER_METER;
        SDL_RenderDrawLine(gRenderer,
            0, yIndexPix,
            GAME_GRID_WIDTH * PIXELS_PER_METER, yIndexPix);
    }
}

void Graphics::drawBG() {
    SDL_Rect bgRect = {
        0,
        0,
        SCREEN_WIDTH_PIXELS,
        SCREEN_HEIGHT_PIXELS
    };
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 1);
    SDL_RenderFillRect(gRenderer, &bgRect);
    drawGrid();
}


void Graphics::drawWinScreen(int winningSide) {
    if (winningSide == 0) { return; }

    const char* msg = (winningSide > 0) ? "Game Over. Player Wins!" : "Game Over. Enemy Wins!";
    int topY = SCREEN_HEIGHT_PIXELS / 5;
    int leftX = SCREEN_WIDTH_PIXELS / 15;
    int height = SCREEN_HEIGHT_PIXELS / 3;
    int width = (SCREEN_WIDTH_PIXELS * 14) / 15;

    SDL_Rect stringRect = { leftX, topY, width, height };
    SDL_Color color = { 0, 0, 0, 255 };
    drawText(msg, stringRect, color);
}

void Graphics::drawUI() {
    // Draws the rectangle to the right of the play area that contains the UI

    SDL_Rect uiRect = {
        (int)(GAME_GRID_WIDTH * PIXELS_PER_METER),
        (int)0,
        (int)(UI_WIDTH * PIXELS_PER_METER),
        (int)(UI_HEIGHT * PIXELS_PER_METER),
    };
    SDL_SetRenderDrawColor(gRenderer, 0x50, 0x50, 0x50, 100);
    SDL_RenderFillRect(gRenderer, &uiRect);


}
