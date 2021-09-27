#include "PokemonDatabase.h"

#include "Evolution.h"

#include <iostream>
#include <fstream>
#include <cassert>


enum class CSV_Sort
{
	name, form_name,
	pokedex_number,
	abilities, abilities2, abilities3,
	typing, typing2,
	hp, attack, defense, special_attack, special_defense, speed,
	height, weight,
	genus,
	gen_introduced,
	female_rate, genderless, baby_pokemon,
	legendary, mythical, ultrabeast,
	is_default, forms_switchable,
	base_experience, capture_rate,
	egg_groups, egg_groups2,
	egg_cycles,
	base_happiness,
	can_evolve, evolves_from, evolve_condition,
	primary_color, shape
};

Pokemon_Data::Pokemon_Data(
	int In_DexNum,
	std::string In_Name, std::string In_FormName, std::string In_Classification,
	bool In_IsDefaultForm, bool In_FormsSwitchable,
	Type In_Type1, Type In_Type2,
	int In_Base_HP, int In_Base_Attack, int In_Base_Defense, int In_Base_SpAttack, int In_Base_SpDefense, int In_Base_Speed,
	int In_Gen,
	bool In_Legendary, bool In_Mythical, bool In_UltraBeast,
	int In_Stage,
	int In_Ability1, int In_Ability2, int In_HiddenAbility,
	float In_Height, float In_Weight,
	float In_FemalePercentage, bool In_Genderless,
	bool In_IsBaby,
	int In_BaseXP, int In_CaptureRate,
	EggGroup In_EggGroup1, EggGroup In_EggGroup2,
	int In_EggCycles,
	int In_BaseHappiness,
	bool In_CanEvolve,
	Pokemon_Data* In_EvolvesFrom, EvolutionMethod* In_EvolutionType,
	PokemonColor In_Color,
	PokemonShape In_Shape
)
{
	DexNum = In_DexNum;
	Name = In_Name; FormName = In_FormName; Classification = In_Classification;
	IsDefaultForm = In_IsDefaultForm; FormsSwitchable = In_FormsSwitchable;
	Type1 = In_Type1; Type2 = In_Type2;
	Base_HP = In_Base_HP; Base_Attack = In_Base_Attack;	Base_Defense = In_Base_Defense;	Base_SpAttack = In_Base_SpAttack; Base_SpDefense = In_Base_SpDefense; Base_Speed = In_Base_Speed;
	Gen = In_Gen;
	Legedary = In_Legendary; Mythical = In_Mythical; UltraBeast = In_UltraBeast;
	Stage = In_Stage;
	Ability1 = In_Ability1; Ability2 = In_Ability2; HiddenAbility = In_HiddenAbility;
	Height = In_Height; Weight = In_Weight;
	FemalePercentage = In_FemalePercentage; Genderless = In_Genderless;
	IsBaby = In_IsBaby;
	BaseXP = In_BaseXP; CaptureRate = In_CaptureRate;
	EggGroup1 = In_EggGroup1; EggGroup2 = In_EggGroup2;
	EggCycles = In_EggCycles;
	BaseHappiness = In_BaseHappiness;
	CanEvolve = In_CanEvolve;
	EvolvesFrom = In_EvolvesFrom;
	EvolvesTo = std::vector<Evolution>();
	Color = In_Color;
	Shape = In_Shape;
}

