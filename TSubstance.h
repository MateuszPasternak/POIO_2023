#pragma once
#include <iostream>
#include <vector>

class TSubstance
{
	std::string name;
	double Ro;

public:
	TSubstance(std::string name, double Ro);

	std::string get_name();
	double get_Ro();
};

extern std::vector<TSubstance> substancje;