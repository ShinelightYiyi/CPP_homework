#pragma once  
#include "Scene.h"

extern Scene* gameScene;

class SceneManager
{
public:
	Scene* currentScene;

	void CreateGhost()
	{
		currentScene->CreateGhost();
	}

	void Update()
	{
		currentScene->Update();
	}

	void Draw(HDC hdc, RECT& rect, unsigned long time0)
	{
		currentScene->Draw(hdc, rect, time0);
	}

	void InputDown(WPARAM downKey)
	{
		currentScene->InputDown(downKey);
	}

	void InputUp(WPARAM upKey)
	{
		currentScene->InputUp(upKey);
	}

	void SetCurrentScene(Scene* scene)
	{
		currentScene = scene;
	}

	void ChangeScene(SceneType o)
	{
		switch (o)
		{
		case SceneType::TheGameScene: currentScene = gameScene; break;
		case SceneType::TheMainMnue: break;
		case SceneType::TheGameOverScene:  break;
		}
	}

};
