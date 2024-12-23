#pragma once  
#include "framework.h"
#include "labyrinth.h"
#include"Ghost.h"  
#include <math.h>
#include <array>
#include <windows.h>
#include <algorithm>  

 int mapkindX = 0;
 int mapkindY = 0;
 int mapkind = 0;
 unsigned long time0;

 WCHAR str[20];

enum SceneType
{
	TheGameScene,TheMainMnue,TheWinScene
};


class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void Update()
	{

	}

	virtual void Draw(HDC hdc,RECT& rect, unsigned long time0)
	{

	}


	virtual void InputDown(WPARAM downKey)
	{

	}


    virtual void InputUp(WPARAM upKey)
    {

    }
};  





class GameScene : public Scene
{
public:
	Player& player;
	Map& map;
	int mapSize;

    GameScene(Player& p,Map& m ,int size) : player(p),map(m),mapSize(size) {}

	void Update() override
	{
		if (map.grid[(int)floor(player.playerY / 7)][(int)floor(player.playerX / 7)])
		{
			//win = true;
		}

		if (Wkey)
		{
			player.playerDir = 1;
			updatePlayer(player.playerX, player.playerY);
		}
		if (Akey)
		{
			player.playerAngle += 0.05;
		}
		if (Dkey)
		{
			player.playerAngle += -0.05;
		}
		if (Skey)
		{
			player.playerDir = -1;
			updatePlayer(player.playerX, player.playerY);
		}
	}


	void Draw(HDC hdcMem,RECT& clientRect , unsigned long time0) override
	{
		FillRect(hdcMem, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));
		showMap(hdcMem, floor(player.playerX / mapSize), floor(player.playerY / mapSize));
		drawMapPlayer(hdcMem);
		drawRay(hdcMem);
		player.CheckCollision(&map);
		//wwwwwwblinky.Update();
		drawTime(hdcMem, time0);
	}  


    void InputDown(WPARAM wParam) override
    {
        downKey = wParam;  //传入输入信息
        switch (downKey)
        {
            case 87:
            {
                Wkey = true;
                break;
            }
            case 65:
            {
                Akey = true;
                break;
            }
            case 68:
            {
                Dkey = true;
                break;
            }
            case 83:
            {
                Skey = true;
                break;
            }
            case 82:
            {
                Rkey = true;
                break;
            }
        }


    }


	void InputUp(WPARAM wParam) override
    {
		upKey = wParam;
		switch (upKey)
		    {
		    case 87:
		    {
			    Wkey = false;
			    break;
		    }
		    case 65:
		    {
			    Akey = false;
			    break;
		    }
		    case 68:
		    {
			    Dkey = false;
			    break;
		    }
		    case 83:
		    {
			    Skey = false;
			    break;
		    }
		    case 82:
		    {
			    Rkey = false;
			    break;
		    }
		}
    }


