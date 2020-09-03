// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    HiddenWords = GetValidWords(Isograms);


    
    SetupGame();

    // PrintLine(TEXT("The number of possible words is %i"), Isograms.Num());
    // PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Isograms).Num());
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    if (bGameover)
    {
        ClearScreen();
        SetupGame();
    }
    else
    { // checking guess
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    
    Word = HiddenWords[FMath::RandRange(0, HiddenWords.Num() - 1)];
    Lives = Word.Len();
    bGameover = false;
    // welcoming the player
    PrintLine(TEXT("Welcome to Bullcow!"));
    // PrintLine(TEXT("the hidden word is %s"), *Word);
    PrintLine(TEXT("Can you guess the %i letter word?"), Word.Len());
    PrintLine(TEXT("Please enter your guess and press Enter"));
    PrintLine(TEXT("lives: %i"), Lives);

}

void UBullCowCartridge::EndGame()
{
    bGameover = true;
    PrintLine(TEXT("Please press Enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Word == Guess)
    {
        PrintLine(TEXT("correct, you have won"));
        EndGame();
        return;
    }

    if (Word.Len() != Guess.Len())
    {
        PrintLine(TEXT("Sorry try guessing again. This hidden word is %i letters long. You have %i lives remaining"), Word.Len(), --Lives);
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left"));
        PrintLine(TEXT("The hidden word was %s"), *Word);
        EndGame();
        return;
    }

    //show bulls and cows 
    
    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("you have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {

        for (int32 Compare = Index + 1; Compare < Word.Len(); Compare++)
        {
            if (Word[Index] == Word[Compare])
            {
                return false;
            }
        }
    }

    return true;
}



TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Wordlist) const
{

TArray<FString> ValidWords;

 for (FString Word : Wordlist)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word)) 
        {
            
            ValidWords.Emplace(Word);

        }
    }

    return ValidWords;
}


FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++) {
        if (Guess[GuessIndex] == Word[GuessIndex]) {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < Word.Len(); HiddenIndex++) {
            if (Guess[GuessIndex] == Word[HiddenIndex]) {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}
