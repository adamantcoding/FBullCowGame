#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() {
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetSecretWordLength() const { return MySecretWord.length();  }
bool FBullCowGame::isGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{
		{3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20}
	};
	return WordLengthToMaxTries[MySecretWord.length()];
}

void FBullCowGame::Reset() {
	const FString SECRET_WORD = "benivol";
	MySecretWord = SECRET_WORD;

	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!isIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!isLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	} else if (Guess.length() != GetSecretWordLength()) {
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MySecretWord.length();

	for (int32 HWChar = 0; HWChar < WordLength; HWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MySecretWord[HWChar]) {
				if (GChar == HWChar) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::isIsogram(FString Word) const {
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::isLowerCase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
