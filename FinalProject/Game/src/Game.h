// MIT License
// 
// Copyright(c) 2020 Arthur Bacon and Kevin Dill
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <chrono>
#include "Singleton.h"
#include "Vec2.h"
#include "Gunner.h"
#include "Bullet.h"
#include "Cover.h"
#include "Generator.h"
#include "CoverDistanceConsideration.h"
#include "CoverAngleConsideration.h"
#include "CoverSelectedConsideration.h"
#include "Aggregator.h"
#include "PositionFunctor.h"
#include "CoverToPlayerConsideration.h"
#include "CoverOccupyConsideration.h"
#include "ShootAction.h"
#include "MoveAction.h"
#include "WaitAction.h"
#include "MaxAggregator.h"
#include <vector>
#include <float.h>

// game class
class Game : public Singleton<Game>
{
public:
    explicit Game();
    virtual ~Game();
    // game tick
    void tick(float deltaTSec);
    // get all covers
    std::vector<Cover*>& getCovers() {return m_covers;}
    // get all enemy
    std::vector<Gunner*>& getEnemy() {return m_enemy;}
    // get all bullet
    std::vector<Bullet*>& getBullets() {return m_bullets;}
    // get player
    Gunner* getPlayer() {return m_player;}
    // check game status
    int checkGameOver();
    // add bullet to game
    void addBullet(Bullet* bullet) {m_bullets.push_back(bullet);}


private:
    // build player, covers and enemy
    void buildPlayer();
    void buildCovers();
    void buildEnemy();

private:
    Gunner* m_player;
    std::vector<Gunner*> m_enemy;

    std::vector<Cover*> m_covers;

    std::vector<Bullet*> m_bullets;

    // Negative => Enemy won, Positive => Player won, 0 => no winner yet
    int gameOverState; 
};

