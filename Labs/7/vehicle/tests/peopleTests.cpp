#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../vehicle/CPerson.h"
#include "../vehicle/CRacer.h"
#include "../vehicle/CPoliceMan.h"

TEST_CASE("Person tests")
{
	CPerson person("Andrey");
	CHECK(person.GetName() == "Andrey");
}

TEST_CASE("Racer tests")
{
	CRacer racer("Alexander", 5);
	CHECK(racer.GetName() == "Alexander");
	CHECK(racer.GetAwardsCount() == 5);
}

TEST_CASE("Police man tests")
{
	CPoliceMan policeMan("Maxim", "Northwest police station");
	CHECK(policeMan.GetName() == "Maxim");
	CHECK(policeMan.GetDepartmentName() == "Northwest police station");
}