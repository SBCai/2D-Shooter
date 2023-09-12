#include "Game.h"

#include <cmath>

template<>
Game* Singleton<Game>::s_Obj = NULL;

// initialize game
Game::Game()
    : gameOverState(0) // No winner at start of game
{
    buildPlayer();
    buildCovers();
    buildEnemy();
}

// delete pointers
Game::~Game()
{
  delete m_player;
  for (Cover* cover : m_covers)
    delete cover;
  for (Gunner* enemy : m_enemy)
    delete enemy;
  for (Bullet* bullet : m_bullets)
    delete bullet;
}

// game tick
void Game::tick(float deltaTSec)
{
    // make sure game is active
    if (this->gameOverState == 0) {
      // go through all enemy
      for (Gunner* enemy: getEnemy()) {
        // generate all covers positions
        Generator* generator = new Generator();
        std::vector<std::pair<Vec2, char>> coversPos = generator->generatePositions(*this);
        // initialize all considerations
        FloatFunctor* coverDistanceConsideration = new CoverDistanceConsideration(enemy->getPosition());
        FloatFunctor* coverAngleConsideration = new CoverAngleConsideration(m_player->getPosition());
        FloatFunctor* coverSelectedConsideration = new CoverSelectedConsideration(enemy->getCoverPos());
        FloatFunctor* coverToPlayerConsideration = new CoverToPlayerConsideration(m_player->getPosition(), enemy->getPosition());
        FloatFunctor* coverOccupyConsideration = new CoverOccupyConsideration(m_enemy);

        std::vector<FloatFunctor*> considerations;
        considerations.push_back(coverDistanceConsideration);
        considerations.push_back(coverAngleConsideration);
        considerations.push_back(coverSelectedConsideration);
        considerations.push_back(coverToPlayerConsideration);
        considerations.push_back(coverOccupyConsideration);

        // initialize aggregator for cover points
        Aggregator* aggregator = new Aggregator(considerations);
        std::vector<float> points;
        // evaluate points for all covers
        for(std::pair<Vec2, char> cover : coversPos) {
          aggregator->setCover(cover);
          points.push_back(aggregator->evaluate());
        }
        // cover position selector
        PositionFunctor* posSelector = new PositionFunctor();
        // initialize all actions
        Action* shootAction = new ShootAction(m_player, enemy, m_covers, SHOOTPRIORITY);
        Action* moveAction = new MoveAction(m_player, enemy, m_covers, MOVEPRIORITY);
        Action* waitAction = new WaitAction();
        std::vector<Action*> action;
        action.push_back(shootAction);
        action.push_back(moveAction);
        action.push_back(waitAction);

        // initialize aggregator for action
        MaxAggregator* maxAggregator = new MaxAggregator(action);
        // find the max point of an action
        float action_point = maxAggregator->evaluate();
        // action selector
        if (action_point > 3.0f) {
          addBullet(enemy->enemyShootBullet(getPlayer()->getPosition()));
        } else if (action_point > 2.0f) {
          Vec2 destPos = posSelector->evaluate(coversPos, points);
          if (destPos != Vec2(-1, -1)) {
            enemy->setDestPos(destPos);
            enemy->tick(deltaTSec);
          }
        } else {
          // wait, do nothing
        }

        delete generator;
        delete coverDistanceConsideration;
        delete coverAngleConsideration;
        delete coverSelectedConsideration;
        delete coverToPlayerConsideration;
        delete aggregator;
        delete maxAggregator;
        delete posSelector;
        delete shootAction;
        delete moveAction;
        delete waitAction;
      }

      //use a reverse iterator, which will allow us to delete elements without affecting the rest of the loop.
      for (auto bullet = m_bullets.rbegin(); bullet != m_bullets.rend(); ++bullet) {
        (*bullet)->tick(deltaTSec);
        if((*bullet)->isOutOfMap() || (*bullet)->collideCover(m_covers)) {
          m_bullets.erase(std::next(bullet).base());
        } else {

          if ((*bullet)->collideEntity(m_player->getPosition(), m_player->getSize(), 0)) {
            m_player->getHit();
          }

          for (auto enemy = m_enemy.rbegin(); enemy != m_enemy.rend(); ++enemy) {
            if ((*bullet)->collideEntity((*enemy)->getPosition(), (*enemy)->getSize(), 1)) {
              m_enemy.erase(std::next(enemy).base());
            }
          }
        }
      }
    }
}
// build player
void Game::buildPlayer() {
  Vec2 player_init_pos(GAME_GRID_WIDTH / 2.f, GAME_GRID_HEIGHT - 1.f);
  m_player = new Gunner(player_init_pos, 1, SHORT_GUNNER_TYPE, SHORT_GUNNER_SIZE);
}
// build cover
void Game::buildCovers() {
  Cover* cover1 = new Cover(Vec2(2,2), 1);
  Cover* cover2 = new Cover(Vec2(15,1), 0);
  Cover* cover3 = new Cover(Vec2(30,2), 0);
  Cover* cover4 = new Cover(Vec2(45,3), 1);
  Cover* cover5 = new Cover(Vec2(3,15), 0);
  Cover* cover6 = new Cover(Vec2(8,12), 1);
  Cover* cover7 = new Cover(Vec2(15,15), 1);
  Cover* cover8 = new Cover(Vec2(50,15), 0);
  Cover* cover9 = new Cover(Vec2(18,30), 1);
  Cover* cover10 = new Cover(Vec2(25,28), 0);

  Cover* cover11 = new Cover(Vec2(25,8), 1);
  Cover* cover12 = new Cover(Vec2(40,4), 1);
  Cover* cover13 = new Cover(Vec2(20,15), 0);
  Cover* cover14 = new Cover(Vec2(25,20), 1);
  Cover* cover15 = new Cover(Vec2(25,28), 0);

  Cover* cover16 = new Cover(Vec2(30,10), 0);
  Cover* cover17 = new Cover(Vec2(40,10), 1);
  Cover* cover18 = new Cover(Vec2(6,25), 0);
  Cover* cover19 = new Cover(Vec2(15,25), 1);
  Cover* cover20 = new Cover(Vec2(30,28), 0);

  Cover* cover21 = new Cover(Vec2(32,16), 0);
  Cover* cover22 = new Cover(Vec2(34,19), 1);
  Cover* cover23 = new Cover(Vec2(40,24), 0);
  Cover* cover24 = new Cover(Vec2(8,6), 0);
  Cover* cover25 = new Cover(Vec2(11,20), 1);

  Cover* cover26 = new Cover(Vec2(49,24), 0);
  Cover* cover27 = new Cover(Vec2(20,10), 1);
  Cover* cover28 = new Cover(Vec2(30,24), 1);
  Cover* cover29 = new Cover(Vec2(43,14), 0);
  Cover* cover30 = new Cover(Vec2(50,7), 0);
  Cover* cover31 = new Cover(Vec2(45,21), 1);

  Cover* cover32 = new Cover(Vec2(16,9), 0);
  Cover* cover33 = new Cover(Vec2(37,7), 0);
  Cover* cover34 = new Cover(Vec2(47,13), 1);
  Cover* cover35 = new Cover(Vec2(44,27), 0);
  Cover* cover36 = new Cover(Vec2(51,22), 1);

  m_covers.push_back(cover1);
  m_covers.push_back(cover2);
  m_covers.push_back(cover3);
  m_covers.push_back(cover4);
  m_covers.push_back(cover5);
  m_covers.push_back(cover6);
  m_covers.push_back(cover7);
  m_covers.push_back(cover8);
  m_covers.push_back(cover9);
  m_covers.push_back(cover10);
  m_covers.push_back(cover11);
  m_covers.push_back(cover12);
  m_covers.push_back(cover13);
  m_covers.push_back(cover14);
  m_covers.push_back(cover15);
  m_covers.push_back(cover16);
  m_covers.push_back(cover17);
  m_covers.push_back(cover18);
  m_covers.push_back(cover19);
  m_covers.push_back(cover20);
  m_covers.push_back(cover21);
  m_covers.push_back(cover22);
  m_covers.push_back(cover23);
  m_covers.push_back(cover24);
  m_covers.push_back(cover25);
  m_covers.push_back(cover26);
  m_covers.push_back(cover27);
  m_covers.push_back(cover28);
  m_covers.push_back(cover29);
  m_covers.push_back(cover30);
  m_covers.push_back(cover31);
  m_covers.push_back(cover32);
  m_covers.push_back(cover33);
  m_covers.push_back(cover34);
  m_covers.push_back(cover35);
  m_covers.push_back(cover36);
}

// build enemy
void Game::buildEnemy() {
  m_enemy.push_back(new Gunner(Vec2(1,1), 1, SHORT_GUNNER_TYPE, SHORT_GUNNER_SIZE));
  m_enemy.push_back(new Gunner(Vec2(7,7), 1, SHORT_GUNNER_TYPE, SHORT_GUNNER_SIZE));
  m_enemy.push_back(new Gunner(Vec2(20,20), 1, SNIPER_TYPE, SNIPER_SIZE));
  m_enemy.push_back(new Gunner(Vec2(30,5), 1, SNIPER_TYPE, SNIPER_SIZE));
  m_enemy.push_back(new Gunner(Vec2(40,20), 1, SNIPER_TYPE, SNIPER_SIZE));
}

int Game::checkGameOver() {
    if (this->gameOverState == 0) {
        if (m_player->getHealth() == 0)
          this->gameOverState = -1;
        else {
          int health = 0;
          for (Gunner* enemy: m_enemy) {
            health += enemy->getHealth();
          }
          if (health == 0) {
            this->gameOverState = 1;
          }
        }
    }
    return this->gameOverState;
}



