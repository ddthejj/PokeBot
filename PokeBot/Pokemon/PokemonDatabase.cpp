#include "PokemonDatabase.h"
#include <iostream>
#include <fstream>

Pokemon_Data::Pokemon_Data(
int In_DexNum, 
std::string In_Name, std::string In_FormName, 
Type In_Type1, Type In_Type2, 
int In_Base_HP, int In_Base_Attack, int In_Base_Defense, int In_Base_SpAttack, int In_Base_SpDefense, int In_Base_Speed, 
int In_Gen, bool In_Legendary, int In_Stage)
{
	DexNum = In_DexNum;
	Name = In_Name;
	Type1 = In_Type1;
	Type2 = In_Type2;
	Base_HP = In_Base_HP;
	Base_Attack = In_Base_Attack;
	Base_Defense = In_Base_Defense;
	Base_SpAttack = In_Base_SpAttack;
	Base_SpDefense = In_Base_SpDefense;
	Base_Speed = In_Base_Speed;
	Gen = In_Gen;
	Legedary = In_Legendary;
	Stage = In_Stage;
}

Type Pokemon_Data::StringToType(std::string In_Type)
{
	if (0 == stricmp(In_Type.c_str(), " "))
	{
		return Type::None;
	}
	else if (0 == stricmp(In_Type.c_str(), "Normal"))
	{
		return Type::Normal;
	}
	else if (0 == stricmp(In_Type.c_str(), "Fire"))
	{
		return Type::Fire;
	}
	else if (0 == stricmp(In_Type.c_str(), "Water"))
	{
		return Type::Water;
	}
	else if (0 == stricmp(In_Type.c_str(), "Grass"))
	{
		return Type::Grass;
	}
	else if (0 == stricmp(In_Type.c_str(), "Electric"))
	{
		return Type::Electric;
	}
	else if (0 == stricmp(In_Type.c_str(), "Ice"))
	{
		return Type::Ice;
	}
	else if (0 == stricmp(In_Type.c_str(), "Fighting"))
	{
		return Type::Fighting;
	}
	else if (0 == stricmp(In_Type.c_str(), "Poison"))
	{
		return Type::Poison;
	}
	else if (0 == stricmp(In_Type.c_str(), "Ground"))
	{
		return Type::Ground;
	}
	else if (0 == stricmp(In_Type.c_str(), "Flying"))
	{
		return Type::Flying;
	}
	else if (0 == stricmp(In_Type.c_str(), "Psychic"))
	{
		return Type::Psychic;
	}
	else if (0 == stricmp(In_Type.c_str(), "Bug"))
	{
		return Type::Bug;
	}
	else if (0 == stricmp(In_Type.c_str(), "Rock"))
	{
		return Type::Rock;
	}
	else if (0 == stricmp(In_Type.c_str(), "Ghost"))
	{
		return Type::Ghost;
	}
	else if (0 == stricmp(In_Type.c_str(), "Dark"))
	{
		return Type::Dark;
	}
	else if (0 == stricmp(In_Type.c_str(), "Dragon"))
	{
		return Type::Dragon;
	}
	else if (0 == stricmp(In_Type.c_str(), "Steel"))
	{
		return Type::Steel;
	}
	else if (0 == stricmp(In_Type.c_str(), "Fairy"))
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



Pokedex::Pokedex()
{
	std::ifstream file("../../../Content/PokemonList.csv", std::ios::in);

	if (!file.is_open())
		return;


	// read every line from the file
	std::string words[15];

	char buffer[2048];
	// skip header
	file.getline(buffer, 2048);

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
		// ID,Name,Form,Type1,Type2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary,Stage

		/*
		int In_DexNum, 
				std::string In_Name, std::string In_FormName, 
				Type In_Type1, Type In_Type2, 
				int In_Base_HP, int In_Base_Attack, int In_Base_Defense, int In_Base_SpAttack, int In_Base_SpDefense, int In_Base_Speed, 
				int In_Gen, bool In_Legendary, int In_Stage);
		*/

		Pokemon_Data newMon = Pokemon_Data(
			atoi(words[0].c_str()), 
			words[1], words[2],
			Pokemon_Data::StringToType(words[3]), Pokemon_Data::StringToType(words[4]), 
			atoi(words[6].c_str()), atoi(words[7].c_str()), atoi(words[8].c_str()), atoi(words[9].c_str()), atoi(words[10].c_str()), atoi(words[11].c_str()),
			atoi(words[12].c_str()), words[13] == std::string("TRUE"), atoi(words[14].c_str()));

		pokedex.insert(std::pair<int, Pokemon_Data>(atoi(words[0].c_str()), newMon));
	}

	file.close();
	return;
}