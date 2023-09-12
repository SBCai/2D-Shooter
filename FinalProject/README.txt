Since I am a Mac user, here's the command I need to compile my code:
g++ -std=c++14 -I./Interface/src -I./Game/src -I Modular_AI_system/src -I/opt/homebrew/include/SDL2 -g $(find . -type f -iregex ".*\.cpp") -D_THREAD_SAFE -lSDL2 -lSDL2_image -lSDL2_ttf -o shooter

Description:
  This is the game from "Pre-Approved Topic #1: Modular AI for Position Selection". In generally, it's a top down game which includes a list of pre-set covers (horizontal bar and vertical bar), a list of enemies (rectangle), and a player (rectangle). Enemies move from cover to cover to approach, and shoot the player when player is within their sight range. User can use the direction keys to move the player, and space bar to shoot. When all enemies are shot, or player got shoot, game over.

Design:
  Cover:
    A cover contains a position and the type of it. The type can be horizontal cover and vertical cover. When initializing the game, we pre-define a list of covers for the game and draw them on the game ground. 
  Enemy/player:
    An enemy/player is an instance of the Gunner class which contains all the information needed for it, such as position, size, destination position, cover position etc., and functions that allow it to move and shoot.  
  Bullet:
    In Buller class, we have position and the size of the bullet, as well as the type of the bullet (whether enemy shoots or player shoots). We have tick and move functions for bullet to move, and some functions to check if a bullet is out of map, colliding with covers, and hitting enemy/player.
  Generator:
    In the generator, we basically take the list of horizontal covers and vertical covers we pre-define of the game, and generates positions on top/down of the horizontal covers, and left/right of the vertical covers, so that each cover has 2 cover sides. Each cover generated has 2 elements. One is the position, another is the side it can protect the enemy. For example, if the type is "up", then when enemy moves to it, it can protect player who's position is below the cover.
  Considerations:
    For considerations, we let all the consideration classes inherits float functor class so that we can use them as one type. 
    1. We have a CoverToPlayerConsideration, which takes in enemy's and player's position, and evaluate a cover to see if the cover is between enemy and player, so that enemy will not choose covers that would make them move away from player.
    2. We have CoverDistanceConsideration, which takes in enemy's position, and evaluate a cover to see which cover is closer to the enemy, so that we don't choose cover that is far away if we have a closer one.
    3. We have CoverAngleConsideration, which takes in player's position, and evaluate a cover to see if the cover can protect the enemy from being seen by player, by checking the type of the cover, and comparing the position of the cover and player.
    4. We have CoverSelectedConsideration, which takes in previous cover position, and evaluate a cover to see if the cover was selected before, so that enemy will not choose the same set of cover and move back and forth forever.
    5. We have CoverOccupyConsideration, which takes in a list of enemy, and evaluate a cover to see if any enemy is occupying the cover, so that another enemy will not move to the cover.
  Aggregator:
    This is the sum aggregator which takes in a list of considerations defined above, to evaluate a cover using the considerations and return the total score of the cover.
  PositionFunctor:
    This is the position selector which takes in a list of cover positions, and a list of scores corresponding the covers evaluated by the aggregator above, to choose the best cover position.
  Action:
    There are 3 type of actions.
    1. Shoot action:
      This class takes in a player, an enemy, all cover positions, and priority to evaluate if the enemy should shoot player. It check the positions between player and the enemy, and also check if there's any cover in between them. Then it will check the distance between player and the enemy and see if within shoot range. Then return the total priority score.
    2. Move action:
      This class takes in an enemy, and priority to evaluate if the enemy should be on the move to the next cover position. It will check if the enemy is currently hidden or not, and if it's been hiding more than 3 seconds. Then return the total priority score. It also check if the player can see them. If player can, it will return a higher point to force the enemy to move to another cover, regardless if it has been hiding for 3 seconds. 
    3. Wait action:
      This class serves the purpose of not doing anything when both shoot action and move action return priority score of less than 1. It will always return the priority score of 1.
  MaxAggregator:
     This class basically takes in a list of action, and return the max score among all the action scores. In the game tick, basing on the score, we choose action. 

Overall, when the game starts up, we will build all the covers, enemies and player, and draw them on the game. For players we can use the direction keys to move, and space key to shoot. Each game tick, we initialize all the cover positions, all the considerations, aggregators and. For each enemy on the game, we evaluate cover positions and generate the best cover position. Then we initialize all actions, and for each enemy we evaluate what action the enemy should do. If shoot, we will generate a bullet, and aim the bullet to player. If move, the we will set the destination of the enemy to the best cover position we just generated. If wait, we do nothing. Then we go through all bullets in the game, and check if any bullet is out of map so we remove it from the game, if any bullet is colliding with cover so we remove it, if any bullet is hitting enemy so we remove both the enemy and the bullet, and if any bullet is hitting player, so we decrement the player's health. We continue game tick until all enemies are eliminated or player is eliminated. 

What went well is that enemies are moving as expected. They can move from cover to cover to approach player regardless of where the player is. They shoot player when player is within sight range instead of trying to hide again, but they will try to hide when player is not within sight range. Even when the enemy is on the move to the next cover, if the player currently moves near the enemy, the enemy will abandon the cover and choose another one to hide from player.  
What went not very well is that although there's a consideration for enemy to choose a cover that's not currently occupied, there's still little bug that sometimes enemy still use the same cover position and resulting in overlaying each other. Another thing is that there's only 1 type of enemy right now, which makes the game not as fun. I was planing on adding another type which will stay away from player and shoot in a long range. 
