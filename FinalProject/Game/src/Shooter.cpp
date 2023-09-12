#include "Constants.h"
#include "Game.h"
#include "Graphics.h"

#include <chrono>

bool init() {
    return true;
}

void close() {
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    Game& game = Game::get();
    Graphics& graphics = Graphics::get();

    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        using namespace std::chrono;
        high_resolution_clock::time_point prevTime = high_resolution_clock::now();

        bool quit = false;
        SDL_Event e;
        while (!quit) {
            // Get the elapsed time, and ensure it's at between TICK_MIN and TICK_MAX
            high_resolution_clock::time_point now = high_resolution_clock::now();
            double deltaTSec = (float)duration_cast<milliseconds>(now - prevTime).count() / 1000;

            if (deltaTSec > TICK_MAX)
            {
                //std::cout << "Tick duration over budget: " << deltaTSec << std::endl;
                deltaTSec = TICK_MAX;
            }

            if (deltaTSec < TICK_MIN)
                continue;

            prevTime = now;

            graphics.resetFrame();

            Gunner* player = game.getPlayer();

            // Handle UI events - quit if appropriate, otherwise, pass them on to the UI controller (if any)
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) { quit = true; }
                if (e.type == SDL_KEYDOWN) {
                  switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        player->moveUp();
                        break;
                    case SDLK_DOWN:
                        player->moveDown();
                        break;
                    case SDLK_RIGHT:
                        player->moveRight();
                        break;
                    case SDLK_LEFT:
                        player->moveLeft();
                        break;
                    case SDLK_SPACE:
                        game.addBullet(player->shootBullet());
                        break;
                    default:
                        break;
                  }
                }
            }

            // TICK 
            game.tick((float)deltaTSec);

            // RENDER
            std::vector<Gunner*> enemies = game.getEnemy();
            std::vector<Cover*> covers = game.getCovers();
            std::vector<Bullet*> bullets = game.getBullets();

            graphics.drawPlayer(game.getPlayer());

            for (Gunner* enemy: enemies) {
                graphics.drawEnemy(enemy);
            }

            for (Cover* cover : covers) {
                graphics.drawCovers(cover);
            }

            for (Bullet* bullet : bullets) {
              graphics.drawEnemy(bullet);
            }

            // If there is a winner, draw the message to the screen
            graphics.drawWinScreen(game.checkGameOver());

            graphics.render();
        }

    }

    close();
    return 0;
}

