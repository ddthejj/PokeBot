#pragma once
#include <map>
#include <vector>

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
	Fairy,
	Type_Max
};

enum class EggGroup
{
	None,
	Undiscovered,
	Monster,
	Water1,
	Bug,
	Flying,
	Field,
	Fairy,
	Grass,
	Humanlike,
	Water3,
	Mineral,
	Amorphous,
	Water2,
	Ditto,
	Dragon,
	EggGroup_Max
};

enum class PokemonColor
{
	None,
	Red,
	Blue,
	Yellow,
	Green,
	Black,
	Brown,
	Purple,
	Gray,
	White,
	Pink,
	PokemonColor_Max
};

enum class PokemonShape
{
	None,
	Armor,
	Arms,
	Ball,
	Blob,
	BugWings,
	Fish,
	Heads,
	Humanoid,
	Legs,
	Quadruped,
	Squiggle,
	Tentacles,
	Upright,
	Wings,
	PokemonShape_Max
};

class Pokemon_Data
{
public:

	Pokemon_Data() {}
	Pokemon_Data(
		int In_DexNum,
		std::string In_Name, std::string In_FormName, std::string In_Classification,
		bool In_IsDefaultForm, bool In_FormsSwitchable,
		Type In_Type1, Type In_Type2,
		int In_Base_HP, int In_Base_Attack, int In_Base_Defense, int In_Base_SpAttack, int In_Base_SpDefense, int In_Base_Speed,
		int In_Gen, 
		bool In_Legendary, bool In_Mythical,
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
		Pokemon_Data* In_EvolvesFrom,
		PokemonColor In_Color,
		PokemonShape In_Shape
	);

	int DexNum = -1;
	std::string Name = "ERROR_NAME";
	std::string FormName = "ERROR_FORM";
	std::string Classification = "ERROR_GENUS";
	bool IsDefaultForm = false, FormsSwitchable = false;
	Type Type1 = Type::None, Type2 = Type::None;
	int Base_HP = 1, Base_Attack = 1, Base_Defense = 1, Base_SpAttack = 1, Base_SpDefense = 1, Base_Speed = 1;
	int Gen = 0;
	bool Legedary = false, Mythical = false;
	int Stage = -1;
	int Ability1 = -1, Ability2 = -1, HiddenAbility = -1;
	float Height = -1.f, Weight = -1.f;
	float FemalePercentage = .5f; bool Genderless = false;
	bool IsBaby = false;
	int BaseXP = -1, CaptureRate = 255;
	EggGroup EggGroup1 = EggGroup::None, EggGroup2 = EggGroup::None;
	int EggCycles;
	int BaseHappiness;
	bool CanEvolve; 
	Pokemon_Data* EvolvesFrom = nullptr;
	PokemonColor Color = PokemonColor::None;
	PokemonShape Shape = PokemonShape::None;


	static Type StringToType(std::string In_Type);
	static std::string TypeToString(Type In_Type);
	static EggGroup StringToEggGroup(std::string In_EggGroup);
	static std::string EggGroupToString(EggGroup In_EggGroup);
	static PokemonColor StringToColor(std::string In_Color);
	static std::string ColorToString(PokemonColor In_Color);
	static PokemonShape StringToShape(std::string In_Shape);
	static std::string ShapeToString(PokemonShape In_Shape);

	std::string TypeAsString();
	std::string EggGroupAsString();
	std::string ColorAsString();
	std::string ShapeAsString();
};

class Pokedex
{
public:

	Pokedex();
	~Pokedex();

	std::map<int, std::vector<Pokemon_Data*>> pokedex;
	std::map <std::string, int> abilityDex;
};