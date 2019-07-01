#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    int usrNum, randNum = -1, guessNum = 0;
    
    srand(static_cast<unsigned int>(time(0)));
    randNum = (rand() % 10) + 1;

    while (usrNum != randNum && guessNum <= 2)
    {
        cout << "Enter a number 1 - 10: ";
        cin >> usrNum;

        guessNum++;

        if(usrNum < 1 || usrNum > 10)
            cout << "Invalid number\n";
        else if(usrNum > randNum)
            cout << "Too high, try again\n";
        else if(usrNum < randNum)
            cout << "Too low, try again\n";

    }
    if(usrNum == randNum)
        cout << "That is correct. You had: " << guessNum << " guesses\n"; 
    else
        cout << "You did not guess correctly. The answer was: " << randNum << endl;
    
    return 0;
}