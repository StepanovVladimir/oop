#pragma once

#include <string>

class CCar
{
public:
	enum struct DirOfMove
	{
		Forward,
		Back,
		Stop
	};

	CCar();

	void TurnOnEngine();
	bool TurnOffEngine();
	void SetGear(int gear);
	bool SetSpeed(int speed);

	bool EngineIsOn() const;
	DirOfMove GetDirOfMove() const;
	int GetGear() const;
	int GetSpeed() const;

private:
	bool m_engineIsOn;
	DirOfMove m_dirOfMove;
	int m_gear;
	int m_speed;

	void TrySetPositiveGear(int gear, int lowerBound, int upperBound);
	bool TrySetSpeed(int speed, int lowerBound, int upperBound, DirOfMove dir);
};
