#pragma once

#include <glm/vec2.hpp>
#include <array>
#include <memory>

class Tank;

class Game {
public:
	Game(const glm::ivec2 windowSize);
	~Game();

	void update(const uint64_t delta);
	void render();
	void setKey(const int key, const int action);
	bool init();

private:

	std::array <bool, 349> m_keys;

	enum class EGameState {
		Active, 
		Pause
	};

	glm::ivec2 m_WindowSize;
	EGameState m_currentGameState;

	std::unique_ptr<Tank> m_pTank;
};