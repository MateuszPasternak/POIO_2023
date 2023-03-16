#include "TSubstance.h"

TSubstance::TSubstance(std::string name, double Ro)
{
	this->name = name;
	this->Ro = Ro;
}

std::string TSubstance::get_name()
{
	return name;
}

double TSubstance::get_Ro()
{
	return Ro;
}

std::vector<TSubstance> substancje =
{
	TSubstance{"woda", 997.8},
	TSubstance{"mleko", 1030.0},
	TSubstance{"oliwa", 920.0},
	TSubstance{"krew", 1050.0}
};