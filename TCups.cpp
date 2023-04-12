#include "TCups.h"

TCups::TCups()
{
	this->volume_sum = 0;
	this->mass_sum = 0;
	this->substances.clear();
	this->volumes.clear();
	this->masses.clear();
}

void TCups::add(TSubstance substance, double volume_in_ml)
{
	std::string new_name = substance.get_name();
	int substance_pos_in_cup = get_substance_id(this->substances, new_name, false);
	double mass = volume_in_ml * substance.get_Ro() /1000;  //tu by³ bugg powinno byæ /1000 nie *1000
	//std::cout << substance.get_Ro() << "\n";
	//std::cout << "id: " << _id << std::endl;

	if (substance_pos_in_cup == -1)
	{
		substances.push_back(substance);
		volumes.push_back(volume_in_ml / 1e6);
		//std::cout << mass << "\n";
		masses.push_back(mass);
		volume_sum += volume_in_ml / 1e6;
		mass_sum += mass;
	}
	else if (substance_pos_in_cup >= 0)
	{
		volumes[substance_pos_in_cup] += volume_in_ml / 1e6;
		masses[substance_pos_in_cup] += mass;
		//std::cout << "\t\n\n" << volumes[_id] << "\n\n";
		volume_sum += volume_in_ml / 1e6;
		mass_sum += mass;
	}

}

void TCups::add(std::string name, double volume_in_ml)
{
	int _id = get_substance_id(substancje, name);
	//std::cout << _id;
	if (_id >= 0)
	{
		this->add(substancje[_id], volume_in_ml);
	}
}

void TCups::add_2(std::string name, double percent, std::string type)
{
	int _id = get_substance_id(substances, name);

	if (_id >= 0)
	{
		if (type.compare("volume")==0)
		{
			double others_vol = volume_sum - volumes[_id];
			double perc = 100 - (others_vol / volume_sum);
			double diff = abs(percent - perc);
			double desired_vol, new_vol_sum;
			//std::cout << "\n" << perc << "\n\n";
			new_vol_sum = others_vol / (diff/100);
			desired_vol = new_vol_sum - others_vol;

			volume_sum = new_vol_sum;
			volumes[_id] = desired_vol;
			mass_sum -= masses[_id];
			masses[_id] = volumes[_id] * substances[_id].get_Ro() * 1000;
			//std::cout << "\n" << masses[_id] << "\n";
			mass_sum += masses[_id];
		}
		else if (type.compare("mass")==0)
		{
			double others_mass = mass_sum - masses[_id];
			double perc = 100 - (others_mass / mass_sum);
			double diff = abs(percent - perc);
			double desired_mass, new_mass_sum;
			
			new_mass_sum = others_mass / (diff / 100);
			//std::cout << "\n" << new_mass_sum << "\n";
			desired_mass = new_mass_sum - others_mass;

			mass_sum = new_mass_sum;
			masses[_id] = desired_mass;
			volume_sum -= volumes[_id];
			volumes[_id] = masses[_id] / (substances[_id].get_Ro() * 1000);
			volume_sum += volumes[_id];
		}	
	}
	else if(type.compare("volume") == 0)
	{
		if (name.compare("woda") == 0)
		{
			add("woda", percent);
			add("oliwa", 100 - percent);
		}
		else
		{
			add("woda", 100 - percent);
			add(name, percent);
		}
	}
	else if (type.compare("mass") == 0)
	{
		double water_vol, oth_vol;
		int _id = get_substance_id(substancje, name);

		if (name.compare("woda") == 0)
		{
			water_vol = percent/ (substancje[_id].get_Ro() * 1000);
			oth_vol = (100 - percent) / (substancje[_id].get_Ro() * 1000);
			add("woda", percent);
			add("oliwa", 100 - percent);
		}
		else
		{
			water_vol = (100 - percent) / (substancje[_id].get_Ro() * 1000);
			oth_vol = percent / (substancje[_id].get_Ro() * 1000);
			add("woda", 100 - percent);
			add(name, percent);
		}
	}
}

void TCups::mixup(TCups * cup)
{
	int size_cup1 = cup->substances.size();
	int size_cup2 = this->substances.size();
	
	for (int i = 0; i < size_cup1; i++)
	{
		std::string name = cup->substances[i].get_name();
		int _id = get_substance_id(cup->substances, name, false);

		if (_id == -1)
		{
			int _id2 = get_substance_id(this->substances, this->substances[i].get_name(), false);

			if (_id2 == -1)
			{
				std::cout << "\n\n W zadnym kubku nie ma takiej substancji\n\n";
			}
			else
			{
				cup->substances.push_back(this->substances[_id2]);
				cup->volumes.push_back(this->volumes[_id2]);
				cup->masses.push_back(this->masses[_id2]);
				cup->volume_sum += this->volumes[_id2];
				cup->mass_sum += this->masses[_id2];
			}
		}
		else if(_id >= 0)
		{
			int _id3 = get_substance_id(this->substances, name, false);
			
			if (_id3 >= 0)
			{
				cup->volumes[_id] += this->volumes[_id3];
				cup->masses[_id] += this->masses[_id3];
				cup->volume_sum += this->volumes[_id3];
				cup->mass_sum += this->masses[_id3];
			}
		}
	}

	this->clear_cup();
}

void TCups::clear_cup()
{
	this->substances.clear();
	this->volumes.clear();
	this->masses.clear();
	this->volume_sum = 0;
	this->mass_sum = 0;
}

void TCups::show()
{
	int count = this->substances.size();

	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			std::string sub_name = this->substances[i].get_name();
			double volume = this->volumes[i] * 1e6;
			double mass = this->masses[i];
			std::cout << "\n" << sub_name
			<< "; volume: " << volume << " ml"
			<< "; mass: " << mass << " g" << std::endl;
		}

		print_coe_vol();
		print_coe_mass();
		std::cout << "\n\n";
	}
	else
	{
		std::cout << "Kubek jest pusty!\n\n\n";
	}
}

void TCups::print_coe_vol()
{
	int size = TCups::volumes.size();

	std::cout << "\nVolume coe: \n";
	for (int i = 0; i < size; i++)
	{
		std::cout << substances[i].get_name() << ": " << (TCups::volumes[i] / TCups::volume_sum) * 100 << " --- ";
	}
}

void TCups::print_coe_mass()
{
	int size = TCups::volumes.size();

	std::cout << "\nMass coe: \n";
	for (int i = 0; i < size; i++)
	{
		std::cout << substances[i].get_name() << ": " << TCups::volumes[i]*substances[i].get_Ro()*1000 / TCups::mass_sum * 100 << " --- ";
	}

}

int TCups::get_substance_id(std::vector <TSubstance> subs_buff, std::string name, bool alert)
{
	int _id = -1;
	size_t count = subs_buff.size();
	bool run = count;

	while (run)
	{
		_id += 1;
		std::string sub_name = subs_buff[_id].get_name();
		//std::cout << "\n" << sub_name << "\n";

		if (sub_name == name) run = false;

		if ((run == true) && (_id + 1 == count))
		{
			_id = -1;
			if (alert) std::cout << "Nie znaleziono plynu o podanej nazwie: " << name << "\n\n";
			run = false;
		}
	}


	return _id;
}