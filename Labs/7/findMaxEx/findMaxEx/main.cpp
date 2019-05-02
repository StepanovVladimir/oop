#include "pch.h"
#include "Finder.h"
#include "Sportsman.h"
#include <iostream>
#include <sstream>

using namespace std;

Sportsman GetSportsman(const string &inStr)
{
	istringstream inStrm(inStr);
	Sportsman sportsman;
	inStrm >> sportsman.firstName >> sportsman.lastName >> sportsman.height >> sportsman.weight;
	if (!inStrm)
	{
		throw runtime_error("Invalid input string");
	}
	return sportsman;
}

vector<Sportsman> GetSportsmans()
{
	vector<Sportsman> sportsmans;
	string inStr;
	while (getline(cin, inStr))
	{
		try
		{
			sportsmans.push_back(GetSportsman(inStr));
		}
		catch (const runtime_error &exc)
		{
			cout << exc.what() << endl;
		}
	}
	return sportsmans;
}

void PrintSportsmanWithMaxHeight(const vector<Sportsman> &sportsmans)
{
	Sportsman sportsman;
	if (FindMax(sportsmans, sportsman, LessByHeight))
	{
		cout << "Sportsman with max height: " << sportsman.firstName << ' ' << sportsman.lastName << ' ';
		cout << sportsman.height << ' ' << sportsman.weight << endl;
	}
}

void PrintSportsmanWithMaxWeight(const vector<Sportsman> &sportsmans)
{
	Sportsman sportsman;
	if (FindMax(sportsmans, sportsman, LessByWeight))
	{
		cout << "Sportsman with max weight: " << sportsman.firstName << ' ' << sportsman.lastName << ' ';
		cout << sportsman.height << ' ' << sportsman.weight << endl;
	}
}

int main()
{
	vector<Sportsman> sportsmans = GetSportsmans();
	Sportsman sportsmanWithMaxHeight, sportsmanWithMaxWeight;
	PrintSportsmanWithMaxHeight(sportsmans);
	PrintSportsmanWithMaxWeight(sportsmans);
}