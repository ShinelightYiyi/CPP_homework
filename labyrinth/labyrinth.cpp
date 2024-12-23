// labyrinth.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "labyrinth.h"
#include"Ghost.h"  
#include <math.h>
#include <array>
#include <windows.h>
#include <algorithm>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

WPARAM downKey = 0;
WPARAM upKey = 0;
Player player1(20,20);

bool Wkey = false;
bool Akey = false;
bool Skey = false;
bool Dkey = false;
bool Rkey = false;

int mapSize =6;
int mapkindX = 0;
int mapkindY = 0;
int mapkind = 0;

unsigned long time0;
WCHAR str[20];
int count = 0;
unsigned long tolTime = 0;



const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

bool win = false;

Map worldMap(200,200);


BlinkyGhost blinky(10,10,&player1,&worldMap,"G1");
//
//int worldMap[mapWidth][mapHeight] =
//{
// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
// {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
// {1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
// {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
// {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
// {1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
// {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
// {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1}
//};

void SetMap()
{
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            if (i == 0 || i == 200 - 1 || j == 0 || j == 200 - 1)
                worldMap.grid[i][j] = 1;
        }
    }

    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            if (i%5==1 && j%5==1)
                worldMap.grid[i][j] = 8;
        }
    }
}

void showMap(HDC hdc,int playerX, int playerY)
{
    //HBRUSH hBrush0 = CreateSolidBrush(RGB(100, 120, 150)); 
    //HBRUSH hBrush1 = CreateSolidBrush(RGB(60, 60, 60));
    //HBRUSH hBrush2 = CreateSolidBrush(RGB(255, 255, 255));

   
           
    worldMap.grid[12][1] = 3;

    HBRUSH hBrush3 = CreateSolidBrush(RGB(230, 240, 250));
    HBRUSH hBrush4 = CreateSolidBrush(RGB(90, 80, 70));
    HBRUSH hBrush5 = CreateSolidBrush(RGB(150, 220, 90));
    SelectObject(hdc, hBrush3);
    Rectangle(hdc, 300,0 , 1600, 450);
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

std::array<double,2> updatePlayer(double&playerX, double&playerY)
{
    player1.playerDeltaX = sin(player1.playerAngle) * player1.speed* player1.playerDir;
    player1.playerDeltaY = cos(player1.playerAngle) * player1.speed* player1.playerDir;
    //撞墙判断
    if(worldMap.grid[(int)floor(playerY/mapSize)][(int)floor((playerX+ player1.playerDeltaX)/ mapSize)] != 1)
        player1.playerX += player1.playerDeltaX;
    if (worldMap.grid[(int)floor((playerY+ player1.playerDeltaY) / mapSize)][(int)floor(playerX/ mapSize)] != 1)
    player1.playerY += player1.playerDeltaY;

    std::array<double, 2> position = {playerX, playerY};
    return position;
}

void drawPlayerWin(HDC hdc, unsigned long time0,int &count, unsigned long&tolTime)
{
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 100;
    lf.lfWeight = FW_BOLD;
    wcscpy_s(lf.lfFaceName,20, L"Microsoft YaHei");
    HFONT hFont = CreateFontIndirect(&lf);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    if (count == 0)
    {
		tolTime = GetTickCount64() - time0;
        count++;
    }
    unsigned long tolSec = tolTime / 1000;
    int min = tolSec / 60;
    int sec = tolSec % 60;
    if (sec > 9)
        swprintf(str, 20, L"用时: %d分%d秒", min, sec);
    else
        swprintf(str, 20, L"用时: %d分0%d秒", min, sec);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, 0, 0, 1600, 900);
    TextOut(hdc, 550, 400, str, wcslen(str));
    swprintf(str, 20, L"恭喜通关");
    TextOut(hdc, 650, 300, str, wcslen(str));
    DeleteObject(hBrush);
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
    LOGFONT lf1;
    memset(&lf1, 0, sizeof(LOGFONT));
    lf1.lfHeight = 20;
    lf1.lfWeight = FW_BOLD;
    wcscpy_s(lf.lfFaceName, 20, L"Microsoft YaHei");
    HFONT hFont1 = CreateFontIndirect(&lf1);
    HFONT hOldFont1 = (HFONT)SelectObject(hdc, hFont1);
    swprintf(str, 20, L"按 R 键重新开始");
    TextOut(hdc,1400 , 800, str, wcslen(str));
    SelectObject(hdc, hOldFont1);
    DeleteObject(hFont1);

}

void drawTime(HDC hdc, unsigned long time0)
{
    unsigned long time = GetTickCount64()-time0;
    unsigned long tolSec = time / 1000;
    int min = tolSec / 60;
    int sec= tolSec %60;
    if (sec > 9)
        swprintf(str,20, L"用时: %d:%d",min,sec);
    else
        swprintf(str,20, L"用时: %d:0%d", min, sec);

    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 50;
    lf.lfWeight = FW_BOLD;
    wcscpy_s(lf.lfFaceName,20, L"Microsoft YaHei");
    HFONT hFont = CreateFontIndirect(&lf);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    
    TextOut(hdc, 50, 350, str, wcslen(str));
    swprintf(str, 20, L"得分: %d", player1.score);
    TextOut(hdc, 50, 400, str, wcslen(str));
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}
void drawMapPlayer(HDC hdc)
{
    HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 120, 150));
    SelectObject(hdc, hBrush1);
    Ellipse(hdc, 5+ player1.playerX-3,5+ player1.playerY-3, 5+ player1.playerX+3, 5+ player1.playerY+3);
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    MoveToEx(hdc, 5+ player1.playerX, 5+ player1.playerY, NULL);
    LineTo(hdc, 5+ player1.playerX+sin(player1.playerAngle)*8, 5+ player1.playerY+cos(player1.playerAngle)*8);
    DeleteObject(hPen);
}

