#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All Values initialise to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame
{
public:
	
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset();
	bool CheckGuessValidity(FString);

	// Counts bulls and cows and increase try # assuming a valid guess
	FBullCowCount SubmitGuess(FString);

private:
	// See constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	
};

