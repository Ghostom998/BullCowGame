/* Section_02.cpp : Defines the entry point for the console application.

*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// Declaring the functions
void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; // instantiate a new game

// The entry point to the program
int main()
{
	BCGame.Reset();
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	constexpr int32 WORD_LENGTH = 5;
	std::cout << "Welcome to Bulls & Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?\n\n";
	return;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();

	for (int32 i = 0 ; i < MaxTries ; i++)
	{
		FText Guess = GetGuess();

		// Submit a valid guess to the game & recieve count
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		// Print number of bulls and cows
		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << std::endl;

		std::cout << "You have entered: " << Guess << std::endl;
		std::cout << std::endl;
	}
	return;
}

FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();

	std::cout << "Try " << CurrentTry;
	std::cout << ". Guess a word: ";
	FText Guess = "";

	// Get a guess from the player
	getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? y/n ";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl;

	// returns the 'bool' true or false
	return (Response[0] == 'y') || (Response[0] == 'Y');
}