void drawRay(HDC hdc)
{
    double currentAngle = player1.playerAngle + 0.5;
    //玩家位置向下取整为mapSize的倍数
    int rayStartX = floor(player1.playerX / mapSize) * mapSize;
    int rayStartY = floor(player1.playerY / mapSize) * mapSize;
    
    for (int i = 0; i <1300; i++)
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
            verticalDepth = (rayEndX - player1.playerX) / currentSin;
            rayEndY = player1.playerY + verticalDepth * currentCos;
            int mapTargetX =floor(rayEndX / mapSize);
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
            if (worldMap.grid[mapTargetY][mapTargetX] != 0)
            {
                mapkindX = 1;
                break;
            }
            if (worldMap.grid[mapTargetY][mapTargetX] == 8)
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
            horizontalDepth = (rayEndY - player1.playerY) / currentCos;
            rayEndX = player1.playerX + horizontalDepth * currentSin;
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
            if (worldMap.grid[mapTargetY][mapTargetX] == 1)
            {
                mapkindY = 1;
                break;
            }
            if (worldMap.grid[mapTargetY][mapTargetX] == 8)
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
        depth *= cos(player1.playerAngle - currentAngle);
        int height=8000/(depth+0.001);
        HPEN hPen1 = CreatePen(PS_SOLID, 2, RGB(min(120+endX/3,255), min(120+endY/3,255), 110));
        HPEN hPen2 = CreatePen(PS_SOLID, 2, RGB(min(150+endX/3,255),min(150+endY/3,255),160));
        if(verticalDepth < horizontalDepth)
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen2);
        else
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen1);
       MoveToEx(hdc,  i+300,450-height/2, NULL);
       LineTo(hdc , i+300,450+ height / 2);
       DeleteObject(hPen1);
       DeleteObject(hPen2);
       mapkind = 0;
       mapkindX = 0;
       mapkindY = 0;
        }
       
        if (mapkind == 8)
        {
            depth *= cos(player1.playerAngle - currentAngle);
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

        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(100,150, 50));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        MoveToEx(hdc, 5+player1.playerX, 5+player1.playerY, NULL);
        LineTo(hdc, 5+endX, 5+endY);
        DeleteObject(hPen);
        currentAngle -= 1.0466/1300;
    }
}
    
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
  time0 = GetTickCount64();
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LABYRINTH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABYRINTH));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABYRINTH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABYRINTH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* pMinMaxInfo = (MINMAXINFO*)lParam;
        pMinMaxInfo->ptMinTrackSize.x = WINDOW_WIDTH;
        pMinMaxInfo->ptMinTrackSize.y = WINDOW_HEIGHT;
        pMinMaxInfo->ptMaxTrackSize.x = WINDOW_WIDTH;
        pMinMaxInfo->ptMaxTrackSize.y = WINDOW_HEIGHT;
    }
	case WM_CREATE:
        SetMap();
		// 在窗口创建时启动定时器
		SetTimer(hWnd, 1, 1000/30,NULL);
        SetMenu(hWnd, NULL);
		break;

    case WM_TIMER:
		// 处理定时器消息，重绘窗口
		if (wParam == 1) 
        {
            if (worldMap.grid[(int)floor(player1.playerY / 7)][(int)floor(player1.playerX / 7)])
            { 
				//win = true;
            }
               
            if (Wkey)
            {
                player1.playerDir = 1;
                updatePlayer(player1.playerX, player1.playerY);
            }
            if (Akey)
            {
                player1.playerAngle += 0.05;
            }
            if (Dkey)
            {
                player1.playerAngle += -0.05;
            }
            if (Skey)
            {
                player1.playerDir = -1;
                updatePlayer(player1.playerX, player1.playerY);
            }
            InvalidateRect(hWnd, NULL, FALSE);
            if (win)
            {
                if (Rkey)
                {
                    KillTimer(hWnd, 1);
                    SetTimer(hWnd, 1, 1000 / 30, NULL);
                    player1.playerX = 10;
                    player1.playerY = 10;
                    win = false;
                    count = 0;
                    tolTime = 0;
                    time0 = GetTickCount64();
                }
            }
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_KEYDOWN:
    { 
        downKey = wParam;
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
        break;
    }
    case WM_KEYUP:
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
        break;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            //缓冲绘图
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmMem = CreateCompatibleBitmap(hdc,1600, 900);
            HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
            //==============================================================================
            if (!win)
            {
				FillRect(hdcMem, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));
				showMap(hdcMem, floor(player1.playerX / mapSize), floor(player1.playerY / mapSize));
				drawMapPlayer(hdcMem);
				drawRay(hdcMem);
                player1.CheckCollision(&worldMap);
                //wwwwwwblinky.Update();
				drawTime(hdcMem, time0);
            }
            
            if (win)
                drawPlayerWin(hdcMem, time0,count,tolTime);
            //==============================================================================
            BitBlt(hdc, 0, 0, 1600,900, hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem, hbmOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
