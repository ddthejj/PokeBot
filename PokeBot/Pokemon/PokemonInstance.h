#pragma once

#include <stdint.h>
#include <string>

class Pokemon_Data;

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
	// Held item
	int8_t Ability = -1; // 0 - 2
	// moves
	uint8_t HPIV = 0, AttackIV = 0, DefenseIV = 0, SpecialAttackIV = 0, SpecialDefenseIV = 0, SpeedIV = 0; // 1 - 31
	uint8_t AttackEV = 0, DefenseEV = 0, SpecialAttackEV = 0, SpecialDefenseEV = 0, SpeedEV = 0; // 0 - 255
	Pokemon_Nature Nature = Pokemon_Nature::None;
	uint8_t Happiness = 0; // 0 - 255
	// Characteristic
	uint8_t Affection = 0; // 0 - 255

	// Modifiers
	// Status

public:

	Pokemon_Instance(Pokemon_Data* data);

	Pokemon_Gender Gender();
};