#pragma once
#include "stdafx.h"
#include <string>

using FString = std::string;
using int32 = int;

// All Values initialise to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame
{
public:

	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();

	// Counts bulls and cows and increase try # assuming a valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	// See constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool bIsIsogram(FString) const;
	bool bIsLowerCase(FString) const;
};
