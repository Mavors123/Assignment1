#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include <glm/gtx/string_cast.hpp>

#include "imgui.h"
#include "imgui_sdl.h"
#include "Projectile.h"
#include "Renderer.h"
#include "Stormtrooper.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{

	drawDisplayList();

	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	updateLabels();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	//
	// // handle player movement with GameController
	// if (SDL_NumJoysticks() > 0)
	// {
	// 	if (EventManager::Instance().getGameController(0) != nullptr)
	// 	{
	// 		const auto deadZone = 10000;
	// 		if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
	// 		{
	// 			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
	// 			m_playerFacingRight = true;
	// 		}
	// 		else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
	// 		{
	// 			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
	// 			m_playerFacingRight = false;
	// 		}
	// 		else
	// 		{
	// 			if (m_playerFacingRight)
	// 			{
	// 				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
	// 			}
	// 			else
	// 			{
	// 				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
	// 			}
	// 		}
	// 	}
	// }

	//
	// // handle player movement if no Game Controllers found
	// if (SDL_NumJoysticks() < 1)
	// {
	// 	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	// 	{
	// 		m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
	// 		m_playerFacingRight = false;
	// 	}
	// 	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	// 	{
	// 		m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
	// 		m_playerFacingRight = true;
	// 	}
	// 	else
	// 	{
	// 		if (m_playerFacingRight)
	// 		{
	// 			m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
	// 		}
	// 		else
	// 		{
	// 			m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
	// 		}
	// 	}
	// }
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pBackground = new Background();
	const auto Height = Config::SCREEN_HEIGHT;
	const auto Width = Config::SCREEN_WIDTH;

	m_pBackground->setWidth(Width);
	m_pBackground->setHeight(Height);
	addChild(m_pBackground);

	m_pWookie = new Wookie();
	m_pWookie->getTransform()->position = glm::vec2(100.0f, 400.0f);
	addChild(m_pWookie);
	
	m_pStormtrooper = new Stormtrooper();
	m_pStormtrooper->getTransform()->position = glm::vec2(700.0f, 400.0f);
	addChild(m_pStormtrooper);

	m_pProjectile = new Projectile();
	addChild(m_pProjectile);
	
	// Plane Sprite
	// m_pPlaneSprite = new Plane();
	// addChild(m_pPlaneSprite);
	//
	// // Player Sprite
	// m_pPlayer = new Player();
	// addChild(m_pPlayer);
	// m_playerFacingRight = true;

	// Back Button
	m_pResetButton = new Button("../Assets/textures/resetButton.png", "backButton", BACK_BUTTON);
	m_pResetButton->getTransform()->position = glm::vec2(300.0f, 50.0f);
	m_pResetButton->addEventListener(CLICK, [&]()-> void
	{
		std::cout << "Resetting the scene";
		resetScene();
		// m_pResetButton->setActive(false);
		// TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pResetButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pResetButton->setAlpha(128);
	});

	m_pResetButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pResetButton->setAlpha(255);
	});
	addChild(m_pResetButton);

	// Next Button
	m_pRunButton = new Button("../Assets/textures/runButton.png", "nextButton", NEXT_BUTTON);
	m_pRunButton->getTransform()->position = glm::vec2(500.0f, 50.0f);
	m_pRunButton->addEventListener(CLICK, [&]()-> void
	{
		std::cout << "Running sim";
		runSimulation();
		// m_pRunButton->setActive(false);
		// TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pRunButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pRunButton->setAlpha(128);
	});

	m_pRunButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pRunButton->setAlpha(255);
	});

	addChild(m_pRunButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 100.0f);

	m_pMassLabel = new Label(std::to_string(m_Mass).c_str(), "Consolas");
	m_pMassLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 120.0f);
	
	m_pAccelerationLabel = new Label(glm::to_string(m_pProjectile->getRigidBody()->acceleration), "Consolas");
	m_pAccelerationLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 140.0f);
	
	m_pPositionLabel = new Label(glm::to_string(m_pProjectile->getTransform()->position), "Consolas");
	m_pPositionLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 160.0f);
	
	m_pVelocityLabel = new Label(glm::to_string(m_pProjectile->getRigidBody()->velocity), "Consolas");
	m_pVelocityLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 180.0f);

	addChild(m_pInstructionsLabel);
	addChild(m_pMassLabel);
	addChild(m_pAccelerationLabel);
	addChild(m_pPositionLabel);
	addChild(m_pVelocityLabel);
}

