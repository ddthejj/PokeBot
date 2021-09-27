#pragma once

#include <stdint.h>
#include <string>

class Pokemon_Data;
class Item;
class EvolutionMethod;

enum class Pokemon_Nature
{
	None = 0,
	UpAttack = 1,
	DownAttack = 1 << 1,
	UpDefense = 1 << 2,
	DownDefense = 1 << 3,
	UpSpAttack = 1 << 4,
	DownSpAttack = 1 << 5,
	UpSpDefense = 1 << 6,
	DownSpDefense = 1 << 7,
	UpSpeed = 1 << 8,
	DownSpeed = 1 << 9,

	Hardy = None,
	Lonely = UpAttack | DownDefense,
	Brave = UpAttack | DownSpeed,
	Adamant = UpAttack | DownSpAttack,
	Naughty = UpAttack | DownSpDefense,
	Bold = UpDefense | DownAttack,
	Docile = None,
	Relaxed = UpDefense | DownSpeed,
	Impish = UpDefense | DownSpAttack,
	Lax = UpDefense | DownSpDefense,
	Timid = UpSpeed | DownAttack,
	Hasty = UpSpeed | DownDefense,
	Serious = None,
	Jolly = UpSpeed | DownSpAttack,
	Naive = UpSpeed | DownSpDefense,
	Modest = UpSpAttack | DownAttack,
	Mild = UpSpAttack | DownDefense,
	Quiet = UpSpAttack | DownSpeed,
	Bashful = None,
	Rash = UpSpAttack | DownSpDefense,
	Calm = UpSpDefense | DownAttack,
	Gentle = UpSpDefense | DownDefense,
	Sassy = UpSpDefense | DownSpeed,
	Careful = UpSpDefense | DownSpAttack,
	Quirky = None
};

enum class Pokemon_Gender
{
	Genderless,
	Male,
	Female
};


class Pokemon_Instance
{
	uint32_t PersonalityValue = 0;

	Pokemon_Data* Data = nullptr;
	std::string Nickname;
	uint8_t Level = 0; // 1 - 100
	bool IsShiny = false;
	Item* HeldItem;
	int8_t Ability = -1; // 0 - 2
	// moves
	uint8_t HPIV = 0, AttackIV = 0, DefenseIV = 0, SpecialAttackIV = 0, SpecialDefenseIV = 0, SpeedIV = 0; // 1 - 31
	uint8_t HPEV = 0, AttackEV = 0, DefenseEV = 0, SpecialAttackEV = 0, SpecialDefenseEV = 0, SpeedEV = 0; // 0 - 255
	Pokemon_Nature Nature = Pokemon_Nature::None;
	uint8_t Happiness = 0; // 0 - 255
	// Characteristic
	uint8_t Affection = 0; // 0 - 255

	// Modifiers
	// Status

public:

	Pokemon_Instance(Pokemon_Data* data);

	Pokemon_Data* GetSpecies() { return Data; }
	std::string GetNickname() { return Nickname; }
	int GetLevel() { return (int)Level; }
	bool GetIsShiny() { return IsShiny; }
	Item* GetHeldItem() { return HeldItem; }
	int GetAbility() { return (int)Ability; }
	int GetHPIV() { return (int)HPIV; }
	int GetAttackIV() { return (int)AttackIV; }
	int GetDefenseIV() { return (int)DefenseIV; }
	int GetSpecialAttackIV() { return (int)SpecialAttackIV; }
	int GetSpecialDefenseIV() { return (int)SpecialDefenseIV; }
	int GetSpeedIV() { return (int)SpeedIV; }
	int* GetIVs() { int IVs[]{ (int)HPIV, (int)AttackIV, (int)DefenseIV, (int)SpecialAttackIV, (int)SpecialDefenseIV, (int)SpeedIV }; return IVs; }
	int* GetEVs() { int EVs[]{ (int)HPEV, (int)AttackEV, (int)DefenseEV, (int)SpecialAttackEV, (int)SpecialDefenseEV, (int)SpeedEV }; return EVs; }
	int GetHPEV() { return (int)HPEV; }
	int GetAttackEV() { return (int)AttackEV; }
	int GetDefenseEV() { return (int)DefenseEV; }
	int GetSpecialAttackEV() { return (int)SpecialAttackEV; }
	int GetSpecialDefenseEV() { return (int)SpecialDefenseEV; }
	int GetSpeedEV() { return (int)SpeedEV; }
	Pokemon_Nature GetNature() { return Nature; }
	int GetFriendship() { return (int)Happiness; }
	int GetAffection() { return (int)Affection; }

	Pokemon_Gender GetGender();
};