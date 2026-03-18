#pragma once

class GameStateManager
{
public:
	static int lives;
	static int coins;

	static void ResetGame()
	{
		lives = 3;
		coins = 0;
	}

	static void LoseLife()
	{
		lives--;
		if (lives < 0)
			lives = 0;
	}

	static int GetLives()
	{
		return lives;
	}

	static void SetLives(int count)
	{
		lives = count;
	}
};
