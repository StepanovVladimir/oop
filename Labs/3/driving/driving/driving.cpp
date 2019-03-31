#include "pch.h"
#include "Car.h"
#include <iostream>

using namespace std;

void PrintInfo(const CCar &car)
{
	cout << "Engine: " << car.GetEngineCondition() << endl;
	cout << "Direction of move: " << car.GetDirOfMove() << endl;
	cout << "Speed: " << car.GetSpeed() << endl;
	cout << "Gear: " << car.GetGear() << endl;
}

void TryTurnOffEngine(CCar &car)
{
	if (!car.TurnOffEngine())
	{
		cout << "You cannot turn off the engine. Gear and speed must be zero\n";
	}
}

bool ReadNumber(int &num)
{
	string str;
	cin >> str;
	try
	{
		num = stoi(str);
	}
	catch (const invalid_argument &)
	{
		return false;
	}
	catch (const out_of_range &)
	{
		return false;
	}
	return true;
}

void TrySetGear(CCar &car)
{
	int gear;
	if (!ReadNumber(gear))
	{
		cout << "Unexpected command argument \"SetGear\". Input in the form \"SetGear <integer>\" was expected.\n";
	}
	else try
	{
		car.SetGear(gear);
	}
	catch (const string &err)
	{
		cout << err;
	}
}

void TrySetSpeed(CCar &car)
{
	int speed;
	if (!ReadNumber(speed))
	{
		cout << "Unexpected command argument \"SetSpeed\". Input in the form \"SetSpeed <integer>\" was expected.\n";
	}
	else if (!car.SetSpeed(speed))
	{
		cout << "You cannot set this speed because it outside the speed range for this gear.\n";
	}
}

int main()
{
	CCar car;
	string command;
	cout << "Enter \"Info\", \"EngineOn\", \"EngineOff\", \"SetGear <integer>\", \"SetSpeed <integer>\" or \"Exit\".\n";
	while (cin >> command)
	{
		if (command == "Info")
		{
			PrintInfo(car);
		}
		else if (command == "EngineOn")
		{
			car.TurnOnEngine();
		}
		else if (command == "EngineOff")
		{
			TryTurnOffEngine(car);
		}
		else if (command == "SetGear")
		{
			TrySetGear(car);
		}
		else if (command == "SetSpeed")
		{
			TrySetSpeed(car);
		}
		else if (command == "Exit")
		{
			break;
		}
		else
		{
			cout << "Unexpected command.\n";
		}
	}
}