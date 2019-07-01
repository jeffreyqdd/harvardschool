/*
Assignment: week 1 game project
File name:  qian_week1_gp.cpp
Name: Jeffrey Qian
Compiler: Microsoft Visual Studio Code
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

/* game 1: make a fortune teller */


//main code for problem 1
void fortune_teller()
{
    string replies[6] = {"Yes"
                        , "Perhaps in a week or so"
                        , "Maybe"
                        , "That is unlikely to happen"
                        , "No"
                        , "It will never happen"};
    
    string answer, playAgain;
    
    while(true)
    {
        cout << "What is your burning question regarding the mysteries of life?" << endl;

        getline(cin, answer);

        cout << "The all-knowing fortunate teller has come to a conclusion. The answer?" << endl;

        //starts at a random number in the sequence based off the system clock
        //just doing rand() will always yield the same answer
        //rand yields a num btwn 0 and a very large number, we need to % it by 6
        // no +1 since arrays start at 0
        srand(time(0));
        cout << replies[rand() % 6]  << endl << endl;



        cout << "Would you want to play again? y/n: ";
        getline(cin, playAgain);

        if(playAgain != "y")
        {
            cout << "Exiting...\n";
            break;
        }
    }

    return;
}
/*
Game 2: player has two chances to guess the right number.
*/
void shell_game()
{   
    while (true)
    {
        //initiate
        srand(time(0));
        int correct_box = rand() % 5 + 1;

        bool flag = false;
        int answer;
        string playAgain, dummy;

        //for loop for two tries max
        for(int i = 0; i < 2; i ++)
        {
            cout << "Which box contains the shell? Pick a number 1-5" << endl;
            cin >> answer;

            //flush newline
            getline(cin, dummy);

            if(answer == correct_box)
            {
                flag = true;
                break;
            }
            else if (i == 0)
                cout << "Incorrect, you may try again. \n";
            
        }
        
        //check if player got it right
        if(flag)
            cout << "You are right! Congrats!\n";
        else
            cout << "Sorry, you failed\n";
        

        //if no, break from loop
        cout << "Would you want to play again? y/n: ";
        getline(cin, playAgain);

        if(playAgain != "y")
        {
            cout << "Exiting...\n";
            break;
        }
        
    }
    
}
int main()
{   
    fortune_teller();
    
    cout << endl << endl << endl;

    shell_game();

    return 0;
}