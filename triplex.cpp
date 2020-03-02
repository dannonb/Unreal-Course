#include <iostream>
#include <ctime>



void PrintMessage(int Difficulty) {
    // this is the beginning message that details the game
    std::cout << "\n\nYou are a young wizard trying to save the world from a level " << Difficulty;
    
    std::cout << " evil sorcerer\nUnscramble the spell to unlock the sorcerers spellbook \n\n";
}



bool PlayGame(int Difficulty) {
    
    PrintMessage(Difficulty);
    
    // declare 3 number code
    const int CodeA = rand() % Difficulty + Difficulty;
    const int CodeB = rand() % Difficulty + Difficulty;
    const int CodeC = rand() % Difficulty + Difficulty;

    

    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;
    
    std::cout << " + There are three numbers in the code\n";
    std::cout << " + The codes add up to: " << CodeSum;
    std::cout << "\n + The codes multiply to give: " << CodeProduct << std::endl;

    // store player guesses
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;
    
    
    
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    // check if players code is correct
    if (GuessSum == CodeSum && GuessProduct == CodeProduct) {
        std::cout << "\n***You guessed correctly and have managed to use the sorcerers spellbook against him. \n Keep it up***";
        return true;
    } else {
        std::cout << "\n***You have made a mistake. Please try harder!***";
        return false;
    }
}

 
int main() {
   srand(time(NULL));
   const int MaxLevel = 5;
   int LevelDifficulty = 1; 
   while (LevelDifficulty <= MaxLevel) { // loop game until all levels are completed
       bool bLevelComplete = PlayGame(LevelDifficulty);
       std::cin.clear(); //clears errors
       std::cin.ignore(); // discards the buffer

       if (bLevelComplete) {
           ++LevelDifficulty;
       }
       
   }

    std::cout << "\n\n\nCongrats! You have defeated the evil sorcerer and have saved us all";
    return 0;
}
