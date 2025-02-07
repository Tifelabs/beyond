#include <iostream>

int main () {

    int CodeA,CodeB,CodeC;
    std::cin >> CodeA;
    std::cin >> CodeB;
    std::cin >> CodeC;

    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    std::cout << "The sum is " << CodeSum << std::endl;
    std::cout << "The product is " << CodeProduct;

    int GuessA,GuessB,GuessC;
    std::cin >> GuessA;
    std::cin >> GuessB;
    std::cin >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    std::cout << "The guessed a total of: " << GuessSum <<std::endl;

    int GuessProduct = GuessA * GuessB * GuessC;
    std::cout << "The Total product is: "<<GuessProduct;

    std::cout<< std:: endl;
if (GuessSum == CodeSum && GuessProduct == CodeProduct)
{
    std::cout << "You win!";
}
else{
    std::cout <<"You lose, better luck next time";
}
    

    return 0;
}