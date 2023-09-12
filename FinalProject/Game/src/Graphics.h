#pragma once

#include "Gunner.h"
#include "Entity.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Singleton.h"
#include "Cover.h"

class Graphics : public Singleton<Graphics> {
	/**
	 * Houses the logic for drawing the game to the screen.
	 * Acts as a StringBuilder but for images drawn the the canvas.
	 */

public:
	Graphics();
	virtual ~Graphics();  //SDL_DestroyRenderer(gRenderer);

  void drawPlayer(Gunner* gunner);
	void drawEnemy(Entity* enemy);
	void drawText(const char* textToDraw, SDL_Rect messageRect, SDL_Color color);
	void drawCovers(Cover* cover);

	void resetFrame();

	void drawWinScreen(int winningSide);

	void render();

private: 

	void drawSquare(float centerX, float centerY, float size);
  void drawRect(float centerX, float centerY, float width, float height, int type);

	void drawGrid();
	void drawBG();
	void drawUI();

	SDL_Renderer* gRenderer;
	SDL_Window* gWindow;
	TTF_Font* sans;
};