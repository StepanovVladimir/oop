#include "pch.h"
#include "Car.h"

using namespace std;

CCar::CCar()
	:m_engineIsOn(false),
	m_dirOfMove(DirOfMove::Stop),
	m_speed(0),
	m_gear(0)
{
}

void CCar::TurnOnEngine()
{
	m_engineIsOn = true;
}

bool CCar::TurnOffEngine()
{
	if (m_gear != 0 || m_speed != 0)
	{
		return false;
	}
	m_engineIsOn = false;
	return true;
}

bool CCar::TrySetPositiveGear(int gear, int lowerBound, int upperBound)
{
	if (!m_engineIsOn || m_dirOfMove == DirOfMove::Back || m_speed < lowerBound || m_speed > upperBound)
	{
		return false;
	}
	m_gear = gear;
	return true;
}

bool CCar::SetGear(int gear)
{
	switch (gear)
	{
	case -1:
		if (m_gear != gear && (!m_engineIsOn || m_speed != 0))
		{
			return false;
		}
		m_gear = gear;
		return true;

	case 0:
		m_gear = gear;
		return true;

	case 1:
		return TrySetPositiveGear(gear, 0, 30);

	case 2:
		return TrySetPositiveGear(gear, 20, 50);

	case 3:
		return TrySetPositiveGear(gear, 30, 60);

	case 4:
		return TrySetPositiveGear(gear, 40, 90);

	case 5:
		return TrySetPositiveGear(gear, 50, 150);

	default:
		return false;
	}
}

bool CCar::TrySetSpeed(int speed, int lowerBound, int upperBound, DirOfMove dir)
{
	if (speed < lowerBound || speed > upperBound)
	{
		return false;
	}
	m_speed = speed;
	if (m_speed == 0)
	{
		m_dirOfMove = DirOfMove::Stop;
	}
	else
	{
		m_dirOfMove = dir;
	}
	return true;
}

bool CCar::SetSpeed(int speed)
{
	switch (m_gear)
	{
	case -1:
		return TrySetSpeed(speed, 0, 20, DirOfMove::Back);

	case 0:
		return TrySetSpeed(speed, 0, 0, DirOfMove::Stop);

	case 1:
		return TrySetSpeed(speed, 0, 30, DirOfMove::Forward);

	case 2:
		return TrySetSpeed(speed, 20, 50, DirOfMove::Forward);

	case 3:
		return TrySetSpeed(speed, 30, 60, DirOfMove::Forward);

	case 4:
		return TrySetSpeed(speed, 40, 90, DirOfMove::Forward);

	case 5:
		return TrySetSpeed(speed, 50, 150, DirOfMove::Forward);

	default:
		return false;
	}
}

string CCar::GetEngineCondition() const
{
	if (m_engineIsOn)
	{
		return "On";
	}
	else
	{
		return "Off";
	}
}

string CCar::GetDirOfMove() const
{
	switch (m_dirOfMove)
	{
	case DirOfMove::Forward:
		return "Forward";

	case DirOfMove::Back:
		return "Back";

	default:
		return "Stop";
	}
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}