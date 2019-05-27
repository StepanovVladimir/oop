#include "../../../../catch2/catch.hpp"
#include "../vehicle/CPerson.h"
#include "../vehicle/CRacer.h"
#include "../vehicle/CPoliceMan.h"
#include "../vehicle/CTaxi.h"
#include "../vehicle/CPoliceCar.h"
#include "../vehicle/CRacingCar.h"
#include "../vehicle/CBus.h"

using namespace std;

TEST_CASE("Taxi tests")
{
	CTaxi taxi(3, MakeOfTheCar::BMW);
	CHECK(taxi.GetMakeOfTheCar() == MakeOfTheCar::BMW);
	CHECK(taxi.GetPlaceCount() == 3);

	CHECK(taxi.GetPassengerCount() == 0);
	CHECK(taxi.IsEmpty());
	CHECK_FALSE(taxi.IsFull());
}

TEST_CASE("Taxi add passenger tests")
{
	CTaxi taxi(3, MakeOfTheCar::BMW);

	shared_ptr<IPerson> person1 = make_shared<CPerson>("Ivan");
	taxi.AddPassenger(person1);

	CHECK(taxi.GetPassenger(0).GetName() == "Ivan");
	CHECK(taxi.GetPassengerCount() == 1);
	CHECK_FALSE(taxi.IsEmpty());
	CHECK_FALSE(taxi.IsFull());

	shared_ptr<IRacer> racer = make_shared<CRacer>("Artem", 5);
	shared_ptr<IPoliceMan> policeMan = make_shared<CPoliceMan>("Dmitry", "Northwest police station");
	taxi.AddPassenger(racer);
	taxi.AddPassenger(policeMan);

	CHECK(taxi.GetPassenger(1).GetName() == "Artem");
	CHECK(taxi.GetPassenger(2).GetName() == "Dmitry");
	CHECK(taxi.GetPassengerCount() == 3);
	CHECK_FALSE(taxi.IsEmpty());
	CHECK(taxi.IsFull());

	shared_ptr<IPerson> person2 = make_shared<CPerson>("Vasya");
	CHECK_THROWS_AS(taxi.AddPassenger(person2), logic_error);
}

TEST_CASE("Taxi remove passenger tests")
{
	CTaxi taxi(3, MakeOfTheCar::BMW);
	shared_ptr<IPerson> person = make_shared<CPerson>("Ivan");
	shared_ptr<IRacer> racer = make_shared<CRacer>("Artem", 5);
	shared_ptr<IPoliceMan> policeMan = make_shared<CPoliceMan>("Dmitry", "Northwest police station");
	taxi.AddPassenger(person);
	taxi.AddPassenger(racer);
	taxi.AddPassenger(policeMan);

	taxi.RemovePassenger(1);

	CHECK(taxi.GetPassenger(0).GetName() == "Ivan");
	CHECK(taxi.GetPassenger(1).GetName() == "Dmitry");
	CHECK(taxi.GetPassengerCount() == 2);
	CHECK_FALSE(taxi.IsEmpty());
	CHECK_FALSE(taxi.IsFull());

	taxi.RemoveAllPassengers();

	CHECK(taxi.GetPassengerCount() == 0);
	CHECK(taxi.IsEmpty());
	CHECK_FALSE(taxi.IsFull());
}

TEST_CASE("Police car tests")
{
	CPoliceCar policeCar(4, MakeOfTheCar::FORD);
	
	CHECK(policeCar.GetMakeOfTheCar() == MakeOfTheCar::FORD);
	CHECK(policeCar.GetPlaceCount() == 4);

	shared_ptr<IPoliceMan> policeMan = make_shared<CPoliceMan>("Dmitry", "Northwest police station");
	policeCar.AddPassenger(policeMan);

	CHECK(policeCar.GetPassenger(0).GetName() == "Dmitry");
}

TEST_CASE("Racing car tests")
{
	CRacingCar racingCar(2, MakeOfTheCar::FERRARI);

	CHECK(racingCar.GetMakeOfTheCar() == MakeOfTheCar::FERRARI);
	CHECK(racingCar.GetPlaceCount() == 2);

	shared_ptr<IRacer> racer = make_shared<CRacer>("Artem", 5);
	racingCar.AddPassenger(racer);

	CHECK(racingCar.GetPassenger(0).GetName() == "Artem");
}

TEST_CASE("Bus tests")
{
	CBus bus(20);

	CHECK(bus.GetPlaceCount() == 20);

	shared_ptr<IPerson> person = make_shared<CPerson>("Ivan");
	shared_ptr<IRacer> racer = make_shared<CRacer>("Artem", 5);
	shared_ptr<IPoliceMan> policeMan = make_shared<CPoliceMan>("Dmitry", "Northwest police station");
	bus.AddPassenger(person);
	bus.AddPassenger(racer);
	bus.AddPassenger(policeMan);

	CHECK(bus.GetPassenger(0).GetName() == "Ivan");
	CHECK(bus.GetPassenger(1).GetName() == "Artem");
	CHECK(bus.GetPassenger(2).GetName() == "Dmitry");
}