Type Pokemon_Data::StringToType(std::string In_Type)
{
	if (0 == _stricmp(In_Type.c_str(), " "))
	{
		return Type::None;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Normal"))
	{
		return Type::Normal;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Fire"))
	{
		return Type::Fire;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Water"))
	{
		return Type::Water;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Grass"))
	{
		return Type::Grass;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Electric"))
	{
		return Type::Electric;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Ice"))
	{
		return Type::Ice;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Fighting"))
	{
		return Type::Fighting;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Poison"))
	{
		return Type::Poison;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Ground"))
	{
		return Type::Ground;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Flying"))
	{
		return Type::Flying;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Psychic"))
	{
		return Type::Psychic;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Bug"))
	{
		return Type::Bug;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Rock"))
	{
		return Type::Rock;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Ghost"))
	{
		return Type::Ghost;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Dark"))
	{
		return Type::Dark;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Dragon"))
	{
		return Type::Dragon;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Steel"))
	{
		return Type::Steel;
	}
	else if (0 == _stricmp(In_Type.c_str(), "Fairy"))
	{
		return Type::Fairy;
	}

	return Type::None;
}

std::string Pokemon_Data::TypeToString(Type In_Type)
{
	switch (In_Type)
	{
	case Type::None:
	{
		return " ";
	}
	case Type::Normal:
	{
		return "Normal";
	}
	case Type::Fire:
	{
		return "Fire";
	}
	case Type::Water:
	{
		return "Water";
	}
	case Type::Grass:
	{
		return "Grass";
	}
	case Type::Electric:
	{
		return "Electric";
	}
	case Type::Ice:
	{
		return "Ice";
	}
	case Type::Fighting:
	{
		return "Fighting";
	}
	case Type::Poison:
	{
		return "Poison";
	}
	case Type::Ground:
	{
		return "Ground";
	}
	case Type::Flying:
	{
		return "Flying";
	}
	case Type::Psychic:
	{
		return "Psychic";
	}
	case Type::Bug:
	{
		return "Bug";
	}
	case Type::Rock:
	{
		return "Rock";
	}
	case Type::Ghost:
	{
		return "Ghost";
	}
	case Type::Dark:
	{
		return "Dark";
	}
	case Type::Dragon:
	{
		return "Dragon";
	}
	case Type::Steel:
	{
		return "Steel";
	}
	case Type::Fairy:
	{
		return "Fairy";
	}
	default:
	{
		return " ";
	}
	}
}

EggGroup Pokemon_Data::StringToEggGroup(std::string In_EggGroup)
{
	if (0 == _stricmp(In_EggGroup.c_str(), " "))
	{
		return EggGroup::None;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Undiscovered"))
	{
		return EggGroup::Undiscovered;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Monster"))
	{
		return EggGroup::Monster;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Water1"))
	{
		return EggGroup::Water1;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Bug"))
	{
		return EggGroup::Bug;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Flying"))
	{
		return EggGroup::Flying;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Field"))
	{
		return EggGroup::Field;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Fairy"))
	{
		return EggGroup::Fairy;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Grass"))
	{
		return EggGroup::Grass;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Humanlike"))
	{
		return EggGroup::Humanlike;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Water3"))
	{
		return EggGroup::Water3;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Mineral"))
	{
		return EggGroup::Mineral;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Amorphous"))
	{
		return EggGroup::Amorphous;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Water2"))
	{
		return EggGroup::Water2;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Ditto"))
	{
		return EggGroup::Ditto;
	}
	else if (0 == _stricmp(In_EggGroup.c_str(), "Dragon"))
	{
		return EggGroup::Dragon;
	}

	return EggGroup::None;
}

std::string Pokemon_Data::EggGroupToString(EggGroup In_EggGroup)
{
	switch (In_EggGroup)
	{
	case EggGroup::None:
	{
		return " ";
	}
	case EggGroup::Undiscovered:
	{
		return "Undiscovered";
	}
	case EggGroup::Monster:
	{
		return "Monster";
	}
	case EggGroup::Water1:
	{
		return "Water1";
	}
	case EggGroup::Bug:
	{
		return "Bug";
	}
	case EggGroup::Flying:
	{
		return "Flying";
	}
	case EggGroup::Field:
	{
		return "Field";
	}
	case EggGroup::Fairy:
	{
		return "Fairy";
	}
	case EggGroup::Grass:
	{
		return "Grass";
	}
	case EggGroup::Humanlike:
	{
		return "Humanlike";
	}
	case EggGroup::Water3:
	{
		return "Water3";
	}
	case EggGroup::Mineral:
	{
		return "Mineral";
	}
	case EggGroup::Amorphous:
	{
		return "Amorphous";
	}
	case EggGroup::Water2:
	{
		return "Water2";
	}
	case EggGroup::Ditto:
	{
		return "Ditto";
	}
	case EggGroup::Dragon:
	{
		return "Dragon";
	}
	default:
	{
		return " ";
	}
	}
}

PokemonColor Pokemon_Data::StringToColor(std::string In_Color)
{
	if (0 == _stricmp(In_Color.c_str(), " "))
	{
		return PokemonColor::None;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Red"))
	{
		return PokemonColor::Red;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Blue"))
	{
		return PokemonColor::Blue;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Yellow"))
	{
		return PokemonColor::Yellow;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Green"))
	{
		return PokemonColor::Green;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Black"))
	{
		return PokemonColor::Black;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Brown"))
	{
		return PokemonColor::Brown;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Purple"))
	{
		return PokemonColor::Purple;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Gray"))
	{
		return PokemonColor::Gray;
	}
	else if (0 == _stricmp(In_Color.c_str(), "White"))
	{
		return PokemonColor::White;
	}
	else if (0 == _stricmp(In_Color.c_str(), "Pink"))
	{
		return PokemonColor::Pink;
	}

	return PokemonColor::None;
}

std::string Pokemon_Data::ColorToString(PokemonColor In_Color)
{
	switch (In_Color)
	{
	case PokemonColor::None:
	{
		return std::string(" ");
	}
	case PokemonColor::Red:
	{
		return std::string("Red");
	}
	case PokemonColor::Blue:
	{
		return std::string("Blue");
	}
	case PokemonColor::Yellow:
	{
		return std::string("Yellow");
	}
	case PokemonColor::Green:
	{
		return std::string("Green");
	}
	case PokemonColor::Black:
	{
		return std::string("Black");
	}
	case PokemonColor::Brown:
	{
		return std::string("Brown");
	}
	case PokemonColor::Purple:
	{
		return std::string("Purple");
	}
	case PokemonColor::Gray:
	{
		return std::string("Gray");
	}
	case PokemonColor::White:
	{
		return std::string("White");
	}
	case PokemonColor::Pink:
	{
		return std::string("Pink");
	}
	default:
	{
		return std::string("");
	}
	}
}

PokemonShape Pokemon_Data::StringToShape(std::string In_Shape)
{
	if (0 == _stricmp(In_Shape.c_str(), " "))
	{
		return PokemonShape::None;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Armor"))
	{
		return PokemonShape::Armor;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Arms"))
	{
		return PokemonShape::Arms;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Ball"))
	{
		return PokemonShape::Ball;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Blob"))
	{
		return PokemonShape::Blob;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "BugWings"))
	{
		return PokemonShape::BugWings;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Fish"))
	{
		return PokemonShape::Fish;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Heads"))
	{
		return PokemonShape::Heads;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Humanoid"))
	{
		return PokemonShape::Humanoid;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Legs"))
	{
		return PokemonShape::Legs;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Quadruped"))
	{
		return PokemonShape::Quadruped;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Squiggle"))
	{
		return PokemonShape::Squiggle;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Tentacles"))
	{
		return PokemonShape::Tentacles;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Upright"))
	{
		return PokemonShape::Upright;
	}
	else if (0 == _stricmp(In_Shape.c_str(), "Wings"))
	{
		return PokemonShape::Wings;
	}
	return PokemonShape::None;
}

std::string Pokemon_Data::ShapeToString(PokemonShape In_Shape)
{
	switch (In_Shape)
	{
	case PokemonShape::None:
	{
		return std::string("");
	}
	case PokemonShape::Armor:
	{
		return std::string("Armor");
	}
	case PokemonShape::Arms:
	{
		return std::string("Arms");
	}
	case PokemonShape::Ball:
	{
		return std::string("Ball");
	}
	case PokemonShape::Blob:
	{
		return std::string("Blob");
	}
	case PokemonShape::BugWings:
	{
		return std::string("BugWings");
	}
	case PokemonShape::Fish:
	{
		return std::string("Fish");
	}
	case PokemonShape::Heads:
	{
		return std::string("Heads");
	}
	case PokemonShape::Humanoid:
	{
		return std::string("Humanoid");
	}
	case PokemonShape::Legs:
	{
		return std::string("Legs");
	}
	case PokemonShape::Quadruped:
	{
		return std::string("Quadruped");
	}
	case PokemonShape::Squiggle:
	{
		return std::string("Squiggle");
	}
	case PokemonShape::Tentacles:
	{
		return std::string("Tentacles");
	}
	case PokemonShape::Upright:
	{
		return std::string("Upright");
	}
	case PokemonShape::Wings:
	{
		return std::string("Wings");
	}
	default:
	{
		return std::string(" ");
	}
	}
}

std::string Pokemon_Data::TypeAsString()
{
	if (Type2 == Type::None)
	{
		// single type
		return TypeToString(Type1);
	}
	else
	{
		// dual type
		return TypeToString(Type1) + "/" + TypeToString(Type2);
	}
}

std::string Pokemon_Data::EggGroupAsString()
{

	if (EggGroup2 == EggGroup::None)
	{
		// single egg group
		return EggGroupToString(EggGroup1);
	}
	else
	{
		// dual egg group
		return EggGroupToString(EggGroup1) + "/" + EggGroupToString(EggGroup2);
	}
}

std::string Pokemon_Data::ColorAsString()
{
	return ColorToString(Color);
}

std::string Pokemon_Data::ShapeAsString()
{
	return ShapeToString(Shape);
}



Pokedex::Pokedex()
{
	std::ifstream file("../../../Content/PokemonList.csv", std::ios::in);

	if (!file.is_open())
		return;


	// read every line from the file
	std::string words[64];

	char buffer[2048];
	// skip header
	file.getline(buffer, 2048);

	std::map<Pokemon_Data*, std::string> EvolvesFromMap;

	while (file.getline(buffer, 2048))
	{
		std::string line = buffer;

		int charAt = 0;
		int wordsAt = 0;
		while (charAt < line.size())
		{
			char buffer[2048];
			int bufferAt = 0;

			while (charAt < line.size() && line[charAt] != ',')
			{
				buffer[bufferAt] = line[charAt];
				charAt++;
				bufferAt++;
			}

			buffer[bufferAt] = '\0';
			words[wordsAt] = (std::string(buffer));
			charAt++;
			wordsAt++;
		}

		std::string abilities[3] = { words[(int)CSV_Sort::abilities], words[(int)CSV_Sort::abilities2], words[(int)CSV_Sort::abilities3] };
		int abilityNums[3];

		for (int i = 0; i < 3; i++)
		{
			if (abilities[i] != "")
			{
				if (abilityDex.count(abilities[i]))
				{
					abilityNums[i] = abilityDex[abilities[i]];
				}
				else
				{
					abilityDex.insert(std::make_pair(abilities[i], abilityDex.size()));
					abilityNums[i] = abilityDex[abilities[i]];
				}
			}
			else
			{
				abilityNums[i] = -1;
			}
		}

		if (abilityNums[1] != -1 && abilityNums[2] == -1)
		{
			abilityNums[2] = abilityNums[1];
			abilityNums[1] = -1;
		}

		int In_DexNum = atoi(words[(int)CSV_Sort::pokedex_number].c_str());
		std::string In_Name = words[(int)CSV_Sort::name], In_FormName = words[(int)CSV_Sort::form_name], In_Classification = words[(int)CSV_Sort::genus];
		bool In_IsDefaultForm = words[(int)CSV_Sort::is_default] == std::string("TRUE"), In_FormsSwitchable = words[(int)CSV_Sort::forms_switchable] == std::string("TRUE");
		Type In_Type1 = Pokemon_Data::StringToType(words[(int)CSV_Sort::typing]), In_Type2 = Pokemon_Data::StringToType(words[(int)CSV_Sort::typing2]);
		int In_Base_HP = atoi(words[(int)CSV_Sort::hp].c_str()), In_Base_Attack = atoi(words[(int)CSV_Sort::attack].c_str()), In_Base_Defense = atoi(words[(int)CSV_Sort::defense].c_str()),
			In_Base_SpAttack = atoi(words[(int)CSV_Sort::special_attack].c_str()), In_Base_SpDefense = atoi(words[(int)CSV_Sort::special_defense].c_str()), In_Base_Speed = atoi(words[(int)CSV_Sort::speed].c_str());
		int In_Gen = atoi(words[(int)CSV_Sort::gen_introduced].c_str());
		bool In_Legendary = words[(int)CSV_Sort::legendary] == std::string("TRUE"), In_Mythical = words[(int)CSV_Sort::mythical] == std::string("TRUE"), In_UltraBeast = words[(int)CSV_Sort::ultrabeast] == std::string("TRUE");
		int In_Stage = -1;
		int In_Ability1 = abilityNums[0], In_Ability2 = abilityNums[1], In_HiddenAbility = abilityNums[2];
		float In_Height = (float)atof(words[(int)CSV_Sort::height].c_str()), In_Weight = (float)atof(words[(int)CSV_Sort::weight].c_str());
		float In_FemalePercentage = (float)atof(words[(int)CSV_Sort::female_rate].c_str()); bool In_Genderless = words[(int)CSV_Sort::genderless] == std::string("TRUE");
		bool In_IsBaby = words[(int)CSV_Sort::baby_pokemon] == std::string("TRUE");
		int In_BaseXP = atoi(words[(int)CSV_Sort::base_experience].c_str()), In_CaptureRate = atoi(words[(int)CSV_Sort::capture_rate].c_str());
		EggGroup In_EggGroup1 = Pokemon_Data::StringToEggGroup(words[(int)CSV_Sort::egg_groups]), In_EggGroup2 = Pokemon_Data::StringToEggGroup(words[(int)CSV_Sort::egg_groups2]);
		int In_EggCycles = atoi(words[(int)CSV_Sort::egg_cycles].c_str());
		int In_BaseHappiness = atoi(words[(int)CSV_Sort::base_happiness].c_str());
		bool In_CanEvolve = words[(int)CSV_Sort::can_evolve] == std::string("TRUE");
		Pokemon_Data* In_EvolvesFrom = nullptr; std::vector<EvolutionMethod> In_EvolutionType; 
		PokemonColor In_Color = Pokemon_Data::StringToColor(words[(int)CSV_Sort::primary_color]);
		PokemonShape In_Shape = Pokemon_Data::StringToShape(words[(int)CSV_Sort::shape]);

		// parse with ',' as delim
		EvolutionMethod::MakeEvolutionMethod(words[(int)CSV_Sort::evolve_condition]);

		if (!In_IsDefaultForm)
		{
			if (pokedex[In_DexNum].size() != 0)
				In_Name = pokedex[In_DexNum][0]->Name;
		}

		Pokemon_Data* newMon = new Pokemon_Data(
			In_DexNum,
			In_Name, In_FormName, In_Classification,
			In_IsDefaultForm, In_FormsSwitchable,
			In_Type1, In_Type2,
			In_Base_HP, In_Base_Attack, In_Base_Defense, In_Base_SpAttack, In_Base_SpDefense, In_Base_Speed,
			In_Gen,
			In_Legendary, In_Mythical, In_UltraBeast,
			In_Stage,
			In_Ability1, In_Ability2, In_HiddenAbility,
			In_Height, In_Weight,
			In_FemalePercentage, In_Genderless,
			In_IsBaby,
			In_BaseXP, In_CaptureRate,
			In_EggGroup1, In_EggGroup2,
			In_EggCycles,
			In_BaseHappiness,
			In_CanEvolve,
			In_EvolvesFrom, In_EvolutionType,
			In_Color,
			In_Shape
		);

		if (words[(int)CSV_Sort::evolves_from] != "")
		{
			EvolvesFromMap.insert(std::make_pair(newMon, words[(int)CSV_Sort::evolves_from]));
		}
		else
		{
			if (newMon->IsBaby)
			{
				newMon->Stage = 0;
			}
			else
			{
				newMon->Stage = 1;
			}
		}

		if (pokedex.count(newMon->DexNum))
		{
			pokedex[newMon->DexNum].push_back(newMon);
		}
		else
		{
			std::vector<Pokemon_Data*> pokemonList;
			pokemonList.push_back(newMon);

			pokedex.insert(std::pair<int, std::vector<Pokemon_Data*>>(newMon->DexNum, pokemonList));

			assert(newMon->DexNum != 0);
		}
	}

	file.close();

	for (auto it = EvolvesFromMap.begin(); it != EvolvesFromMap.end(); it++)
	{
		std::string EvolvesFrom = (*it).second;
		auto mon = it->first;


		if (EvolvesFrom != std::string(""))
		{
			// first try grabbing from previous entry
			if (pokedex.count(mon->DexNum - 1))
			{
				for (int i = 0; i < pokedex[mon->DexNum - 1].size(); i++)
				{
					Pokemon_Data* prev_mon = pokedex[mon->DexNum - 1][i];

					if (_stricmp(prev_mon->Name.c_str(), EvolvesFrom.c_str()) == 0)
					{
						mon->EvolvesFrom = prev_mon;
						prev_mon->EvolvesTo.push_back(Evolution(mon, mon->EvolutionType));
					}
					else if (0 == _stricmp(prev_mon->FormName.c_str(), EvolvesFrom.c_str()))
					{
						mon->EvolvesFrom = prev_mon;
						prev_mon->EvolvesTo.push_back(Evolution(mon, mon->EvolutionType));
					}
				}
			}

			// search entire pokedex for mon
			if (!mon->EvolvesFrom)
			{
				// find pokemon that this pokemon evolves from
				for (auto it = pokedex.begin(); it != pokedex.end(); it++)
				{
					std::vector<Pokemon_Data*> pokedexEntry = it->second;

					for (int j = 0; j < pokedexEntry.size(); j++)
					{
						Pokemon_Data* prev_mon = pokedexEntry[j];

						if (0 == _stricmp(prev_mon->Name.c_str(), EvolvesFrom.c_str()))
						{
							mon->EvolvesFrom = prev_mon;
							prev_mon->EvolvesTo.push_back(Evolution(mon, mon->EvolutionType));
						}
						else if (0 == _stricmp(prev_mon->FormName.c_str(), EvolvesFrom.c_str()))
						{
							mon->EvolvesFrom = prev_mon;
							prev_mon->EvolvesTo.push_back(Evolution(mon, mon->EvolutionType));
						}
					}
				}
			}

			// didn't find the pre-evolution, crash
			assert(mon->EvolvesFrom);

			// set stage
			if (mon->EvolvesFrom->EvolvesFrom)
			{
				if (mon->EvolvesFrom->EvolvesFrom->IsBaby)
				{
					if (mon->EvolvesFrom->DexNum == mon->EvolvesFrom->EvolvesFrom->DexNum + 1)
					{
						mon->Stage = 3;
					}
					else
					{
						mon->Stage = 2;
					}
				}
				else
				{
					mon->Stage = 3;
				}
			}
			else
			{
				if (mon->EvolvesFrom->IsBaby)
				{
					if (mon->DexNum == mon->EvolvesFrom->DexNum + 1)
					{
						mon->Stage = 2;
						mon->EvolvesFrom->Stage = 1;
					}
					else
					{
						mon->Stage = 1;
					}
				}
				else
				{
					mon->Stage = 2;
				}
			}
		}
		else
		{
			if (mon->IsBaby)
			{
				mon->Stage = 0;
			}
			else
			{
				mon->Stage = 1;
			}
		}
	}

	return;
}

Pokedex::~Pokedex()
{
	for (auto it = pokedex.begin(); it != pokedex.end(); ++it)
	{
		std::vector<Pokemon_Data*> dexEntry = it->second;

		for (int i = 0; i < dexEntry.size(); i++)
		{
			delete dexEntry[i];
		}
	}
}
