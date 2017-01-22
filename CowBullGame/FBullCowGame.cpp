#include "stdafx.h"
#include "FBullCowGame.h"
#include <string>
#include <iostream>
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() // Class Constructor
{
	Reset();
}

// Getter Methods
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

// Functional Class Methods

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5; // Declared constant once to enable easier searching
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;

	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!bIsIsogram(Guess)) // if not an isogram
	{
		return EGuessStatus::Not_Isogram; // flag not an isogram
	}
	
	else if (!bIsLowerCase(Guess)) // if guess is not all lower case
	{
		return EGuessStatus::Not_Lowercase; // flag not lowercase
	}
	else if (Guess.length() != GetHiddenWordLength()) // if guess length is wrong
	{
		return EGuessStatus::Wrong_Length; // flag word is wrong length
	}
	else
	{
		return EGuessStatus::OK; // else ok
	}
}

// Recieves a valid guess, increments turn and returns cout
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // Assuming same length as guess

	for (int32 i = 0; i < WordLength; i++) // Loop through all letter in hidden word
	{
		for (int32 j = 0; j < WordLength; j++) // Compare letters to guess
		{
			if (MyHiddenWord[i] == Guess[j]) // If they match then
			{
				if (i == j) // if theyre in the same place
				{
					BullCowCount.Bulls++; // Increment Bulls
				}
				else
				{
					BullCowCount.Cows++; //Increment Cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	// Compare letters against hidden word
	return BullCowCount;
}

bool FBullCowGame::bIsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; } // sorter considers 0 and 1 letter words to be isograms as the letters obviosuly do not repeat and instead a more meaningful error is given (see CheckGuessValidity() )

	TMap<char, bool> LetterSeen; // Setup map
	for (auto Letter : Word)	// For all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
	}
	return true;
}

bool FBullCowGame::bIsLowerCase(FString Word) const
{
	for (auto Letter : Word)	// For all letters of the word
		if (!islower(Letter)) { return false; } // If not a lowercase letter then return FALSE, not a lower case letter
		else { return true; } // Otherwise returns TRUE, assumes value must be a lowercase letter
}

