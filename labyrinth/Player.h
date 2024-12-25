#pragma once  
#include"Map.h"
#include<iostream>


enum PlayerFlip
{
    Right,Left,Up,Down
};

class Player
{
public:

	/// <summary>
	/// x为纵方向,y为横方向
	/// </summary>
    
    int playerDir = 0;
    int playerDir2 = 0;
    double playerAngle = -1.5;
    double speed = 0.8;

    double playerDeltaX = 0;
    double playerDeltaY = cos(playerAngle) * speed;

    double playerX = 10;
    double playerY = 10;
    Vector2 position;

	bool isDead;
    bool scoreUp=false;
    PlayerFlip flip;

    int score;


    Player(int x, int y) :  playerX(x), playerY(y), isDead(false) { score = 0; }

    // 玩家死亡
    void die() 
    {
        isDead = true;
        std::cout << "Player is dead!" << std::endl;
    }



 

    void CheckCollision(Map* map)
    {
        if (map->grid[(int)floor(playerY / 6)][(int)floor((playerX + playerDeltaX) / 6)] == 8)
        {
            score++;
            map->grid[(int)floor(playerY / 6)][(int)floor((playerX + playerDeltaX) / 6)] = 0;
            scoreUp = true;
        }
    }

    void DisPlayScore()
    {
        std::cout << "本局分数为" << " " << score << std::endl;
    }



    void Update()
    {
        position.x = playerX;
        position.y = playerY;
    }
};
