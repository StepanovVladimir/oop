#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../driving/Car.h"

using namespace std;

TEST_CASE("Car constructor and getters tests")
{
	CCar car;

	CHECK(car.EngineIsOn() == false);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("TurnOnEngine tests")
{
	CCar car;

	car.TurnOnEngine();

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("SetGear and SetSpeed when the engine is off tests")
{
	CCar car;

	try
	{
		car.SetGear(0);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}
	try
	{
		car.SetGear(-1);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}
	try
	{
		car.SetGear(1);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(car.SetSpeed(0));

	CHECK(car.EngineIsOn() == false);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("SetGear and SetSpeed on reverse gear tests")
{
	CCar car;
	car.TurnOnEngine();

	CHECK(!car.SetSpeed(10));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);

	try
	{
		car.SetGear(-1);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}

	CHECK(!car.SetSpeed(21));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == -1);
	CHECK(car.GetSpeed() == 0);

	CHECK(car.SetSpeed(20));

	try
	{
		car.SetGear(-1);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}
	try
	{
		car.SetGear(-2);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}
	try
	{
		car.SetGear(1);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Back);
	CHECK(car.GetGear() == -1);
	CHECK(car.GetSpeed() == 20);

	try
	{
		car.SetGear(0);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}
	try
	{
		car.SetGear(1);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}
	try
	{
		car.SetGear(-1);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(car.SetSpeed(10));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Back);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 10);

	CHECK(car.SetSpeed(0));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("SetGear and SetSpeed on first gear tests")
{
	CCar car;
	car.TurnOnEngine();

	try
	{
		car.SetGear(1);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}

	CHECK(!car.SetSpeed(31));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 0);

	CHECK(car.SetSpeed(30));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 30);
}

TEST_CASE("SetGear and SetSpeed on second gear tests")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(19);

	try
	{
		car.SetGear(2);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 19);

	car.SetSpeed(20);

	try
	{
		car.SetGear(2);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}

	CHECK(!car.SetSpeed(51));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 2);
	CHECK(car.GetSpeed() == 20);

	CHECK(car.SetSpeed(50));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 2);
	CHECK(car.GetSpeed() == 50);
}

TEST_CASE("SetGear and SetSpeed on third gear tests")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(29);

	try
	{
		car.SetGear(3);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 29);

	car.SetSpeed(30);

	try
	{
		car.SetGear(3);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}

	CHECK(!car.SetSpeed(61));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 3);
	CHECK(car.GetSpeed() == 30);

	CHECK(car.SetSpeed(60));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 3);
	CHECK(car.GetSpeed() == 60);
}

TEST_CASE("SetGear and SetSpeed on fourth gear tests")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(39);

	try
	{
		car.SetGear(4);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 2);
	CHECK(car.GetSpeed() == 39);

	car.SetSpeed(40);

	try
	{
		car.SetGear(4);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}

	CHECK(!car.SetSpeed(91));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 4);
	CHECK(car.GetSpeed() == 40);

	CHECK(car.SetSpeed(90));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 4);
	CHECK(car.GetSpeed() == 90);
}

TEST_CASE("SetGear and SetSpeed on fifth gear tests")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(49);

	try
	{
		car.SetGear(5);
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 2);
	CHECK(car.GetSpeed() == 49);

	car.SetSpeed(50);

	try
	{
		car.SetGear(5);
		CHECK(true);
	}
	catch (const string &)
	{
		CHECK(false);
	}

	CHECK(!car.SetSpeed(151));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 5);
	CHECK(car.GetSpeed() == 50);

	CHECK(car.SetSpeed(150));

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 5);
	CHECK(car.GetSpeed() == 150);
}

TEST_CASE("TurnOffEngine tests")
{
	CCar car;

	CHECK(car.TurnOffEngine());

	CHECK(car.EngineIsOn() == false);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);

	car.TurnOnEngine();

	car.SetGear(1);

	CHECK(!car.TurnOffEngine());

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 0);

	car.SetSpeed(10);

	CHECK(!car.TurnOffEngine());

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 10);

	car.SetGear(0);

	CHECK(!car.TurnOffEngine());

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Forward);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 10);

	car.SetSpeed(0);

	CHECK(car.TurnOffEngine());

	CHECK(car.EngineIsOn() == false);
	CHECK(car.GetDirOfMove() == CCar::DirOfMove::Stop);
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}
