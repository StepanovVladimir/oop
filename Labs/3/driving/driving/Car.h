#pragma once

#include <string>

class CCar
{
public:
	CCar();

	void TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

	std::string GetEngineCondition() const;
	std::string GetDirOfMove() const;
	int GetGear() const;
	int GetSpeed() const;

private:
	enum struct DirOfMove
	{
		Forward,
		Back,
		Stop
	};

	bool m_engineIsOn;
	DirOfMove m_dirOfMove;
	int m_gear;
	int m_speed;

	bool TrySetPositiveGear(int gear, int lowerBound, int upperBound);
	bool TrySetSpeed(int speed, int lowerBound, int upperBound, DirOfMove dir);
};