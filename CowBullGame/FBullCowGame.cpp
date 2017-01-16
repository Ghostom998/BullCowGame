#include "stdafx.h"
#include "FBullCowGame.h"
#include <iostream>

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

// Getter methods
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

// Class Methods

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5; // Declared constant once to enable easier searching
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const
{

	return false;
}

bool FBullCowGame::CheckGuessValidity(FString)
{

	return false;
}

// Recieves a valid guess, increments turn and returns cout
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// Increment return number
	MyCurrentTry++;


	// setup a return variable
	FBullCowCount BullCowCount;


	// Loop through all letter in guess
	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessLength = Guess.length();
	// Compare letters to hidden word
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < GuessLength; j++)
		{
			// If they match then
			if (MyHiddenWord[i] == Guess[j])
			{
				// if theyre in the same place
				if (i == j)
				{
					// Increment Bulls
					BullCowCount.Bulls++;
				}
				// Else
				else 
				{					
					//Increment Cows
					BullCowCount.Cows++;
				}
				
				
			}
		}
	}
	// Compare letters against hidden word
	return BullCowCount;
}

