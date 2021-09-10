#pragma once
#include <map>

#include <string>

enum class Type
{
	None,
	Normal,
	Fire,
	Water,
	Grass,
	Electric,
	Ice,
	Fighting,
	Poison,
	Ground,
	Flying,
	Psychic,
	Bug,
	Rock,
	Ghost,
	Dark,
	Dragon,
	Steel,
	Fairy
};

class Pokemon_Data
{
public:

	Pokemon_Data() {}
	Pokemon_Data(
		int In_DexNum, 
		std::string In_Name, std::string In_FormName, 
		Type In_Type1, Type In_Type2, 
		int In_Base_HP, int In_Base_Attack, int In_Base_Defense, int In_Base_SpAttack, int In_Base_SpDefense, int In_Base_Speed, 
		int In_Gen, bool In_Legendary, int In_Stage);

	// #,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary
	int DexNum = -1;
	std::string Name = "ERROR_NAME";
	std::string FormName = "ERROR_FORM";
	Type Type1 = Type::None;
	Type Type2 = Type::None;
	int Base_HP = 1, Base_Attack = 1, Base_Defense = 1, Base_SpAttack = 1, Base_SpDefense = 1, Base_Speed = 1;
	int Gen = 0;
	bool Legedary = false;
	int Stage = -1;

	static Type StringToType(std::string In_Type);
	static std::string TypeToString(Type In_Type);

	std::string TypeAsString();
};

class Pokedex
{
public:

	Pokedex();


	std::map<int, Pokemon_Data> pokedex;
};