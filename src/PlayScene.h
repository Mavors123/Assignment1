#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Background.h"
#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Projectile.h"
#include "Stormtrooper.h"
#include "Wookie.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void calculateSceneScale();
	void updateLabels();
	void runSimulation();
	void resetScene();

private:
	// IMGUI Function
	void GUI_Function() ;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Background* m_pBackground;

	Wookie* m_pWookie;
	Stormtrooper* m_pStormtrooper;
	Projectile* m_pProjectile;

	float m_InitialLinearVelocity = 95.f;
	float m_Distance = 485.f;
	float m_Angle = 45.f;
	float m_Mass = 2.2f;
	float m_G = 9.8f;

	bool bRunning = false;

	Label* m_pMassLabel;
	Label* m_pPositionLabel;
	Label* m_pAccelerationLabel;
	Label* m_pVelocityLabel;
	
	// UI Items
	Button* m_pResetButton;
	Button* m_pRunButton;
	Label* m_pInstructionsLabel;
	float m_Scale = 0.0115f;
};

#endif /* defined (__PLAY_SCENE__) */