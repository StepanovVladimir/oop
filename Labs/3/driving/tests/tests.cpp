#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../driving/Car.h"

using namespace std;

TEST_CASE("Car constructor and getters tests")
{
	CCar car;

	CHECK(car.GetEngineCondition() == "Off");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("TurnOnEngine tests")
{
	CCar car;

	car.TurnOnEngine();

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("SetGear and SetSpeed tests")
{
	CCar car;

	CHECK(car.SetGear(0));
	CHECK(!car.SetGear(1));

	CHECK(car.SetSpeed(0));

	CHECK(car.GetEngineCondition() == "Off");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);

	car.TurnOnEngine();

	CHECK(!car.SetSpeed(10));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);

	CHECK(car.SetGear(-1));

	CHECK(!car.SetSpeed(21));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == -1);
	CHECK(car.GetSpeed() == 0);

	CHECK(car.SetSpeed(20));

	CHECK(car.SetGear(-1));
	CHECK(!car.SetGear(-2));
	CHECK(!car.SetGear(1));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Back");
	CHECK(car.GetGear() == -1);
	CHECK(car.GetSpeed() == 20);

	CHECK(car.SetGear(0));
	CHECK(!car.SetGear(1));
	CHECK(!car.SetGear(-1));

	CHECK(!car.SetSpeed(10));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Back");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 20);

	CHECK(car.SetSpeed(0));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);

	CHECK(car.SetGear(1));

	CHECK(!car.SetSpeed(31));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 0);

	CHECK(car.SetSpeed(19));

	CHECK(!car.SetGear(2));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 19);

	CHECK(car.SetSpeed(29));

	CHECK(car.SetGear(2));
	CHECK(!car.SetGear(3));

	CHECK(!car.SetSpeed(51));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 2);
	CHECK(car.GetSpeed() == 29);

	CHECK(car.SetSpeed(39));

	CHECK(car.SetGear(3));
	CHECK(!car.SetGear(4));

	CHECK(!car.SetSpeed(61));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 3);
	CHECK(car.GetSpeed() == 39);

	CHECK(car.SetSpeed(49));

	CHECK(car.SetGear(4));
	CHECK(!car.SetGear(5));

	CHECK(!car.SetSpeed(91));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 4);
	CHECK(car.GetSpeed() == 49);

	CHECK(car.SetSpeed(90));

	CHECK(car.SetGear(5));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 5);
	CHECK(car.GetSpeed() == 90);

	CHECK(car.SetSpeed(150));
	CHECK(!car.SetSpeed(151));

	CHECK(!car.SetGear(6));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 5);
	CHECK(car.GetSpeed() == 150);

	CHECK(car.SetSpeed(50));

	CHECK(car.SetGear(2));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 2);
	CHECK(car.GetSpeed() == 50);

	CHECK(car.SetGear(0));

	CHECK(!car.SetSpeed(10));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 50);

	CHECK(car.SetSpeed(0));

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("TurnOffEngine tests")
{
	CCar car;

	CHECK(car.TurnOffEngine());

	CHECK(car.GetEngineCondition() == "Off");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);

	car.TurnOnEngine();

	car.SetGear(1);

	CHECK(!car.TurnOffEngine());

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 0);

	car.SetSpeed(10);

	CHECK(!car.TurnOffEngine());

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 1);
	CHECK(car.GetSpeed() == 10);

	car.SetGear(0);

	CHECK(!car.TurnOffEngine());

	CHECK(car.GetEngineCondition() == "On");
	CHECK(car.GetDirOfMove() == "Forward");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 10);

	car.SetSpeed(0);

	CHECK(car.TurnOffEngine());

	CHECK(car.GetEngineCondition() == "Off");
	CHECK(car.GetDirOfMove() == "Stop");
	CHECK(car.GetGear() == 0);
	CHECK(car.GetSpeed() == 0);
}