#include "pch.h"
#include "CPerson.h"
#include "CRacer.h"
#include "CPoliceMan.h"
#include "CTaxi.h"
#include "CPoliceCar.h"
#include "CRacingCar.h"
#include "CBus.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Press Enter to read";

	cin.get();
	shared_ptr<IPoliceMan> policeMan1 = make_shared<CPoliceMan>("John Smith", "Northwest police station");
	CPoliceCar policeCar(5, MakeOfTheCar::FORD);
	policeCar.AddPassenger(policeMan1);
	cout << "Police officer " << policeMan1->GetName() << " from the " << policeMan1->GetDepartmentName()
		<< " got into his service five-seater police car brand Ford.";

	cin.get();
	shared_ptr<IPoliceMan> policeMan2 = make_shared<CPoliceMan>("Jim Clark", "Southeast police station");
	policeCar.AddPassenger(policeMan2);
	cout << "His friend police officer " << policeMan2->GetName() << " from the "
		<< policeMan2->GetDepartmentName() << " got into his car.";

	cin.get();
	policeCar.RemovePassenger(1);
	cout << "The police had a quarrelled and policeman Jim Clark got out of the car.";

	cin.get();
	shared_ptr<IPerson> person = make_shared<CPerson>("Raja Gandhi");
	shared_ptr<IRacer> racer = make_shared<CRacer>("Michael Schumacher", 20);
	CTaxi taxi(2, MakeOfTheCar::TOYOTA);
	taxi.AddPassenger(person);
	taxi.AddPassenger(racer);
	cout << "He stopped a two-seater taxi brand Toyota, which is driven by a native of India, "
		<< person->GetName() << ", driving the racer " << racer->GetName()
		<< " to the stadium, which in 15 minutes should begin the world Cup.";

	cin.get();
	taxi.RemovePassenger(0);
	taxi.AddPassenger(policeMan2);
	cout << "\"Convincing\" the taxi driver with his service weapon to leave the car, police Jim "
		<< "took a taxi to the driver's seat and agreed to drive his favorite driver to the stadium.";

	cin.get();
	try
	{
		taxi.AddPassenger(person);
	}
	catch (const logic_error &err)
	{
		cout << "The taxi driver tried to get back in his car but was unable to do so since "
			<< err.what() << '.';
	}

	return 0;
}