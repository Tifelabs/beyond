#include <iostream>

void PrintIntroduction() {
    std::cout << R"(
          _____
         |A .  | _____
         | /.\ ||A ^  | _____
         |(_._)|| / \ ||A _  | _____
         |  |  || \ / || ( ) ||A_ _ |
         |____V||  .  ||(_'_)||( v )|
                |____V||  |  || \ / |
                       |____V||  .  |
                              |____V|

)";
}

void PlayerGame(){
    std::cout << "GUESS MANIA\n";

    const int CodeA = 2;
    const int CodeB = 4;
    const int CodeC = 3;
    

    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    std::cout << "The sum is " << CodeSum << "\n";
    std::cout << "The product is " << CodeProduct << "\n\n";

    std::cout << "ENTER YOUR GUESS" <<"\n"; 

    int GuessA, GuessB, GuessC;
    
    // Taking inputs for user's guess
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    std::cout << "The guessed sum is: " << GuessSum <<"\n";

    // Check if the guessed numbers match the original numbers
    if (GuessSum == CodeSum && GuessProduct == CodeProduct) {
        std::cout << "You win!" <<"\n";
    } else {
        std::cout << "You Lose!" <<"\n";
    }

}

int main() {

    PrintIntroduction();
    PlayerGame();
    return 0;
}