void PlayScene::calculateSceneScale() {
	const auto spriteDistance =  (m_pStormtrooper->getTransform()->position.x - m_pWookie->getTransform()->position.x);
	m_Scale = m_Distance / spriteDistance;
}

void PlayScene::updateLabels() {
	m_pMassLabel->setText("Mass: " + std::to_string(m_Mass));
	m_pAccelerationLabel->setText("Acceleration: " + glm::to_string(m_pProjectile->getRigidBody()->acceleration / m_Scale));

	const auto Ratio = (m_pProjectile->getTransform()->position.x - m_pWookie->getTransform()->position.x) / (m_pStormtrooper->getTransform()->position.x - m_pWookie->getTransform()->position.x);
	const auto Distance = Ratio * m_Distance;
	
	m_pPositionLabel->setText("Distance: " + std::to_string(Distance));
	m_pVelocityLabel->setText("Velocity: " + glm::to_string(m_pProjectile->getRigidBody()->velocity / m_Scale));
}

void PlayScene::runSimulation() {
	bRunning = true;

	// calculateSceneScale();
	
	// Reset the position.
	m_pProjectile->getTransform()->position = glm::vec2(m_pWookie->getTransform()->position.x, m_pWookie->getTransform()->position.y);

	// Calculate the acceleration.
	m_pProjectile->getRigidBody()->acceleration = glm::vec2(0.0f, m_G) * m_Scale;

	// Calculate start velocity vector (based on the angle).
	const auto a =  m_G * m_Distance / (m_InitialLinearVelocity*m_InitialLinearVelocity);
	const auto s = sinf(a);
	m_Angle = (1.0f / 2.0f) * (1.0f / s);
	
	std::cout << "Angle: " << m_Angle;
	
	m_pProjectile->getRigidBody()->velocity = glm::vec2(m_InitialLinearVelocity * cosf(m_Angle), - m_InitialLinearVelocity * sinf(m_Angle)) * m_Scale;

	std::cout << "Vel x: " << m_pProjectile->getRigidBody()->velocity.x << " vel y: " << m_pProjectile->getRigidBody()->velocity.y;  
	
	m_pProjectile->getRigidBody()->mass = m_Mass;
}

void PlayScene::resetScene() {
	bRunning = false;

	m_pProjectile->getRigidBody()->acceleration = glm::vec2(0,0);
	m_pProjectile->getRigidBody()->velocity = glm::vec2(0, 0);
	m_pProjectile->getRigidBody()->mass = m_Mass;
	m_pProjectile->getTransform()->position = glm::vec2(100, 100);
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	ImGui::ShowDemoWindow();
	
	ImGui::Begin("Sim Options", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	ImGui::Separator();
	
	// Initial velocity
	static float vVelocity[1] = { 100.f };
	if(ImGui::SliderFloat("Initial Velocity", vVelocity, 0.50f, 100.0f))
	{
		m_InitialLinearVelocity = vVelocity[0];
		std::cout << vVelocity[0] << std::endl;
		std::cout << "---------------------------\n";
	}

	// Distance
	static float vDistance[1] = { 100.f };
	if(ImGui::SliderFloat("Distance", vDistance, 50.0f, 500.0f))
	{
		m_Distance = vDistance[0];
		std::cout << vDistance[0] << std::endl;
		std::cout << "---------------------------\n";
	}

	// vAngle
	static float vMass[1] = { 2.2f };
	if(ImGui::SliderFloat("Mass", vMass, 0.5f, 5.0f))
	{
		m_Mass = vMass[0];
		std::cout << vMass[0] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
