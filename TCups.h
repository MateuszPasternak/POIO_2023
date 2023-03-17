#pragma once
#include <iostream>
#include <vector>

#include "TSubstance.h"

class TCups
{
	std::vector<TSubstance> substances;
	std::vector<double> volumes;
	std::vector<double> masses;
	double volume_sum, mass_sum;

public:
	TCups();
	void add(TSubstance substance, double volume_in_ml);
	void add(std::string name, double volume_in_ml);
	void add_2(std::string name, double percent, std::string type="volume");
	void mixup(TCups *cup);
	void show();

private:
	void print_coe_vol();
	void print_coe_mass();
	void clear_cup();
	int get_substance_id(std::vector <TSubstance> subs_buff, std::string name, bool alert = true);
};

