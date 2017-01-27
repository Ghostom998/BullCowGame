#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <string>
#include <iostream>
#include <map>
#include<ctime>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() // Default Constructor
{
	Reset();
}

// Getter Methods

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

// Functional Class Methods

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	MyMaxTries = GetMaxTries();

	MyHiddenWord = GetHiddenWord();
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
	if (Word.length() <= 1) { return true; } // sorter considers 0 and 1 letter words to be isograms as the letters 
						 // obviosuly do not repeat and instead a more meaningful error is given (see CheckGuessValidity() )
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
	for (auto Letter : Word)      // For all letters of the word
		if (!islower(Letter)) { return false; } // If not a lowercase letter then return FALSE, not a lower case letter
		else { return true; } // Otherwise returns TRUE, assumes word must be all lowercase letters
}

FString FBullCowGame::GetHiddenWord() const
{
	std::string HiddenWord[] = { "bird" , "fake" , "frog" , "jump" , "shop" , "bike" , "mask" , "open" , "best" , "bank" , "nail" , "cafe" , "wide" , "star" , "game" , // total = 15
		"code" , "boat" , "join" , "view" , "bang" , "dirty" , "chair" , "coral" , "money" , "heart" , "value" , "pound" , "store" , "house" , "pasty" , "party" , "dream" , // total = 17+15 = 32
		"craft" , "sound" , "boxer" , "junky" , "cigar" , "swear" , "vault" , "after" , "forest" , "ageing" , "bounce" , "donkey" , "planet" , "crusty" , "gamble" , "bucket" , // total = 16+32 = 48
		"tailor" , "castle" , "market" , "retail" , "toilet" , "chunky" , "switch" , "fabric" , "jumble" , "jacked" , "quiche" , "plaque" , "hangers" , "jukebox" , "mugshot" , // total = 48+15 = 63
		"parcels" , "subject" , "qualify" , "equably" , "curtain" , "outpace" , "society" , "travel" , "squeaky" , "jerking" , "jumping" , "closure" , "jackets" ,  // total = 14+63 = 77
		"squelch" , "zombies" , "planted" };																														// total = 3+77 = 80

	srand(time(0));

	return HiddenWord[rand() % 79];
}