private:
	bool Wkey = false;
	bool Akey = false;
	bool Skey = false;
	bool Dkey = false;
	bool Rkey = false;

    WPARAM downKey = 0;
    WPARAM upKey = 0;



	std::array<double, 2> updatePlayer(double& playerX, double& playerY)
	{
		player.playerDeltaX = sin(player.playerAngle) * player.speed * player.playerDir;
		player.playerDeltaY = cos(player.playerAngle) * player.speed * player.playerDir;
		//撞墙判断
		if (map.grid[(int)floor(playerY / mapSize)][(int)floor((playerX + player.playerDeltaX) / mapSize)] != 1)
			player.playerX += player.playerDeltaX;
		if (map.grid[(int)floor((playerY + player.playerDeltaY) / mapSize)][(int)floor(playerX / mapSize)] != 1)
			player.playerY += player.playerDeltaY;

		std::array<double, 2> position = { playerX, playerY };
		return position;
	}


    void drawTime(HDC hdc, unsigned long time0)
    {
        unsigned long time = GetTickCount64() - time0;
        unsigned long tolSec = time / 1000;
        int min = tolSec / 60;
        int sec = tolSec % 60;
        if (sec > 9)
            swprintf(str, 20, L"用时: %d:%d", min, sec);
        else
            swprintf(str, 20, L"用时: %d:0%d", min, sec);

        LOGFONT lf;
        memset(&lf, 0, sizeof(LOGFONT));
        lf.lfHeight = 50;
        lf.lfWeight = FW_BOLD;
        wcscpy_s(lf.lfFaceName, 20, L"Microsoft YaHei");
        HFONT hFont = CreateFontIndirect(&lf);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

        TextOut(hdc, 50, 350, str, wcslen(str));
        swprintf(str, 20, L"得分: %d", player.score);
        TextOut(hdc, 50, 400, str, wcslen(str));
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
    }

    void showMap(HDC hdc, int playerX, int playerY)
    {
        //HBRUSH hBrush0 = CreateSolidBrush(RGB(100, 120, 150)); 
        //HBRUSH hBrush1 = CreateSolidBrush(RGB(60, 60, 60));
        //HBRUSH hBrush2 = CreateSolidBrush(RGB(255, 255, 255));



        map.grid[12][1] = 3;

        HBRUSH hBrush3 = CreateSolidBrush(RGB(230, 240, 250));
        HBRUSH hBrush4 = CreateSolidBrush(RGB(90, 80, 70));
        HBRUSH hBrush5 = CreateSolidBrush(RGB(150, 220, 90));
        SelectObject(hdc, hBrush3);
        Rectangle(hdc, 300, 0, 1600, 450);
        SelectObject(hdc, hBrush4);
        Rectangle(hdc, 300, 450, 1600, 900);

        /* int temX, temY;
         if(player1.playerX-5 >= 0&& player1.playerX+5 < mapHeight)
             temX = player1.playerX;
         else if(player1.playerX-5 < 0)
             temX = 5;
         else if(player1.playerX+5 >= mapHeight)
             temX = mapHeight-5;
         if(player1.playerY-5 >= 0&& player1.playerY+5 < mapWidth)
             temY = playerY;
         else if(player1.playerY-5 < 0)
             temY = 5;
         else if(player1.playerY+5 >= mapWidth)
             temY = mapWidth-5;

         SelectObject(hdc, hBrush1);
         Rectangle(hdc,5,5,5+ mapWidth *mapSize,5+ mapWidth *mapSize);
         SelectObject(hdc, hBrush2);
         Rectangle(hdc, 5+temX*7-35, 5+temY*7-35, 5+temX*7+35, 5+temY*7+35);
         for (int i = temX-5; i < temX+5; i++)
         {
             std::cout << "The value of i is: " << i << std::endl;
             for (int j = temY-5; j < temY+5; j++)
             {

                 std::cout << "The value of j is: " << j << std::endl;
                 if (worldMap.grid[j][i] == 1)
                 {
                     SelectObject(hdc, hBrush0);
                     Rectangle(hdc, 5+mapSize * i, 5+mapSize * j,5+mapSize + mapSize * i,5+mapSize + mapSize * j);
                 }
                 else if(worldMap.grid[j][i] == 2)
                 {
                     SelectObject(hdc, hBrush5);
                     Rectangle(hdc, 5 + mapSize * i, 5 + mapSize * j, 5 + mapSize + mapSize * i, 5 + mapSize + mapSize * j);
                 }
             }
         }   */
         //DeleteObject(hBrush0);
        // DeleteObject(hBrush1);
        // DeleteObject(hBrush2);
        DeleteObject(hBrush3);
        DeleteObject(hBrush4);
        DeleteObject(hBrush5);

    }



    void drawMapPlayer(HDC hdc)
    {
        HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 120, 150));
        SelectObject(hdc, hBrush1);
        Ellipse(hdc, 5 + player.playerX - 3, 5 + player.playerY - 3, 5 + player.playerX + 3, 5 + player.playerY + 3);
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        MoveToEx(hdc, 5 + player.playerX, 5 + player.playerY, NULL);
        LineTo(hdc, 5 + player.playerX + sin(player.playerAngle) * 8, 5 + player.playerY + cos(player.playerAngle) * 8);
        DeleteObject(hPen);
    }

    void drawRay(HDC hdc)
    {
        double currentAngle = player.playerAngle + 0.5;
        //玩家位置向下取整为mapSize的倍数
        int rayStartX = floor(player.playerX / mapSize) * mapSize;
        int rayStartY = floor(player.playerY / mapSize) * mapSize;

        for (int i = 0; i < 1300; i++)
        {
            //当前角度的正弦值和余弦值（不等于0）
            double currentSin = sin(currentAngle);
            if (currentSin == 0.0)
                currentSin = 0.000001;

            double currentCos = cos(currentAngle);
            if (currentCos == 0.0)
                currentCos = 0.000001;

            double rayEndX, rayEndY, verticalDepth;
            int rayDirX, rayDirY;

            if (currentSin > 0)
            {
                rayEndX = rayStartX + mapSize;
                rayDirX = 1;
            }
            else
            {
                rayEndX = rayStartX;
                rayDirX = -1;
            }
            for (int offset = 0; offset < mapWidth; offset += 1)
            {
                verticalDepth = (rayEndX - player.playerX) / currentSin;
                rayEndY = player.playerY + verticalDepth * currentCos;
                int mapTargetX = floor(rayEndX / mapSize);
                int mapTargetY = floor(rayEndY / mapSize);
                if (currentSin <= 0)
                    mapTargetX += rayDirX;
                if (mapTargetY < 0 || mapTargetY > 199)
                {
                    mapkindX = 1;
                    break;
                }
                if (mapTargetX < 0 || mapTargetX > 199)
                {
                    mapkindX = 1;
                    break;
                }
                if (map.grid[mapTargetY][mapTargetX] != 0)
                {
                    mapkindX = 1;
                    break;
                }
                if (map.grid[mapTargetY][mapTargetX] == 8)
                {
                    mapkindX = 8;
                    break;
                }
                rayEndX += rayDirX * mapSize;
            }
            double tempX = rayEndX;
            double tempY = rayEndY;
            double horizontalDepth;
            if (currentCos > 0) { rayEndY = rayStartY + mapSize; rayDirY = 1; }
            else { rayEndY = rayStartY; rayDirY = -1; }
            for (int offset = 0; offset < mapWidth; offset += 1)
            {
                horizontalDepth = (rayEndY - player.playerY) / currentCos;
                rayEndX = player.playerX + horizontalDepth * currentSin;
                int mapTargetX = floor(rayEndX / mapSize);
                int mapTargetY = floor(rayEndY / mapSize);
                if (currentCos <= 0)
                    mapTargetY += rayDirY;
                if (mapTargetY < 0 || mapTargetY > 199)
                {
                    mapkindY = 1;
                    break;
                }
                if (mapTargetX < 0 || mapTargetX > 199)
                {
                    mapkindY = 1;
                    break;
                }
                if (map.grid[mapTargetY][mapTargetX] == 1)
                {
                    mapkindY = 1;
                    break;
                }
                if (map.grid[mapTargetY][mapTargetX] == 8)
                {
                    mapkindY = 8;
                    break;
                }
                rayEndY += rayDirY * mapSize;
            }
            double depth = verticalDepth < horizontalDepth ? verticalDepth : horizontalDepth;
            double endX = verticalDepth < horizontalDepth ? tempX : rayEndX;
            double endY = verticalDepth < horizontalDepth ? tempY : rayEndY;
            mapkind = verticalDepth < horizontalDepth ? mapkindX : mapkindY;
            //=========================================================================
            if (mapkind == 1)
            {
                depth *= cos(player.playerAngle - currentAngle);
                int height = 8000 / (depth + 0.001);
                HPEN hPen1 = CreatePen(PS_SOLID, 2, RGB(min(120 + endX / 3, 255), min(120 + endY / 3, 255), 110));
                HPEN hPen2 = CreatePen(PS_SOLID, 2, RGB(min(150 + endX / 3, 255), min(150 + endY / 3, 255), 160));
                if (verticalDepth < horizontalDepth)
                    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen2);
                else
                    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen1);
                MoveToEx(hdc, i + 300, 450 - height / 2, NULL);
                LineTo(hdc, i + 300, 450 + height / 2);
                DeleteObject(hPen1);
                DeleteObject(hPen2);
                mapkind = 0;
                mapkindX = 0;
                mapkindY = 0;
            }

            if (mapkind == 8)
            {
                depth *= cos(player.playerAngle - currentAngle);
                int height = 8000 / (depth + 0.001);
                HPEN hPen3 = CreatePen(PS_SOLID, 2, RGB(200, 150, 0));
                HPEN hPen4 = CreatePen(PS_SOLID, 2, RGB(255, 200, 0));
                if (verticalDepth < horizontalDepth)
                    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen3);
                else
                    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen4);
                MoveToEx(hdc, i + 300, 450 - height / 2, NULL);
                LineTo(hdc, i + 300, 450 + height / 2);
                DeleteObject(hPen3);
                DeleteObject(hPen4);
                mapkind = 0;
                mapkindX = 0;
                mapkindY = 0;
            }
            //===========================================================================

            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(100, 150, 50));
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
            MoveToEx(hdc, 5 + player.playerX, 5 + player.playerY, NULL);
            LineTo(hdc, 5 + endX, 5 + endY);
            DeleteObject(hPen);
            currentAngle -= 1.0466 / 1300;
        }
    }
	
};  








